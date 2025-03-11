#include "config.h"

CConfig::CConfig()
{
    ReadConfig();
}

void CConfig::ReadConfig()
{
    //read saved config
    QFile file(json_path);
    if(!file.open(QFile::ReadOnly|QFile::Text))
    {
        logger()<<"failed to read config json";
        return;
    }
    QTextStream stream(&file);
    stream.setCodec("UTF-8");
    json_text=stream.readAll();
    file.close();
    config=QJsonDocument::fromJson(json_text.toUtf8(),&json_error);
    if(json_error.error!=QJsonParseError::NoError)
    {
        logger()<<"json parse error";
        return;
    }
    root=config.object();
    server=root.value("server").toObject();
    server_addr=server.value("ip");
    server_port=server.value("port");
    client=root.value("client").toObject();
    client_id=client.value("id");

    logger()<<"config read sucess";
}

QString CConfig::GetServerAddr()
{
    QString str=server_addr.toString();
    return str;
}

int CConfig::GetServerPort()
{
    return server_port.toString().toInt();
}

QString CConfig::GetClientID()
{
    QString str=client_id.toString();
    return str;
}

void CConfig::SaveConfig(QString new_server_ip,QString new_server_port,QString new_client_id)
{
    QVariantHash obj;
    QVariantHash subdata_server,subdata_cient;
    subdata_server.insert("ip",new_server_ip);
    subdata_server.insert("port",new_server_port);
    subdata_cient.insert("id",new_client_id);
    obj.insert("server",subdata_server);
    obj.insert("client",subdata_cient);


    QJsonObject root_obj=QJsonObject::fromVariantHash(obj);
    QJsonDocument doc;
    doc.setObject(root_obj);
    QByteArray ba=doc.toJson(QJsonDocument::Compact);
    QString json_str(ba);
    QFile file(json_path);
    if(!file.open(QFile::WriteOnly|QIODevice::Text))
    {
        logger()<<"failed to write config json";
        return;
    }
    QTextStream out(&file);
    out<<json_str;
    file.close();
    logger()<<"config write sucess";
    ReadConfig();
}

