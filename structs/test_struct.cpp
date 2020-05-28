#include <string>
#include <memory>
#include <iostream>
#include <cstring>
#include "../common/defs.h"

/**
 * Macro definitions
 */
template<typename T1, typename T2>
constexpr auto MAKEWORD(T1 a, T2 b) {
	return static_cast<uint16_t>((static_cast<uint8_t>(a) << 8)) | (static_cast<uint16_t>(static_cast<uint8_t>(b)));
}

/* Get 8 bits of 16 bit value. */
template<typename T1>
constexpr auto LOBYTE(T1 x) {
	return static_cast<uint8_t>((x) & 0xFFu);
}

template<typename T1>
constexpr auto HIBYTE(T1 x) {
	return static_cast<uint8_t>(static_cast<uint16_t>(x) >> 8);
}

/* Get 16 bits of 32 bit value. */
template<typename T1>
constexpr auto LOWORD(T1 x) {
	return static_cast<uint16_t>((x) & 0xFFFFu);
}

template<typename T1>
constexpr auto HIWORD(T1 x) {
	return static_cast<uint16_t>(static_cast<uint32_t>(x) >> 16);
}

template<typename T1>
constexpr auto ARRAY_SIZE(T1 a) {
	return static_cast<int>(sizeof(a)/ sizeof(uint8_t));
}

template<typename T1, typename T2>
constexpr auto MAKELONG(T1 low, T2 hi) {
	return (static_cast<uint32_t>(static_cast<uint16_t>(low)|((static_cast<uint32_t>(static_cast<uint16_t>(hi))) << 16)));
}

static uint8_t RxBuffer[BUF_SIZE] = {0, };

// ------------------------------------------
// Helpers
// ------------------------------------------
void create_buffer()
{
    // eine Structur -> ein Datensatz
    // modulo calc here 
    for(int i = 0; i < BUF_SIZE; i++) {
        std::cout << "Modulo: " << i%2 << std::endl;
        switch (i)
        {
        case 0:
            RxBuffer[i] = 10;        
            break;
        case 4: 
            RxBuffer[i] = 11;
            break;
        case 8: 
            RxBuffer[i] = 20;
            break;
        case 12: 
            RxBuffer[i] = 21;
            break;
        case 16: 
            RxBuffer[i] = 30;
            break;
        case 20: 
            RxBuffer[i] = 31;
            break;
        case 24: 
            RxBuffer[i] = 4;
            break;
        case 26: 
            RxBuffer[i] = 5;
            break;
        default:
            RxBuffer[i] = 0;
            break;
        }
    }    
}

void struct_to_buffer(OneRoiResult* result) 
{
    uint8_t buf[BUF_SIZE] = {0, };
    
    for (int i = 0; i < STRUCT_BUFFER_SIZE; i++) {
        std::cout << "result: " << (int)result[i].overflow << ", " << result[i].intervals << std::endl;
    }

    memcpy(buf, result, BUF_SIZE);

    for (int i=0; i<20; i++) {
        std::cout << "Buffer[" << i << "]: " << (int)buf[i] << std::endl;
    }
}

void buffer_to_struct(OneRoiResult* pResult, size_t bufSize)
{    
    memcpy(pResult, RxBuffer, bufSize);
}

