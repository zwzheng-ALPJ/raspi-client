#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QString>

#include <tcp_cilent.h>
#include <config.h>

namespace Ui {
class Settings;
}

class Settings : public QWidget
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private slots:
    void on_pushButton_connect_clicked();

    void on_pushButto_send_clicked();

    void on_pushButton_clicked();

    void on_pushButton_receive_clicked();

    void on_pushButton_save_server_clicked();

private:
    Ui::Settings *ui;
    CTcpClient TcpClient;
    CConfig config;
};

#endif // SETTINGS_H
