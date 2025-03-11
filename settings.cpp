#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    ui->lineEdit_server_IP->setText(config.GetServerAddr());
    QString qs=QString::number(config.GetServerPort());
    ui->lineEdit_server_port->setText(qs);
    ui->lineEdit_client_id->setText(config.GetClientID());
}

Settings::~Settings()
{
    TcpClient.Close();
    delete ui;
}

void Settings::on_pushButton_connect_clicked()
{
    QString serv_addr=ui->lineEdit_IP->text();
    char* IP;
    QByteArray ba=serv_addr.toLatin1();
    IP=ba.data();
    int port=ui->lineEdit_port->text().toInt();
    if(TcpClient.Connect(IP,port)<0)
        logger()<<"connect error";
    else
        logger()<<"connected";
}


void Settings::on_pushButto_send_clicked()
{
    QString qsmessage=ui->plainTextEdit_message->toPlainText();
    char* message;
    QByteArray ba=qsmessage.toLatin1();
    message=ba.data();
    if(TcpClient.Send(message)<0)
        logger()<<"send error";
    else
        logger()<<"send success";
}


void Settings::on_pushButton_clicked()
{
    TcpClient.Close();
    logger()<<"connection closed";
}


void Settings::on_pushButton_receive_clicked()
{
    TcpClient.Receive();
}


void Settings::on_pushButton_save_server_clicked()
{
    QString ip,port,client_id;
    ip=ui->lineEdit_server_IP->text();
    port=ui->lineEdit_server_port->text();
    client_id=ui->lineEdit_client_id->text();
    config.SaveConfig(ip,port,client_id);
}

