#include <RadioLib.h>
#include <BoardConfig.h>

#define RFM95_CS 11
#define RFM95_RST 22
#define RFM95_INT 25

#define HOLD 3

const LoRaWANBand_t Region = AS923; // Set Frequency to 923 MHz

uint32_t DevAddr = 0x6E395B2B;
const char NwkSKey[] = "89A9A66A61EBB9D1895E1C240EF0702A";
const char AppSKey[] = "63B2F3FB4A78EBE18CD761D2493E6609";

SX1276 radio = new Module(RFM95_CS, RFM95_INT, RFM95_RST);
LoRaWANNode node(&radio, &Region);

char messageBuffer[64];
int LORA_SEND_TIME = 10; // Set Sleep Time to 10 sec -> 10 * 1000 * 1000 us
/*
Init Board
  |
  V
RGB -> White
  |
  V
Send Uplink Sensor Data
  |
  V
Wait for Downlink
  |
  V
If have downlink -> Set RGB to Blue, Set ON - OFF Light
  |
  V
RGB -> OFF
  |
  V
Sleep
*/
void setup() {
  SPI.begin(10, 4, 5);
  pinInit();
  rgbLedWrite(NEO_PIXEL, 100, 100, 100); 
  pinMode(HOLD, OUTPUT);

  while (radio.begin());
  radio.setSpreadingFactor(10);
  radio.setBandwidth(125.0);

  node.beginABP(DevAddr, NULL, NULL, hexStringToBytes(NwkSKey).data(), hexStringToBytes(AppSKey).data());             // Set Key for Node
  node.activateABP();
  node.setDeviceStatus(map(getBattery(), 0, 100, 0, 255));
  snprintf(messageBuffer, sizeof(messageBuffer), "{\"moisture\":%.2f,\"BATT\":%.2f}", getSensor(true), getBattery()); // Create Message
  -----------------------
  getSensor() - read WaterMark sensor with Raw ADC
  getSensor(true) - read WaterMark sensor in Resistance

  getBatter() - read Battery level with Raw ADC
  getBatter(true) - read Battery level in Resistance
  -----------------------
  */
  const char* message = messageBuffer;
  uint8_t downlinkBuffer[64];
  size_t downlinkLength = 0;
  int16_t state = node.sendReceive(message, 1, downlinkBuffer, &downlinkLength, false, NULL, NULL);                   // Send Uplink and Wait for Downlink

  if (downlinkLength > 0) {
    rgbLedWrite(NEO_PIXEL, 0, 100, 100);                                                                              // If Downlink
    int result = HexToStr(downlinkBuffer, downlinkLength).toInt();                                                    // Convert Downlink to Number
    gpio_hold_dis((gpio_num_t)HOLD);
    digitalWrite(HOLD, result);
    gpio_hold_en((gpio_num_t)HOLD);

    delay(100);
  }

  delay(500);
  rgbLedWrite(NEO_PIXEL, 0, 0, 0);
  esp_sleep_enable_timer_wakeup(LORA_SEND_TIME * 1000 * 1000);                                                        // Sleep
  esp_deep_sleep_start();
}

void loop() {
}
