#ifndef ECGPPG_H
#define ECGPPG_H

#include "serial_handler.h"

#include <QBluetoothLocalDevice>

class CEcgPpg : public CSerialHandler
{
    Q_OBJECT
public:
    CEcgPpg();

    void TogglePower(short state);
    void ChangeMode(short target_mode);

signals:
    void ProcessedWave(const QByteArray &data);
    void ProcessedData(const QByteArray &data);
    void AnalysedData(QString category,QString data);

private:
    short mode=1;

private slots:
    void ProcessWave(const QByteArray data);
    void ProcessData(const QByteArray data);
    bool CalcCheckSum(const QByteArray &data);
    void AnalysisData(const QByteArray &data);
    void AnalysisWave(const QByteArray &data);
};

#endif // ECGPPG_H
