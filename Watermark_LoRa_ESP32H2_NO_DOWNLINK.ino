#include <RadioLib.h>
#include <BoardConfig.h>

#define RFM95_CS 11
#define RFM95_RST 22
#define RFM95_INT 25

const LoRaWANBand_t Region = AS923;
uint32_t DevAddr = 0x3EDE35CB;
const char NwkSKey[] = "FF719E06EAE64692568821CD3FDBB131";
const char AppSKey[] = "495FE93D882E7C0D259471505119FB6D";

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

  node.beginABP(DevAddr, NULL, NULL, hexStringToBytes(NwkSKey).data(), hexStringToBytes(AppSKey).data());
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
