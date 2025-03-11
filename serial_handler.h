#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>

#include "logger.h"

class CSerialHandler : public QObject
{
    Q_OBJECT
public:
    CSerialHandler(QObject *parent=nullptr);
    ~CSerialHandler();

    short OpenPort(const QString &port_name,qint32 baud_rate);

signals:
    void RecvedData(const QByteArray &data);

protected slots:
    void ReadData();
    bool SendData(const QString &data);

protected:
    QSerialPort *serial_port;


};

#endif // SERIAL_HANDLER_H
