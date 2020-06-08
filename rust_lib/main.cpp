#include <iostream>
#include <memory>
#include "usb_com_bf.h"

using namespace std;

int main()
{
    cout << "Using Rust library" << endl;
    auto version = make_unique<Version>();
    auto retval = USBCO_InitDLL(version.get());

    if (retval) {
        cout << "Can not init library" << endl;
        exit(EXIT_FAILURE);
    }

    cout << "Library version: " << version->majorRelease << "." << version->minorRelease << "." << version->patchLevel << "." << version->build << endl;
    
    uint32_t serialNo;
    retval = USBCO_GetOpticSN(&serialNo);

    USBCO_CloseDLL();

    exit(EXIT_SUCCESS);
}

