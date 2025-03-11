#include "serial_handler.h"

CSerialHandler::CSerialHandler(QObject *parent) : QObject(parent),serial_port(new QSerialPort(this)) //init new QSerialPort instance
{
    connect(serial_port,&QSerialPort::readyRead,this,&CSerialHandler::ReadData); //once serial port is ready to read, trigger read data function9
}

CSerialHandler::~CSerialHandler()
{
    if(serial_port->isOpen())
        serial_port->close();
}

short CSerialHandler::OpenPort(const QString &port_name, qint32 baud_rate)
{
    serial_port->setPortName(port_name);
    serial_port->setBaudRate(baud_rate);
    if(!serial_port->open(QIODevice::ReadWrite))
    {
        logger()<<"Failed to open serial port!"<<serial_port->errorString();
        return -1;
    }
    else
        return 0;
}

void CSerialHandler::ReadData()
{
    QByteArray data=serial_port->readAll();
    emit RecvedData(data);
    //logger()<<data;
}

bool CSerialHandler::SendData(const QString &data)
{
    if(serial_port->isOpen())
    {
        QByteArray ba=QByteArray::fromHex(data.toUtf8());
        serial_port->write(ba);
        if(!serial_port->waitForBytesWritten(500))
        {
            logger()<<"write failed";
        }
        else
            logger()<<"serial written: "<<ba;
        return true;
    }
    else
    {
        return false;
    }
}
