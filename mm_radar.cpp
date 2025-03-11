#include "mm_radar.h"

CMmRadar::CMmRadar(QObject *parent) : CSerialHandler(parent)
{
    connect(this,SIGNAL(RecvedData(QByteArray)),this,SLOT(ProcessData(QByteArray)));
    connect(this,SIGNAL(ProcessedData(QByteArray)),this,SLOT(AnalysisData(QByteArray)));
}

void CMmRadar::ProcessData(const QByteArray &data)
{
    const QByteArray header=QByteArray::fromHex("53595443");
    const QByteArray tail=QByteArray::fromHex("eeee");
    static QByteArray buffer=NULL;
    int start_index,end_index;

    buffer.append(data);
    //logger()<<"append:"<<data.toHex();

    start_index=buffer.indexOf(header);
    end_index=buffer.indexOf(tail,start_index)+tail.size();

    if(start_index>=0 && end_index-tail.size()>=0)
    {
        QByteArray matched_data=buffer.mid(start_index,end_index-start_index);
        emit ProcessedData(matched_data);
        //logger()<<"matched data:"<<matched_data.toHex();

        buffer.remove(0,end_index);
    }
}

void CMmRadar::AnalysisData(const QByteArray &data)
{
    int heart_rate,breathe_rate;
    heart_rate=data.mid(20,1).toHex().toInt(nullptr,16);
    breathe_rate=data.mid(19,1).toHex().toInt(nullptr,16);
    logger()<<"heartrate: "<<heart_rate<<"breatherate: "<<breathe_rate;
    emit AnalysedData("MMHR",QString::number(heart_rate));
    emit AnalysedData("MMBR",QString::number(breathe_rate));

    //deprecated, to delete
    //emit HeartRate(heart_rate);
    //emit BreatheRate(breathe_rate);
}
