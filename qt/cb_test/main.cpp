#include <QApplication>
#include <thread>
#include <chrono>
#include "../../qt/usbaccesslayer.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    auto usb = std::make_unique<UsbLayer::IUsbAccessLayer>();
    usb->InitDLL();
    return a.exec();
}
