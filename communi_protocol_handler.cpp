#include "communi_protocol_handler.h"

CCommuniProtocolHandler::CCommuniProtocolHandler()
{

}

bool CCommuniProtocolHandler::Send(QString category,QString data)
{
    bool connected=false;
    QByteArray ba=config.GetServerAddr().toUtf8();
    const char* ch=ba.constData();
    for(int i=0;i<5;i++)
    {
        if(tcp_c.Connect(ch,config.GetServerPort())>=0)
        {
            //logger()<<"server connected";
            connected=true;
            break;
        }
        tcp_c.Close();
        logger()<<"server offline, retry"<<i;
    }
    emit ConnectStatusChanged(connected);
    if(!connected)
    {
        logger()<<"server connection failed";
        return false;
    }
    else
    {
        QString message;
        message.append("START");

        message.append("DEVICE=");
        message.append(config.GetClientID());
        message.append(",");
        message.append(category);
        message.append("=");
        message.append(data);

        message.append("END");

        QByteArray ba=message.toLatin1();
        tcp_c.Send(ba.data());
        tcp_c.Close();
    }
    return true;
}
