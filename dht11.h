#ifndef DHT11_H
#define DHT11_H

#include <QDebug>
#include "logger.h"
#include <wiringPi.h>
#include <QObject>
#include <iostream>



class CDht11 : public QObject // 继承自QObject
{
    Q_OBJECT // 添加Q_OBJECT宏

public:
    CDht11(int data_pin);

    ~CDht11();

    void StartReading(void);

signals:
    void DHT11data(int humidity,int humidity_float,int temperature,int temperature_float);

private:
    unsigned char ReadSensorData(void);

    short pin_number;
};

#endif // DHT11_H
