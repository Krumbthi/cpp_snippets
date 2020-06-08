#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

constexpr auto MAX_FILE_SIZE = 0x3c000;
constexpr auto FW_BLOCK_SIZE = 0x8000;
uint8_t dataFrame[8][0xFFFF] = {{0,}};


void hex_dump(const void *src, size_t length, size_t line_size, const char *prefix)
{
    int i = 0;
    const unsigned char *address = (unsigned char*) src;
    const unsigned char *line = address;
    unsigned char c;

    std::printf("%s | ", prefix);

    while (length-- > 0) {
        std::printf("%02X ", *address++);

        if (!(++i % line_size) || (length == 0 && i % line_size)) {
            if (length == 0) {
                while (i++ % line_size)
                    printf("__ ");
            }
            printf(" |");
            while (line < address) {
                c = *line++;
                printf("%c", (c < 32 || c > 126) ? '.' : c);
            }
            printf("|\n");
            if (length > 0)
                printf("%s | ", prefix);
        }
    }
}


void prepare_data_frame(char* pBuffer, uint32_t dataSize, uint32_t *noOfTransfers)
{
    for (int i=0; i <= (dataSize/FW_BLOCK_SIZE); i++) {
        memcpy(&dataFrame[i][0], pBuffer, FW_BLOCK_SIZE);
        pBuffer += FW_BLOCK_SIZE;
        *noOfTransfers = i+1;
    }
    cout << "No. of transfers: " << *noOfTransfers << endl;
}


int main () 
{
    ifstream infile;
    infile.open("/mnt/projects/SpArcfire/LoaderFiles/Higgs_v1.1.7-176-d1fe53e.ldr", ios::binary | ios::in);
    
    long dataSize = 0;
    uint32_t noOfTransfers = 0;

    if (infile) {
        // get length of file:
        infile.seekg (0, infile.end);
        dataSize = infile.tellg();
        infile.seekg (0, infile.beg);

        char* buffer = new char[dataSize];
        
        cout << "Reading " << dataSize << " characters... " << endl;
        // read data as a block:
        infile.read (buffer, dataSize);
        infile.close();

        // hex_dump(buffer, dataSize, 16, "");

        prepare_data_frame(buffer, dataSize, &noOfTransfers);

        // release dynamically-allocated memory
        delete[] buffer;
    }

    for (int i=0; i < noOfTransfers; i++) {
        cout << endl;
        cout << "\t Block: " << i + 1 << endl;

        hex_dump(&dataFrame[i][0], FW_BLOCK_SIZE, 16, "");
    }
    
    exit(EXIT_SUCCESS);
}