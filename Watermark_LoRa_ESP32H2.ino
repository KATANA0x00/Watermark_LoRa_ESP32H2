#include <RadioLib.h>
#include <BoardConfig.h>
#include <EEPROM.h>

#define RFM95_CS 11
#define RFM95_RST 22
#define RFM95_INT 25

const LoRaWANBand_t Region = AS923;
uint32_t DevAddr = 0x93230FFF;
uint8_t NwkSKey[] = { 0x5E, 0xD0, 0x5F, 0x6B, 0xCA, 0x7C, 0xD2, 0x56, 0xD4, 0x26, 0xE9, 0xB0, 0xA7, 0x68, 0x13, 0xAE };
uint8_t AppSKey[] = { 0xD5, 0x7F, 0x47, 0x3E, 0x1C, 0xB4, 0xA5, 0x1F, 0x9B, 0x95, 0xB8, 0xFB, 0x2C, 0x3A, 0x92, 0x01 };

SX1276 radio = new Module(RFM95_CS, RFM95_INT, RFM95_RST);
LoRaWANNode node(&radio, &Region);

char messageBuffer[64];
int LORA_SEND_TIME = 15;
void setup() {
  SPI.begin(10, 4, 5);
  pinInit();
  rgbLedWrite(NEO_PIXEL, 100, 100, 100);

  while (radio.begin());
  radio.setSpreadingFactor(10);
  radio.setBandwidth(125.0);

  node.beginABP(DevAddr, NULL, NULL, NwkSKey, AppSKey);
  node.activateABP();
  node.setDeviceStatus(map(getBattery(), 0, 100, 0, 255));
  snprintf(messageBuffer, sizeof(messageBuffer), "{\"RST\":%.2f,\"RADC\":%.0f,\"BATT\":%.2f,\"BADC\":%.0f}", getSensor(), getSensor(true), getBattery(), getBattery(true));
  const char* message = messageBuffer;
  uint8_t downlinkBuffer[64];
  size_t downlinkLength = 0;

  int16_t state = node.sendReceive(message, 1, downlinkBuffer, &downlinkLength, false, NULL, NULL);

  if (downlinkLength <= 0) {
    rgbLedWrite(NEO_PIXEL, 200, 0, 0);
    esp_sleep_enable_timer_wakeup(60 * 1000 * 1000);
    esp_deep_sleep_start();
  }

  int result = HexToStr(downlinkBuffer, downlinkLength).toInt();
  EEPROM.begin(32);
  if (result > 0) {
    rgbLedWrite(NEO_PIXEL, 0, 150, 200);
    EEPROM.write(0, result);
    EEPROM.commit();
  }
  else if (result == 0) {
    rgbLedWrite(NEO_PIXEL, 0, 200, 0);
  }

  //First Start NO EEPROM
  if (EEPROM.read(0) == 0xFF || EEPROM.read(0) == 0) {
    EEPROM.write(0, 15);
    EEPROM.commit();
  }
  LORA_SEND_TIME = EEPROM.read(0);
  EEPROM.end();

  delay(500);
  rgbLedWrite(NEO_PIXEL, 0, 0, 0);
  esp_sleep_enable_timer_wakeup(LORA_SEND_TIME * 60 * 1000 * 1000);
  esp_deep_sleep_start();
}

void loop() {
}

String HexToStr(uint8_t* data, size_t len) {
  String result = "";
  for (size_t i = 0; i < len; i++) {
    result += (char)data[i];
  }
  return result;
}
