
#include "MyBLE.h"
// TODO Setup for other services
MyBLE::MyBLE() {}

// TODO add in bool for libary actionable, throw error
void MyBLE::init(NimBLEServer *pBLE_SERVER)
{
    gpServer = pBLE_SERVER;
    gpServer->setCallbacks(new MyBLEServerCallbacks());

    // Bringing ours BLE Services up and it corrsponding charecteristic
    initEngineBLE();

    /// Advertising GATT
    const char *manufacturer = DEVICE_NAME;
    NimBLEAdvertising *pAdvertising = NimBLEDevice::getAdvertising();
    // pAdvertising->addServiceUUID(BLE_SERVICE_PROXIMITY_UUID);
    pAdvertising->setManufacturerData(manufacturer);
    pAdvertising->addServiceUUID(BLE_SERVICE_ENGINE_UUID);
    //...
    //...
    pAdvertising->addServiceUUID(BLE_SERVICE_GENERIC_UUID);
    //
    pAdvertising->addServiceUUID(BLE_SERVICE_BATTERY);
    pAdvertising->addServiceUUID(BLE_SERVICE_OTA_UUID);

    pAdvertising->start();
    ////
}

void MyBLE::initEngineBLE()
{
    pEngineServices = gpServer->createService(BLE_SERVICE_ENGINE_UUID);
    pEngineServices->createCharacteristic(BLE_ENGINE_SPEED_METER_CHARACTERISTIC);
    pEngineServices->createCharacteristic(BLE_ENGINE_LOAD_CHARACTERISTIC);
    pEngineServices->createCharacteristic(BE_ENGINE_RPM_CHARACTERISTIC);
    pEngineServices->start();
}

/// ------------------ SET BLE DATA AND NOTIFY TO MOBILE APP

// BLE_ENGINE_SPEED_METER_CHARACTERISTIC
void MyBLE::setEngineSpeedMeter(String number, bool isNotify)
{
    NimBLECharacteristic *pCharacteristic = pEngineServices->getCharacteristic(BLE_ENGINE_SPEED_METER_CHARACTERISTIC);
    pCharacteristic->setValue(std::string(number.c_str()));
    if (isNotify)
    {
        pCharacteristic->notify();
    }
}

// BLE_ENGINE_LOAD_CHARACTERISTIC
void MyBLE::setEngineLoad(String number, bool isNotify)
{
    NimBLECharacteristic *pCharacteristic = pEngineServices->getCharacteristic(BLE_ENGINE_LOAD_CHARACTERISTIC);
    pCharacteristic->setValue(std::string(number.c_str()));
    if (isNotify)
    {
        pCharacteristic->notify();
    }
}

// BE_ENGINE_RPM_CHARACTERISTIC
void MyBLE::setEngineRPM(String number, bool isNotify)
{
    NimBLECharacteristic *pCharacteristic = pEngineServices->getCharacteristic(BE_ENGINE_RPM_CHARACTERISTIC);
    pCharacteristic->setValue(std::string(number.c_str()));
    if (isNotify)
    {
        pCharacteristic->notify();
    }
}

//

// using for debug
void MyBLE::setGeneric(String number, char *BLE_UUID, bool isNotify)
{
    NimBLECharacteristic *pCharacteristic = pGenericServices->getCharacteristic(BLE_UUID);

    if (pCharacteristic != nullptr)
    {
        pCharacteristic = pGenericServices->createCharacteristic(BLE_UUID, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY);
    }
    pCharacteristic->setValue(number);
    if (isNotify)
    {
        pCharacteristic->notify();
    }
};

bool MyBLE::isMobileConnected()
{
    return deviceConnected;
}