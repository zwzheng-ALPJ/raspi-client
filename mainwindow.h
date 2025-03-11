#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <QScreen>
#include <QtConcurrent>
#include <QTime>
#include <QTimer>


#include "dht11.h"
#include "mm_radar.h"
#include "settings.h"
#include "tcp_cilent.h"
#include "config.h"
#include "ecgppg.h"
#include "communi_protocol_handler.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void UpdateTempOnScreen(int humidity,int humidity_float,int temperature,int temperature_float);


private slots:
    void StartRegularUpdate();

    void Dht11Start();

    void UpdateTimeOnScreen();

    void UpdateMMDataOnScreen(QString category,QString data);

    void on_pushButton_setting_clicked();

    void OnConnectStatusChanged(bool status);

signals:

    void initend();

private:
    Ui::MainWindow *ui;

    Settings s;

    //Create sensors' object
    CDht11 dht11;
    CMmRadar mm_radar;
    CEcgPpg ecgppg;

    CCommuniProtocolHandler client;
    CTcpClient tcp_c;
    CConfig config;

    QPixmap offline_logo;
    QPixmap online_logo;
};
#endif // MAINWINDOW_H
