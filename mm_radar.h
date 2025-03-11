#ifndef MM_RADAR_H
#define MM_RADAR_H

#include "serial_handler.h"

class CMmRadar : public CSerialHandler
{
    Q_OBJECT
public:
    CMmRadar(QObject *parent=nullptr);

signals:
    void ProcessedData(const QByteArray &data);

    void AnalysedData(QString category,QString data);

    void HeartRate(int heart_rate);

    void BreatheRate(int breathe_rate);

private slots:
    void ProcessData(const QByteArray &data);

    void AnalysisData(const QByteArray &data);

};

#endif // MM_RADAR_H
