#include "NimBLE.h"

NimBLE ble;
void bleEvent(string msg, size_t select);

extern "C" void app_main()
{
    ble.initBle("BLE_NAME");
    ble.startAdv();
    ble.setReaderHandler(&bleEvent);
}

void bleEvent(string msg, size_t select)
{
    switch (select)
    {
    case FROM_BLE:
        cout << "BLE Income : " << msg << endl;
        break;
    }
}