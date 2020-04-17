#pragma once

#include <QWidget>
#include "usbaccesslayer.h"

namespace Notifier {

class DeviceChangeNotifier : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceChangeNotifier(QWidget *parent = nullptr);
    //void start(UsbLayer::IUsbAccessLayer *usbAccessLayer, quint8 &numberOfConnectedDevs);

protected:
      auto nativeEvent(const QByteArray & eventType, void * message, long * result) -> bool override;

signals:
    //void numberOfDevicesChanged(quint8 number);
};

}
