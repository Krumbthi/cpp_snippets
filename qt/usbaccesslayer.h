#pragma once

#include <QObject>
#include <memory>

#ifdef Q_OS_WIN
#include "windows.h"
#endif

#include "../../common/AppLogger.h"
#include "../../common/FrameDispatcher.h"
#include "devicechangenotifier.h"

namespace UsbLayer {

using namespace Data;
using namespace Notifier;

class IUsbAccessLayer : public QObject
{
    Q_OBJECT
public:
    explicit IUsbAccessLayer(QObject* parent=nullptr);
    ~IUsbAccessLayer();
    void registerNotifyer();

    void InitDLL();
    void RegisterForBFChange(int winHandle, int noOfConDevs);
    void CloseDll();

    void ReadBfMainVerison();
    void ReadROStatus();
    void ReadBFStatus();
    void ReadBFMainVerion();

    void newDeviceDetected(quint8 dev);

protected:
     //void closeEvent(QCloseEvent *event);
     //bool nativeEvent(const QByteArray& eventType, void* message, long* result);

private:
    void ParseErrorMessage(qint32 errVal);
    void DispatchDataFrame(uint8_t* dataFrame, size_t frameSize);
    void Sleep(int val);

    //Ui::MainWindow *ui;
    std::unique_ptr<Logging::AppLogger> Logger;
    std::unique_ptr<FrameDispatcher>    FrameDisp;
    DeviceChangeNotifier*               DevNotifier;
    int                                 TimerID = -1;
};

}
