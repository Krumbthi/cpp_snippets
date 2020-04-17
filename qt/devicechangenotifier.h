#pragma once

#include <QWidget>
#include <functional>

namespace Notifier {

typedef std::function<void (int, int)> CallbackFunction;

class DeviceChangeNotifier : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceChangeNotifier(QWidget *parent = nullptr);
    void    RegisterCb(CallbackFunction cb);
    void    StopTimer(int id);
protected:
      auto  nativeEvent(const QByteArray & eventType, void * message, long * result) -> bool override;
      void  timerEvent(QTimerEvent *event) override;

signals:
    void    numberOfDevicesChanged(quint8 number);

private:
    CallbackFunction  CbFunc;
};

}
