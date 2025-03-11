#include "ecgppg.h"

CEcgPpg::CEcgPpg()
{
    connect(this,SIGNAL(RecvedData(QByteArray)),this,SLOT(ProcessWave(QByteArray)));
    connect(this,SIGNAL(RecvedData(QByteArray)),this,SLOT(ProcessData(QByteArray)));
    connect(this,SIGNAL(ProcessedData(QByteArray)),this,SLOT(AnalysisData(QByteArray)));
    connect(this,SIGNAL(ProcessedWave(QByteArray)),this,SLOT(AnalysisWave(QByteArray)));
}

void CEcgPpg::TogglePower(short state)
{
    short check_digit=0x14+state;
    QString command="14";
    command.append(QString::number(state,16).rightJustified(2,'0').toUpper());
    command.append(QString::number(check_digit,16).rightJustified(2,'0').toUpper());
    command.append("0D");
    SendData(command);
}

void CEcgPpg::ProcessWave(const QByteArray data)
{
    QByteArray header;
    const QByteArray tail=QByteArray::fromHex("0a");
    static QByteArray buffer=NULL;
    int start_index,end_index;
    buffer.append(data);

    switch(mode)
    {
    case 1:
        header=QByteArray::fromHex("23");
        break;
    default:
        header=QByteArray::fromHex("23");
        break;
    }

    start_index=buffer.indexOf(header);
    end_index=buffer.indexOf(tail,start_index+tail.size());

    if(start_index>=0 && end_index-tail.size()>=0)
    {
        QByteArray matched_data=buffer.mid(start_index,end_index-start_index);
        emit ProcessedWave(matched_data);
        //logger()<<"matched wave:"<<matched_data.toHex();

        buffer.remove(0,end_index);
    }
}

void CEcgPpg::ProcessData(const QByteArray data)
{
    QByteArray header=QByteArray::fromHex("26");
    const QByteArray tail=QByteArray::fromHex("0a");
    static QByteArray buffer=NULL;
    int start_index,end_index;
    buffer.append(data);

    start_index=buffer.indexOf(header);
    end_index=buffer.indexOf(tail,start_index+tail.size());

    if(start_index>=0 && end_index-tail.size()>=0)
    {
        QByteArray matched_data=buffer.mid(start_index,end_index-start_index);
        emit ProcessedData(matched_data);
        //logger()<<"matched data:"<<matched_data.toHex();

        buffer.remove(0,end_index);
    }
}

void CEcgPpg::ChangeMode(short target_mode)
{
    short hex_mode;
    switch(target_mode)
    {
    case 1:
        hex_mode=0x01;
    }
    short check_digit=0x15+hex_mode;
    QString command="15";
    command.append(QString::number(hex_mode,16).rightJustified(2,'0').toUpper());
    command.append(QString::number(check_digit,16).rightJustified(2,'0').toUpper());
    command.append("0D");
    SendData(command);
    mode=target_mode;
    logger()<<"ecgppg mode changed to: "<<mode;
}

bool CEcgPpg::CalcCheckSum(const QByteArray &data)
{
    int checksum=0;
    for(int i=0;i<data.size()-1;i++)
        checksum+=static_cast<unsigned char>(data.at(i));
    checksum&=0xFF;
    if(checksum!=static_cast<unsigned char>(data.at(data.size()-1)))
    {
        //logger()<<"didn't pass checksum:"<<data;
        return false;
    }
    //logger()<<"pass checksum"<<data;
    return true;
}

void CEcgPpg::AnalysisData(const QByteArray &data)
{
    if(!CalcCheckSum(data))
        return;
    QString string_data=QString::fromLatin1(data);
    //get rid of the head and tail
    string_data=string_data.mid(1,string_data.size()-2);
    logger()<<"string:"<<string_data;
    QStringList sl=string_data.split("=");
    emit AnalysedData(sl[0],sl[1]);
}

void CEcgPpg::AnalysisWave(const QByteArray &data)
{
    if(!CalcCheckSum(data))
        return;
    QString string_data=QString::fromLatin1(data);
    //get rid of the head and tail
    string_data=string_data.mid(1,string_data.size()-2);
    //logger()<<"string:"<<string_data;
    QStringList sl=string_data.split("\r");
    emit AnalysedData("ECGW",sl[0]);
    emit AnalysedData("PPGW",sl[1]);
}

















