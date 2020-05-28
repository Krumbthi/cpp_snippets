#include <cstdint>

// ------------------------------------------
// Definitions
// ------------------------------------------

// #define HIWORD(l)			((u16)((((u32)(l)) >> 16) & 0xFFFF))
// #define LOWORD(l)			((u16)(u32)(l))
// #define HIBYTE(w)			((u8)(((u16)(w) >> 8) & 0xFF))
// #define LOBYTE(w)			((u8)(w))
// #define MAKELONG(low, hi)	((long)(((u16)(low))|(((u32)((u16)(hi)))<<16)))
// #define MAKEWORD(low, hi)	((u16)(((u8)(low))|(((u16)((u8)(hi)))<<8)))

constexpr int8_t BUFFER_SIZE = 2;
constexpr int8_t STRUCT_BUFFER_SIZE = 1;

typedef struct {
	uint32_t result1[BUFFER_SIZE];
	uint32_t result2[BUFFER_SIZE];
	uint32_t resultFirstScan[BUFFER_SIZE];
	uint16_t overflow;
	uint16_t intervals;
} OneRoiResult;

constexpr auto BUF_SIZE = sizeof(OneRoiResult) * STRUCT_BUFFER_SIZE;
