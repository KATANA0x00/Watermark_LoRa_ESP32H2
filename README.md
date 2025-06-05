# Watermark_LoRa_ESP32H2

## **Description**
LoRa node for **_Watermark_** Sensor using **_ESP32H2_**.

## **Overview**
System is automatic reading value from **_Watermark_** sensor and sending to gateway with period time that setting or command, Default of code is **1 minute period**. With can change period of sending time from downlink message.

**START** --> **Read Sensor Value** --> **Send Value to Gateway** --> **check downlink message** --> **Sleep**

## **How To**
**File Declare**\
**> Watermark_LoRa_ESP32H2.ino :** Main Code and Where to setting **Address** of LoRa Device.\
**> BoardCinfig.h :** Configuration file for board _**(noting need to do with this But need it in project)**_.\
**> Libraries Folder :** Libraies that using in project.

**Setting Folder**\
Watermark_LoRa_ESP32H2\
&nbsp;&nbsp;|--Watermark_LoRa_ESP32.ino\
&nbsp;&nbsp;|--BoardConfig.h

**OR**

1. Git Pull
2. open **Watemark_LoRa_ESP32H2.ino** with ArduinoIDE
3. Copy RadioLib libraies to libraies Folder
4. Edit address of device

**Example**

IF
``` cpp
DevAddr = 65F5EAC1
Network Key = E4246B5003F2C4CD0A759FE13848FCB9
    App Key = B830B7AA0C4229D80EFD7DDEA913B026
```
FROM ( Line 10-12 )
``` cpp
uint32_t DevAddr = 0x--------;
uint8_t NwkSKey[] = { 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x-- };
uint8_t AppSKey[] = { 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x--, 0x-- };
```
TO
``` cpp
uint32_t DevAddr = 0x65F5EAC1;
uint8_t NwkSKey[] = { 0xE4, 0x24, 0x6B, 0x50, 0x03, 0xF2, 0xC4, 0xCD, 0x0A, 0x75, 0x9F, 0xE1, 0x38, 0x48, 0xFC, 0xB9 };
uint8_t AppSKey[] = { 0xB8, 0x30, 0xB7, 0xAA, 0x0C, 0x42, 0x29, 0xD8, 0x0E, 0xFD, 0x7D, 0xDE, 0xA9, 0x13, 0xB0, 0x26 };
```
BOARD SELECT\
Goto > Tools > Board > esp32 > ESP32H2 Dev Module\
for board setting before upload\
Goto > Tools
- USB CDC Boot: **"Disabled"**
- Core Debug Level: **"None"**
- Erase All Flash Before Sketch Upload: **"Disabled"**
- Flash Frequency: **"64MHz"**
- Flash Mode: **"QIO"**
- Flash Size: **"4MB (32Mb)"**
- JTAG Adapter: **"Disabled"**
- Partition Scheme: **"Default 4MB with spiffs (1.2MB APP/1.5MB SPIFFS)"**
- Upload Speed: **"9216000"**
- Zigbee Mode: **"Disabled"**
