#include <RadioLib.h>
#include <BoardConfig.h>

#define RFM95_CS 11
#define RFM95_RST 22
#define RFM95_INT 25

const LoRaWANBand_t Region = AS923;
uint32_t DevAddr = 0x3EDE35CB;
uint8_t NwkSKey[] = { 0xFF, 0x71, 0x9E, 0x06, 0xEA, 0xE6, 0x46, 0x92, 0x56, 0x88, 0x21, 0xCD, 0x3F, 0xDB, 0xB1, 0x31 };
uint8_t AppSKey[] = { 0x49, 0x5F, 0xE9, 0x3D, 0x88, 0x2E, 0x7C, 0x0D, 0x25, 0x94, 0x71, 0x50, 0x51, 0x19, 0xFB, 0x6D };

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
  node.setDeviceStatus(map(getBattery(), 0, 100, 0, 255));
  snprintf(messageBuffer, sizeof(messageBuffer), "{\"moisture\":%.2f,\"BATT\":%.2f}", getSensor(), getBattery());
  const char* message = messageBuffer;
  int16_t state = node.sendReceive(message, 1);

  delay(500);
  rgbLedWrite(NEO_PIXEL, 0, 0, 0);
  esp_sleep_enable_timer_wakeup(LORA_SEND_TIME * 60 * 1000 * 1000);
  esp_deep_sleep_start();
}

void loop() {
}
