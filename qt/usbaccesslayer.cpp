#include "usbaccesslayer.h"

#include <thread>
#include <chrono>

using namespace std;
using namespace UsbLayer;
using namespace Logging;

IUsbAccessLayer::IUsbAccessLayer(QObject* parent): QObject(parent)
{    
    Logger = make_unique<AppLogger>();
    Logger->SetTag("TestAPP");

    FrameDisp = make_unique<FrameDispatcher>();

    DevNotifier = new DeviceChangeNotifier();
//    connect(DevNotifier, SIGNAL(numberOfDevicesChanged), this, SLOT(newDeviceDetected));
}

IUsbAccessLayer::~IUsbAccessLayer()
{
    if (DevNotifier) {
        delete DevNotifier;
    }
}

void IUsbAccessLayer::InitDLL()
{
    Logger->Msg("Init Dll");
    DevNotifier->RegisterCb(
                [this](qint32 handle, quint8 noDev)
                {
                    return this->RegisterForBFChange(handle, noDev);
                });
}

void IUsbAccessLayer::RegisterForBFChange(int winHandle, int timerId)
{
    TimerID = timerId;
    Logger->Msg("Register Window handle: %d", winHandle);
    CloseDll();
}

void IUsbAccessLayer::CloseDll()
{
    Logger->Msg("DLL succesfully closed");
    DevNotifier->StopTimer(TimerID);
}

void IUsbAccessLayer::ReadBfMainVerison()
{
    Logger->Msg("");
    Sleep(3);
}

void IUsbAccessLayer::ReadROStatus()
{
    Logger->Msg("");
    Sleep(3);
}

void IUsbAccessLayer::ReadBFStatus()
{
    Logger->Msg("BF Status");
}

void IUsbAccessLayer::ReadBFMainVerion()
{
    Logger->Msg("");
    Sleep(3);
}

void IUsbAccessLayer::newDeviceDetected(quint8 dev)
{
    Logger->Msg("New device added: ", dev);
}

void IUsbAccessLayer::ParseErrorMessage(qint32 errVal)
{
    if ((errVal > 0))
        Logger->Msg("Request error msg: %d", errVal);
}

void IUsbAccessLayer::DispatchDataFrame(uint8_t* dataFrame, size_t frameSize)
{
    for (int i = 0; i < frameSize; i++) {
        Logger->Msg("Data[%d] \t: %c \t0x%02X", i, dataFrame[i], dataFrame[i]);
    }
}

void IUsbAccessLayer::Sleep(int val)
{
    this_thread::sleep_for(chrono::seconds(val));
}
