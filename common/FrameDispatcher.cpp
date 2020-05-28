#include "FrameDispatcher.h"
#include <sstream>

using namespace Data;

FrameDispatcher::FrameDispatcher()
{
	Logger = std::make_unique<AppLogger>();
	Logger->SetTag("FrameDispatcher");
}

void FrameDispatcher::SourceFWVersion(uint8_t* dataBuf) const
{
    Logger->Msg("SourceFWVersion");
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
