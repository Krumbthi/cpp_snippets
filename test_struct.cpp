#include <string>
#include <memory>
#include <iostream>
#include <cstdint>
#include <cstring>

// ------------------------------------------
// Definitions
// ------------------------------------------
typedef struct {
	uint32_t result1[61];
	uint32_t result2[61];
	uint32_t resultFirstScan[61];
	uint16_t overflow;
	uint16_t intervals;
} OneRoiResult;

constexpr auto BUF_SIZE = sizeof(OneRoiResult) * 128;
uint8_t RxBuffer[0xFFFFFFFF] = {0,};

// ------------------------------------------
// Helpers
// ------------------------------------------
void struct_to_buffer(OneRoiResult* result) 
{
	uint8_t buf[BUF_SIZE] = {0, };
    
	for (int i=0; i<3; i++) {
		std::cout << "result: " << (int)result[i].overflow << ", " << result[i].intervals << std::endl;
	}
	memcpy(buf, result, BUF_SIZE);
	
	for (int i=0; i<20; i++) {
		std::cout << "Buffer[" << i << "]: " << (int)buf[i] << std::endl;
	}
}

void buffer_to_struct(OneRoiResult* result)
{
    for(int i=0; i < sizeof(OneRoiResult) * 128; i++) {
        RxBuffer[i] = i;
    }

    memcpy(result, RxBuffer, BUF_SIZE);
	return;
}

int main() 
{
 	auto pResult = std::make_unique<OneRoiResult[]>(128);
    
    std::cout << "Sizeof Struct: " << sizeof(OneRoiResult) << std::endl;

	/*for(int i=0; i<3; i++) {
		pPerson[i].id = uint8_t(i+10);
		pPerson[i].age = i + 20;
	}
	pprint(pPerson.get());
    */

    buffer_to_struct(pResult.get());
	
	return 0;
}

