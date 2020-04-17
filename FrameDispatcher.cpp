#include "FrameDispatcher.h"
#include "UsbComDef.h"
#include <sstream>

using namespace Data;

FrameDispatcher::FrameDispatcher()
{
	Logger = std::make_unique<AppLogger>();
	Logger->SetTag("FrameDispatcher");
}

void FrameDispatcher::SourceFWVersion(uint8_t* dataBuf) const
{
	VersionAndInfo version = {};
	Logger->Msg("dispatch FW version data");
	version.HWID = dataBuf[0];
	version.ReleaseFlag = dataBuf[1];
    version.MajorRelease = MAKEWORD(dataBuf[3], dataBuf[2]);	// uint16_t
    version.MinorRelease = MAKEWORD(dataBuf[5], dataBuf[4]);	// uint16_t
	version.PatchLevel = MAKEWORD(dataBuf[7], dataBuf[6]);		// uint16_t 
	version.BuildNumber = MAKEWORD(dataBuf[9], dataBuf[8]);		// uint16_t 
	memcpy(version.gitSha1, &dataBuf[10],7);					// uint8_t 
	version.CompileDateTime.Day = dataBuf[17]; // TDateTime
	version.CompileDateTime.Month = dataBuf[18];
	version.CompileDateTime.Year = MAKEWORD(dataBuf[19], dataBuf[20]);
	version.CompileDateTime.Hour = dataBuf[21];
	version.CompileDateTime.Minute = dataBuf[22];
	version.CompileDateTime.Second = dataBuf[23];

	memcpy(version.Name, &dataBuf[25],24);		// uint8_t 
	//version.reserved[175];	// uint8_t 

	Logger->Msg("---------------------------");
	Logger->Msg("HWID: 0x%02X", version.HWID);
	Logger->Msg("Version Release Flag: %d", version.ReleaseFlag);
	Logger->Msg("%d.%d.%d.%d", version.MajorRelease, version.MinorRelease, version.PatchLevel, version.BuildNumber);
	Logger->Msg("Name: %s", ConvertToString(version.Name, 24).c_str());
	Logger->Msg("Git: %s", ConvertToString(version.gitSha1, 7).c_str());
	Logger->Msg("---------------------------");

}

std::string FrameDispatcher::ConvertToString(uint8_t* a, int size)
{
	std::ostringstream convert;
	int val;
	
	for (int i = 0; i < size; i++) {
		val = static_cast<int>(a[i]);
		convert << static_cast<char>(val);
	}
	return convert.str();
}
