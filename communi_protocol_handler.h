#ifndef COMMUNI_PROTOCOL_HANDLER_H
#define COMMUNI_PROTOCOL_HANDLER_H

#include "tcp_cilent.h"
#include "logger.h"
#include "config.h"

#include <QObject>
#include <QString>


class CCommuniProtocolHandler : public QObject
{
    Q_OBJECT
public:
    CCommuniProtocolHandler();

signals:
    void ConnectStatusChanged(bool status);

public slots:
    bool Send(QString category,QString data);

private:
    CTcpClient tcp_c;
    CConfig config;
};

#endif // COMMUNI_PROTOCOL_HANDLER_H
