#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dht11(0)
    , mm_radar()
    , ecgppg()
{
    qDebug()<<"helloworld";
    ui->setupUi(this);

    //init dht11
    connect(&dht11,SIGNAL(DHT11data(int,int,int,int)),this,SLOT(UpdateTempOnScreen(int,int,int,int)));


    //init micrometer radar
    mm_radar.OpenPort("/dev/ttyUSB0",QSerialPort::Baud115200);


    //init ppg ecg sensor
    ecgppg.OpenPort("/dev/ttyUSB1",QSerialPort::Baud115200);
    ecgppg.TogglePower(0x01);
    ecgppg.ChangeMode(1);

    connect(this, SIGNAL(initend()), this, SLOT(StartRegularUpdate()), Qt::QueuedConnection);


    //data uploading
    connect(&mm_radar,SIGNAL(AnalysedData(QString,QString)), &client, SLOT(Send(QString,QString)));
    connect(&ecgppg, SIGNAL(AnalysedData(QString,QString)), &client, SLOT(Send(QString,QString)));


    //----GUI stuff----------------------------------------------
    //init time display
    QTimer *update_time_timer=new QTimer(this);
    connect(update_time_timer,SIGNAL(timeout()),this,SLOT(UpdateTimeOnScreen()));
    update_time_timer->start(1000);

    //update data from sensor
    connect(&mm_radar,SIGNAL(AnalysedData(QString,QString)),this,SLOT(UpdateMMDataOnScreen(QString,QString)));

    //load image assets
    offline_logo.load("/home/zzw/CS-project/offline.png");
    offline_logo=offline_logo.scaled(50,50,Qt::KeepAspectRatio);
    online_logo.load("/home/zzw/CS-project/online.png");
    online_logo=online_logo.scaled(50,50,Qt::KeepAspectRatio);
    ui->label_network_condition->setPixmap(offline_logo);

    connect(&client,SIGNAL(ConnectStatusChanged(bool)),this,SLOT(OnConnectStatusChanged(bool)));

    emit initend();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Dht11Start()
{
    QEventLoop loop;
    QTimer timer;
    timer.setSingleShot(true);
    QFuture<void> future;
    QObject::connect(&timer,&QTimer::timeout,&loop,&QEventLoop::quit);

    while(1)
    {
        future=QtConcurrent::run([this]{dht11.StartReading();});
        timer.start(5000);
        loop.exec();

        if(timer.isActive())
        {
            timer.stop();
        }
        else
        {
            //logger()<<"DHT11 time out, retrying...";
        }
    }

}

void MainWindow::StartRegularUpdate()
{
    QtConcurrent::run([this]{Dht11Start();});
}


void MainWindow::UpdateTimeOnScreen()
{
    QTime time=QTime::currentTime();
    QString time_string=time.toString("HH:mm");
    ui->label_current_time->setText(time_string);
}

void MainWindow::UpdateTempOnScreen(int humidity,int humidity_float,int temperature,int temperature_float)
{
    QString qshumid,qstemp;
    qshumid.append(QString::number(humidity));
    qshumid.append(".");
    qshumid.append(QString::number(humidity_float));
    qshumid.append("%");
    qstemp.append(QString::number(temperature));
    qstemp.append(".");
    qstemp.append(QString::number(temperature_float).at(0)); //有时读取抽风会出现两位，强制只显示一位，以免搞乱排版 force showing 1 decimal place only
    qstemp.append("°C");
    ui->label_temp->setText(qstemp);
    ui->label_humid->setText(qshumid);
}

void MainWindow::UpdateMMDataOnScreen(QString category,QString data)
{
    if(category=="MMHR")
        ui->label_heartr_data->setText(data);
    else if(category=="MMBR")
        ui->label_breater_data->setText(data);
}

void MainWindow::OnConnectStatusChanged(bool is_connected)
{
    if(is_connected)
        ui->label_network_condition->setPixmap(online_logo);
    else
        ui->label_network_condition->setPixmap(offline_logo);
}

void MainWindow::on_pushButton_setting_clicked()
{
    s.show();
}


