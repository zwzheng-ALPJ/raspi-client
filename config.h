#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QFile>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>


#include <logger.h>

class CConfig
{
public:
    CConfig();
    void ReadConfig();
    void SaveConfig(QString new_server_ip,QString new_server_port,QString new_client_id);
    QString GetServerAddr();
    int GetServerPort();
    QString GetClientID();

private:
    const QString json_path="/home/zzw/config/client_config.json";
    QString json_text;
    QJsonParseError json_error;
    QJsonDocument config;
    QJsonObject root;
    QJsonObject server;
    QJsonObject client;
    QJsonValue server_addr;
    QJsonValue server_port;
    QJsonValue client_id;

};

#endif // CONFIG_H
