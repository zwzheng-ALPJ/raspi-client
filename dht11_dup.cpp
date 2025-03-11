#include "dht11.h"

CDht11::CDht11(int data_pin)
{
    // 设置dht11的数据引脚
    // set pin number of dht11 sensor
    pin_number=data_pin;
}

CDht11::~CDht11()
{

}

typedef unsigned char uint8;
typedef unsigned int  uint16;
typedef unsigned long uint32;

#define HIGH_TIME 32

uint32 databuf;

uint8 CDht11::ReadSensorData(void)
{
    uint8 crc = '\0';
    uint8 i;

    pinMode(pin_number, OUTPUT); // set mode to output
    digitalWrite(pin_number, 0); // output a high level
    delay(25);
    digitalWrite(pin_number, 1); // output a low level
    pinMode(pin_number, INPUT); // set mode to input
    pullUpDnControl(pin_number, PUD_UP);

    delayMicroseconds(27);
    if (digitalRead(pin_number) == 0) //SENSOR ANS
    {
        while (!digitalRead(pin_number)); //wait to high

        for (i = 0; i < 32; i++)
        {
            while (digitalRead(pin_number)); //data clock start
            while (!digitalRead(pin_number)); //data start
            delayMicroseconds(HIGH_TIME);
            databuf *= 2;
            if (digitalRead(pin_number) == 1) //1
                databuf++;
        }

        for (i = 0; i < 8; i++)
        {
            while (digitalRead(pin_number))
                ; //data clock start
            while (!digitalRead(pin_number))
                ; //data start
            delayMicroseconds(HIGH_TIME);
            crc *= 2;
            if (digitalRead(pin_number) == 1) //1
            {
                crc++;
            }
        }
        return 1;
    }
    else
        return 0;
}


void CDht11::StartReading(void)
{
    logger()<<"DHT11 is connected at pin "<<pin_number;
    if (-1 == wiringPiSetup()) {
        qDebug("Setup wiringPi failed!");
        return;
    }

    pinMode(pin_number, OUTPUT); // set mode to output
    digitalWrite(pin_number, 1); // output a high level

    qDebug("DHT11: Start reading...");
    while (1)
    {
        pinMode(pin_number, OUTPUT); // set mode to output
        digitalWrite(pin_number, 1); // output a high level
        delay(3000);

        QEventLoop loop;
        QTimer timer;
        timer.setSingleShot(true);
        QFuture<bool> future = QtConcurrent::run(this, &CDht11::ReadSensorData);
        QObject::connect(&timer, &QTimer::timeout, &loop, &QEventLoop::quit);
        timer.start(5000); // 设置超时时间为5秒
        loop.exec();

        if (timer.isActive()) {
            // ReadSensorData 完成，停止计时器
            timer.stop();
            if (future.result()) {
                qDebug("DHT11: read success");
                emit DHT11data((databuf >> 24) & 0xff,(databuf >> 16) & 0xff,(databuf >> 8) & 0xff, databuf & 0xff);
                qDebug("Humid:%ld.%ld", (databuf >> 24) & 0xff, (databuf >> 16) & 0xff);
                qDebug("Temp:%ld.%ld", (databuf >> 8) & 0xff, databuf & 0xff);
                databuf = 0;
            } else {
                qDebug("DHT11: no respond, time out!");
                databuf = 0;
            }
        } else {
            // 超时，future还未完成
            qDebug("ReadSensorData timeout, retrying...");
            // 这里可以添加重试逻辑
        }
    }
}