void buf_to_struct_man(OneRoiResult* pResult, size_t bufSize)
{
    /*for(int i=0; i < BUF_SIZE; i++) {
        RxBuffer[i] = i;
    }*/
    int j = 0;
    for (int i = 0; i < STRUCT_BUFFER_SIZE; i++) {
        pResult[i].result1[j] = MAKELONG(MAKEWORD(RxBuffer[i+1], RxBuffer[i]), MAKEWORD(RxBuffer[i+3], RxBuffer[i+2]));
        pResult[i].result1[j+1] = MAKELONG(MAKEWORD(RxBuffer[i+5], RxBuffer[i+4]), MAKEWORD(RxBuffer[i+7], RxBuffer[i+6]));

        pResult[i].result2[j] = MAKELONG(MAKEWORD(RxBuffer[i+9], RxBuffer[i+8]), MAKEWORD(RxBuffer[i+11], RxBuffer[i+10]));
        pResult[i].result2[j+1] = MAKELONG(MAKEWORD(RxBuffer[i+13], RxBuffer[i+12]), MAKEWORD(RxBuffer[i+15], RxBuffer[i+14]));

        pResult[i].resultFirstScan[j] = MAKELONG(MAKEWORD(RxBuffer[i+17], RxBuffer[i+16]), MAKEWORD(RxBuffer[i+19], RxBuffer[i+18]));
        pResult[i].resultFirstScan[j+1] = MAKELONG(MAKEWORD(RxBuffer[i+21], RxBuffer[i+20]), MAKEWORD(RxBuffer[i+23], RxBuffer[i+22]));

        pResult[i].overflow = MAKEWORD(RxBuffer[i+25], RxBuffer[i+24]);
        pResult[i].intervals = MAKEWORD(RxBuffer[i+27], RxBuffer[i+26]);
    }
}

template<size_t row, size_t col>
void write_data_frame(void* pBuffer, size_t bufSize, uint8_t (&dataFrame)[row][col])
{
    size_t i = 0, j = 0;
    for(; i<row; i++) {
        for (; j<col; j++) {
            dataFrame[i][j] = *((uint8_t*)pBuffer+j);
        }
    }
}

template<size_t row, size_t col>
void print_data_frame(uint8_t (&dataFrame)[row][col])
{
    std::cout << "Print dataframe ..." << std::endl; 
    std::cout << "Rows: " << row << "; Cols: " << col << std::endl;

    for (size_t i=0; i < row; i++) {
        std::cout << "data[" << i <<"]";
        for (size_t j=0; j < col; j++) {
            std::cout << "[" << j << "]: " << std::hex << dataFrame[i][j] << "; ";
        }
        std::cout << std::endl;
    }

    std::cout << "done" << std::endl;
}

int main()
{
    auto pResult = std::make_unique<OneRoiResult[]>(STRUCT_BUFFER_SIZE);

    std::cout << "Sizeof Struct: " << sizeof(OneRoiResult) << std::endl;
    create_buffer();

#ifdef MEM_CPY
    buffer_to_struct(pResult.get(), sizeof(OneRoiResult));
    std::cout << "Buf memcpy! " << std::endl;
#else 
    buf_to_struct_man(pResult.get(), sizeof(OneRoiResult));
    std::cout << "Buf manualy copy! " << std::endl;
#endif

    for(int i = 0; i < STRUCT_BUFFER_SIZE; i++) {
        std::cout << "Result id: " 
            << pResult[i].result1[0] 
            << "; " << pResult[i].result2[0]
            << "; " << pResult[i].resultFirstScan[0]
            << "; " << pResult[i].overflow 
            << "; " << pResult[i].intervals  
            << std::endl;

        std::cout << "Result id: " 
            << pResult[i].result1[1] 
            << "; " << pResult[i].result2[1]
            << "; " << pResult[i].resultFirstScan[1]
            << "; " << pResult[i].overflow 
            << "; " << pResult[i].intervals  
            << std::endl;
    }

    uint8_t dataFrame[3][8] = { { } };
    uint8_t buffer[24] = {0x41, 0x42, 0x43, 0x45, 
                          0x26, 0x27, 0x28, 0x29, 
                          0x0A, 0x0B, 0x0C, 0x0D, 
                          0x0E, 0x0F, 0x10, 0x12, 
                          0x13, 0x14, 0x15, 0x16, 
                          0x17, 0x18, 0x19, 0x1A };

    write_data_frame(buffer, sizeof(buffer), dataFrame);
    print_data_frame(dataFrame);
    
    return EXIT_SUCCESS;
}

