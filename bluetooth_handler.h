#ifndef BLUETOOTH_HANDLER_H
#define BLUETOOTH_HANDLER_H

#include <QObject>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>

class CBluetoothHandler : public QObject
{
    Q_OBJECT
public:
    CBluetoothHandler();
    void Discover(char *device_name);
    bool Connect();

private:
    QLowEnergyController *bt_control;
    QList<QBluetoothDeviceInfo> *device_info_list;
};

#endif // BLUETOOTH_HANDLER_H
