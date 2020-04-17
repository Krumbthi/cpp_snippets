#pragma once
#include <cstdint>
#include <memory>

#include "AppLogger.h"

/**
 * Macro definitions
 */
#ifndef Q_OS_WIN
template<typename T1, typename T2>
constexpr auto MAKEWORD(T1 a, T2 b) {
    return static_cast<uint16_t>((static_cast<uint8_t>(a) << 8)) | (static_cast<uint16_t>(static_cast<uint8_t>(b)));
}

/* Get 8 bits of 16 bit value. */
template<typename T1>
constexpr auto LO8(T1 x) {
    return static_cast<uint8_t>((x) & 0xFFu);
}

template<typename T1>
constexpr auto HI8(T1 x) {
    return static_cast<uint8_t>(static_cast<uint16_t>(x) >> 8);
}

/* Get 16 bits of 32 bit value. */
template<typename T1>
constexpr auto LO16(T1 x) {
    return static_cast<uint16_t>((x) & 0xFFFFu);
}

template<typename T1>
constexpr auto HI16(T1 x) {
    return static_cast<uint16_t>(static_cast<uint32_t>(x) >> 16);
}

template<typename T1>
constexpr auto ARRAY_SIZE(T1 a) {
    return static_cast<int>(sizeof(a)/ sizeof(uint8_t));
}
#endif

// old style macros ------------------------------------------------------------------------------------------
// #define MAKEWORD(a, b)  		(((uint16_t)(((uint8_t)(a) << 8)) | ((uint16_t) ( (uint8_t) (b)))))
// #define LO8(x)                  ((uint8_t) ((x) & 0xFFu))
// #define HI8(x)                  ((uint8_t) ((uint16_t)(x) >> 8))
// #define LO16(x)                 ((uint16_t) ((x) & 0xFFFFu))
// #define HI16(x)                 ((uint16_t) ((uint32_t)(x) >> 16))

/* Swap the byte ordering of 32 bit value */
// #define SWAP_ENDIAN32(x)          ((uint32_t)((((x) >> 24) & 0x000000FFu) | (((x) & 0x00FF0000u) >> 8) | (((x) & 0x0000FF00u) << 8) | ((x) << 24)))

/* Swap the byte ordering of 16 bit value */
// #define SWAP_ENDIAN16(x)      	((uint16_t)(((x) << 8) | (((x) >> 8) & 0x00FFu)))


namespace Data {

using namespace ::Logging;

/**
 * Frame dispatcher class
 */
class FrameDispatcher
{
public:
	FrameDispatcher();
    FrameDispatcher(const FrameDispatcher&) = delete;
    FrameDispatcher& operator=(const FrameDispatcher&) = delete;
    FrameDispatcher(FrameDispatcher&&) = delete;
    FrameDispatcher& operator=(FrameDispatcher&&) = delete;
	~FrameDispatcher() = default;

	void SourceFWVersion(uint8_t* dataBuf) const;

private:
	static std::string ConvertToString(uint8_t* a, int size);
	std::unique_ptr<AppLogger>  Logger;
};

}
