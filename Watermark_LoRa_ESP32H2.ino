#include <RadioLib.h>
#include <BoardConfig.h>
#include <EEPROM.h>

#define RFM95_CS   11
#define RFM95_RST  22
#define RFM95_INT  25

const LoRaWANBand_t Region = AS923;
uint32_t DevAddr = 0xEA52B415;
uint8_t NwkSKey[] = { 0x62, 0xE8, 0xBA, 0x11, 0x26, 0x14, 0xBC, 0xCC, 0x4E, 0x51, 0xB3, 0x7A, 0xF5, 0x05, 0x06, 0x95 };
uint8_t AppSKey[] = { 0x69, 0x20, 0x77, 0xD1, 0x23, 0xD1, 0xD3, 0x4A, 0x48, 0x56, 0xE6, 0xD2, 0xB3, 0x0F, 0x1E, 0x2C };

SX1276 radio = new Module(RFM95_CS, RFM95_INT, RFM95_RST);
LoRaWANNode node(&radio, &Region);

char messageBuffer[64];
int LORA_SEND_TIME = 1;
void setup() {
  SPI.begin(10, 4, 5);
  pinInit();
  rgbLedWrite(NEO_PIXEL, 100, 100, 100);

  while (radio.begin());
  radio.setSpreadingFactor(10);
  radio.setBandwidth(125.0);

  node.beginABP(DevAddr, NULL, NULL, NwkSKey, AppSKey);
  node.activateABP();
  node.setDeviceStatus( map(getBattery(), 0, 100, 0, 255) );
  snprintf(messageBuffer, sizeof(messageBuffer), "{\"RST\":%.2f,\"RADC\":%.0f,\"BATT\":%.2f,\"BADC\":%.0f}",getSensor(),getSensor(true),getBattery(),getBattery(true));
  const char* message = messageBuffer;
  uint8_t downlinkBuffer[64];
  size_t downlinkLength = 0;

  int16_t state = node.sendReceive(message, 1, downlinkBuffer, &downlinkLength, false, NULL, NULL);

  EEPROM.begin(32);
  if(downlinkLength > 0){
    rgbLedWrite(NEO_PIXEL, 0, 150, 200);
    EEPROM.write(0, HexToStr(downlinkBuffer, downlinkLength).toInt());
    EEPROM.commit();
  }
  else {
    if(state == 0) rgbLedWrite(NEO_PIXEL, 0, 200, 0);
    else if(state < 0) rgbLedWrite(NEO_PIXEL, 200, 0, 0);
    if (EEPROM.read(0) == 0xFF || EEPROM.read(0) == 0) {
      EEPROM.write(0, 1);
      EEPROM.commit();
    }
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
