#include "devicechangenotifier.h"
#include <QDebug>
#include <QTimerEvent>

#ifdef Q_OS_WIN
#include "UsbComDef.h"
#include <windows.h>
#endif

using namespace Notifier;

DeviceChangeNotifier::DeviceChangeNotifier(QWidget *parent)
    : QWidget(parent)
{
}

bool DeviceChangeNotifier::nativeEvent(const QByteArray& eventType, void* message, long* result)
{
#ifdef Q_OS_WIN
    if (eventType == "windows_generic_MSG") {
#if (QT_VERSION == QT_VERSION_CHECK(5, 11, 1))
       MSG* msg = *reinterpret_cast<MSG**>(message);
#else
       MSG* msg = reinterpret_cast<MSG*>(message);
#endif
       if (msg->message == WM_NUMBER_OF_BFS_CHANGE) {
           //emit numberOfDevicesChanged(msg->wParam);
           qDebug() << "test";
       }
    }
    // Handed to Qt processing
    return QWidget::nativeEvent(eventType, message, result);
#else
    Q_UNUSED(eventType)
    Q_UNUSED(message)
    Q_UNUSED(result)

    return false;
#endif
}

void DeviceChangeNotifier::timerEvent(QTimerEvent *event)
{
     qDebug() << "Timer ID:" << event->timerId();
     CbFunc(this->winId(), event->timerId());
}

void DeviceChangeNotifier::RegisterCb(CallbackFunction cb)
{
    CbFunc = cb;
    startTimer(3000);   // 1-second timer
}

void DeviceChangeNotifier::StopTimer(int id)
{
    killTimer(id);
}
