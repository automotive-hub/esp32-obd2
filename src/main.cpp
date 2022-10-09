#include <Arduino.h>
#include <device_config.h>
#include <NimBLEDevice.h>
#include <BLE_DESIGN.g.h>

#include <MyBLE.h>
#include <serial_emulator.h>

// https://github.com/sandeepmistry/arduino-CAN

// https://github.com/collin80/ESP32RET
// https://github.com/collin80/esp32_can

// question close BLE GATT advs

// gpServer is use to controlling BLE GATT with sensor
static NimBLEServer *gpServer;

// Hidden wrapper for gatt server setup & control central pairing
static MyBLE myBLE;

static BLESerialEmulator serialEmulator;

void setup()
{
  Serial.begin(115200);
  Serial.println("Starting BLE server");
  NimBLEDevice::init(DEVICE_NAME);
  NimBLEDevice::setPower(ESP_PWR_LVL_P9);
  gpServer = NimBLEDevice::createServer();
  myBLE.init(gpServer);

  // TODO Mode
  // 1. READ continuously for OBD data
  // 2. Request read via PID
  // put your setup code here, to run once:

#ifdef DEBUG
  serialEmulator.init(&myBLE);
#endif
}
/// TODO READ OBD Code from car
/// 1. how does it hook up to the vehicle
void loop()
{
#ifdef DEBUG
  serialEmulator.start();
#endif
  // put your main code here, to run repeatedly:
}