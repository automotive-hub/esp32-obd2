#ifndef DEVICE_CONFIG_H
#define DEVICE_CONFIG_H
/// BLE SERIAL EMULATOR
#define DEBUG

/// SENSOR DATA LOG
#define DEBUG_DATA_LOG
#endif

//
#ifdef DEBUG
#define CONFIG_NIMBLE_CPP_LOG_LEVEL 4
#endif