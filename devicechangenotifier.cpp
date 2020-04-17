#include "devicechangenotifier.h"
#include "UsbComDef.h"
#include <QDebug>

#ifdef Q_OS_WIN
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
    return false;
#endif
}

//void DeviceChangeNotifier::start(IUsbAccessLayer *usbAccessLayer, quint8 &numberOfConnectedDevs)
//{
//#ifdef Q_OS_WIN
//       usbAccessLayer->RegisterForBFChange(reinterpret_cast<HWND>(this->winId()), numberOfConnectedDevs);
//#else
//       Q_UNUSED(numberOfConnectedDevs);
//       Q_UNUSED(usbAccessLayer);
//       return UsbResult::DLL_CO_OK;
//#endif
//}
