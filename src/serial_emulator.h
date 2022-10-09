
#include <device_config.h>
#include <NimBLEServer.h>
#include <Arduino.h>
#include <MyBLE.h>

#ifndef MYBLE_H_
#define MYBLE_H_
#endif

#ifdef DEBUG
/* TODO mock create fake sensor data :> (currently in order & shipping :>)
  - [x] proximity
  - [x] thermometer
*/
// TODO web-client for to controlling sensor over serial (python,nodejs maybe)
// using keyboard input suck, web forward port client UI just click click :)) we could writing ours testcases
// key/data (97:15)-> 97 for calling proximity - 15cm in range :>

// control sensor data state and calling gatt services and characteristics
String serialInput;
int key;
String value;
String genericBLE_UUID = "";

void parsingCommandFromSerial()
{
    serialInput = Serial.readStringUntil('\n');
    int index = serialInput.indexOf(":");
    int indexGenericBLE_UUID = serialInput.lastIndexOf(":");
    //

    key = atoi(serialInput.substring(0, index).c_str());
    ///
    value = serialInput.substring(index + 1, serialInput.length());
    /// 69:23:BLE_UUID
    if (index != indexGenericBLE_UUID)
    {
        genericBLE_UUID = serialInput.substring(indexGenericBLE_UUID + 1, serialInput.length());
    }
}

class BLESerialEmulator
{
private:
    MyBLE *gpMyBLE;
    void log();

public:
    BLESerialEmulator();
    void init(MyBLE *myBLE);
    void start();
};

BLESerialEmulator::BLESerialEmulator() {}

void BLESerialEmulator::init(MyBLE *myBLE)
{
    gpMyBLE = myBLE;
};

void BLESerialEmulator::log()
{
#ifdef DEBUG_DATA_LOG
    Serial.println("[DEV] BLESerialEmulator:\t" + String(key) + ":\t" + value + ":\t" + genericBLE_UUID);
#endif
}

void BLESerialEmulator::start()
{
    while (Serial.available())
    {
        parsingCommandFromSerial();
        switch (key)
        {
        case 1:
            gpMyBLE->setEngineSpeedMeter(value);
            break;
        case 2:
            gpMyBLE->setEngineRPM(value);
            break;
        case 3:
            gpMyBLE->setEngineLoad(value);
            break;
        case 69:
            gpMyBLE->setGeneric(value, (char *)genericBLE_UUID.c_str());
            break;
        default:
            break;
        }
        log();
        Serial.flush();
    }
}
#endif