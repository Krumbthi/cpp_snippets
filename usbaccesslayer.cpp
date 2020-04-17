#include "usbaccesslayer.h"

#include <thread>
#include <chrono>

#include "UsbComDef.h"
#include "ErrorMap.h"
#include "USBComAPI.h"
#include "USBCommunicationJob.h"

using namespace std;
using namespace UsbLayer;
using namespace Logging;

IUsbAccessLayer::IUsbAccessLayer(QObject* parent): QObject(parent)
{    
    Logger = make_unique<AppLogger>();
    FrameDisp = make_unique<FrameDispatcher>();

//    DevNotifier = new DeviceChangeNotifier();
//    connect(DevNotifier, SIGNAL(numberOfDevicesChanged), this, SLOT(newDeviceDetected));
}

IUsbAccessLayer::~IUsbAccessLayer()
{
//    if (DevNotifier) {
//        delete DevNotifier;
//    }
}

#if 0
void IUsbAccessLayer::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
    CloseDll();
}
#endif

void IUsbAccessLayer::InitDLL()
{
    auto retval = UsbResult::DLL_CO_OK;
    Logger->SetTag("TestAPP");

    auto* dllVersion = new Version();
    dllVersion->majorRelease = 0;
    dllVersion->minorRelease = 0;
    dllVersion->patchlevel = 0;
    dllVersion->build = 0;

    Logger->Msg("Application for testing the dll");

    retval = USBCO_InitDLL(dllVersion);

    if (retval == UsbResult::DLL_CO_OK) {
        Logger->Msg("DLL Version: %d.%d.%d.%d", dllVersion->majorRelease, dllVersion->minorRelease, dllVersion->patchlevel, dllVersion->build);
//        DevNotifier->start(this, NoOfConnectedDevs);
    } else {
        ParseErrorMessage(retval);
    }
}

void IUsbAccessLayer::RegisterForBFChange(HWND winHandle, quint8 &noOfConDevs)
{
    
}

void IUsbAccessLayer::CloseDll()
{
        Logger->Msg("DLL succesfully closed");
}

void IUsbAccessLayer::ReadBfMainVerison()
{
    Sleep(3);
}

void IUsbAccessLayer::ReadROStatus()
{
    Sleep(3);
}

void IUsbAccessLayer::ReadBFStatus()
{
    
        Logger->Msg("BF Stutus failure");
    
}

void IUsbAccessLayer::ReadBFMainVerion()
{
    
    Sleep(3);
}

void IUsbAccessLayer::newDeviceDetected(quint8 dev)
{
    Logger->Msg("New device added: ", dev);
}

void IUsbAccessLayer::ParseErrorMessage(UsbResult errVal)
{
    if ((errVal > UsbResult::DLL_CO_OK))
        Logger->Msg("Request error msg: %s", ErrorMap[errVal].c_str());
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

