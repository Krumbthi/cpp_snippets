#include <iostream>
#include <fstream>

using namespace std;

int main() 
{
    int x;
    ifstream infile;
    ofstream outfile;
    
    infile.open("/path/to/file.hex", ios::binary | ios::in);
    outfile.open("/path/to/hex_dump.hex", ios::binary | ios::out);
    
    if (infile) {
        // get length of file:
        infile.seekg (0, infile.end);
        long length = infile.tellg();
        infile.seekg (0, infile.beg);
        char * buffer = new char [length];

        cout << "Reading " << length << " characters... ";
        // read data as a block:
        infile.read (buffer, length);

        if (outfile) {
            outfile.write (buffer, length);
        }

        // release dynamically-allocated memory
        delete[] buffer;
    }

    infile.close();
    outfile.close();

    exit(EXIT_SUCCESS);
}
