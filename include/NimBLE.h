#ifndef KKBLE_H
#define KKBLE_H
#define PROTOCOL
#include "iostream"
#include "BLE/NimBLEDevice.h"
#include "freertos/queue.h"

using namespace std;

class NimBLE : public BLEServerCallbacks, public BLECharacteristicCallbacks
{

private:
    bool is_available = false;
    bool is_handler_invoked = false;
#ifdef PROTOCOL
    TaskHandle_t ble_handler;
#endif
    bool deviceConnected = false;
    friend void queueTask(void *pvParams);
    void onConnect(BLEServer *pServer, BLEConnInfo &connInfo);
    void onDisconnect(BLEServer *pServer, BLEConnInfo &connInfo, int reason);
    void onWrite(BLECharacteristic *pCharacteristic, BLEConnInfo &connInfo);
    const char SERVICE_UUID[37] = "6E400001-B5A3-F393-E0A9-E50E24DCCA9E";
    const char CHARACTERISTIC_UUID_RX[37] = "6E400002-B5A3-F393-E0A9-E50E24DCCA9E";
    const char CHARACTERISTIC_UUID_TX[37] = "6E400003-B5A3-F393-E0A9-E50E24DCCA9E";
    char txBuf[20];
    QueueHandle_t queue_handler;
    BLEServer *pServer = NULL;
    BLEService *pService;
    BLECharacteristic *pTxCharacteristic;
    BLECharacteristic *pRxCharacteristic;

public:
    void init_ble(string ble_name);
    void start_adv(void);
    bool isConnected(void);
    void pushQueue(char *buf);
#ifdef PROTOCOL
    void setHandler(TaskHandle_t ble_control_handler);
#endif
    // void bleEvent(string msg);
    string rxValue = "";
    string old_rxValue = "";
    void (*bleEvent)(string msg, size_t select);
    void setReaderHandler(void (*func)(string msg, size_t select));
    string getData(void);
    bool isDataAvailable(void);
};

#endif
