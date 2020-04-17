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
    USBCO_RegisterForBFChange(winHandle, &noOfConDevs);
}

void IUsbAccessLayer::CloseDll()
{
    if (USBCO_CloseDLL() == UsbResult::DLL_CO_OK) {
        Logger->Msg("DLL succesfully closed");
    }
}

void IUsbAccessLayer::ReadBfMainVerison()
{
    auto* versionAndInfo = new VersionAndInfo({ 0 });
    auto retval = USBRO18_GetBfMainVersionAndInfo(versionAndInfo);
    if (retval == UsbResult::DLL_CO_OK) {
        Logger->Msg("BF Main Version");
        Logger->Msg("Major release: 0x%04X", versionAndInfo->MajorRelease);
        Logger->Msg("Minor release: 0x%04X", versionAndInfo->MinorRelease);
        Logger->Msg("Patch level  : 0x%04X", versionAndInfo->PatchLevel);
        Logger->Msg("Build number : 0x%04X", versionAndInfo->BuildNumber);
        Logger->Msg("Release flag : %d", static_cast<int>(versionAndInfo->ReleaseFlag));
        Logger->Msg("Name         : %s", versionAndInfo->Name);
        Logger->Msg("Compile time : %02d.%02d.%04d", versionAndInfo->CompileDateTime.Day, versionAndInfo->CompileDateTime.Month, versionAndInfo->CompileDateTime.Year);
    }
    else {
        ParseErrorMessage(retval);
    }
    Sleep(3);
}

void IUsbAccessLayer::ReadROStatus()
{
    auto* ro18Status = new Ro18Status({ 0 });
    auto retval = USBRO18_GetRO18Status(ro18Status);
    if (retval == UsbResult::DLL_CO_OK) {
        Logger->Msg("BatteryVoltage: %f", ro18Status->batteryVoltage);
        Logger->Msg("MainBoardTemperature: %f", ro18Status->mainBoardTemperature);
        Logger->Msg("SourceStatus  : 0x%02X", ro18Status->sourceStatus);
        Logger->Msg("I_MASK_HW     : 0x%04X ", ro18Status->inputMask);
    } else {
        ParseErrorMessage(retval);
    }
    Sleep(3);
}

void IUsbAccessLayer::ReadBFStatus()
{
    auto* bfStatus = new BfStatus();
    auto retval = USBCO_GetBFStatus(bfStatus);
    if (retval == UsbResult::DLL_CO_OK) {
        Logger->Msg("BF Status");
        Logger->Msg("Address: ", bfStatus->bfAddress);
        Logger->Msg("%d", bfStatus->readOutType);
        Logger->Msg("%s", bfStatus->firmwareVersion);
        Logger->Msg("%s", bfStatus->applicationVersion);
        Logger->Msg("%s", bfStatus->frameworkVersion);
        Logger->Msg("%s", bfStatus->cpldVersion);
        Logger->Msg("%s", bfStatus->flashID);
        Logger->Msg("%s", bfStatus->firmwareName);
        Logger->Msg("%s", bfStatus->compileDate);
        Logger->Msg("%s", bfStatus->compileTime);
    } else {
        Logger->Msg("BF Stutus failure");
    }
}

void IUsbAccessLayer::ReadBFMainVerion()
{
    auto* bfVersionAndInfo = new VersionAndInfo({ 0 });
    auto retval = USBRO18_GetBfFwVersionAndInfo(bfVersionAndInfo);
    if (retval == UsbResult::DLL_CO_OK) {
        Logger->Msg("BF FW Version");
        Logger->Msg("Major release: 0x%04X", bfVersionAndInfo->MajorRelease);
        Logger->Msg("Minor release: 0x%04X", bfVersionAndInfo->MinorRelease);
        Logger->Msg("Patch level  : 0x%04X", bfVersionAndInfo->PatchLevel);
        Logger->Msg("Build number : 0x%04X", bfVersionAndInfo->BuildNumber);
        Logger->Msg("Release flag : %d", static_cast<int>(bfVersionAndInfo->ReleaseFlag));
        Logger->Msg("Name         : %s", bfVersionAndInfo->Name);
        Logger->Msg("Compile time : %02d.%02d.%04d", bfVersionAndInfo->CompileDateTime.Day, bfVersionAndInfo->CompileDateTime.Month, bfVersionAndInfo->CompileDateTime.Year);
    } else {
        ParseErrorMessage(retval);
    }
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

