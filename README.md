# Watermark_LoRa_ESP32H2

## **Description**
LoRa node for **_Watermark_** Sensor using **_ESP32H2_**.

## **Overview**
System is automatic reading value from **_Watermark_** sensor and sending to gateway with period time that setting or command, Default of code is **1 minute period**. With can change period of sending time from downlink message.

**START** --> **Read Sensor Value** --> **Send Valur to Gatway** --> **check downlink message** --> **Sleep**

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
3. Install RadioLib libraies
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
BOARD SELECT
Goto > Tools > Board > esp32 > ESP32H2 Dev Module
for board setting before upload
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

# **Address Table**
Name | DevAddr | NwkSKey | AppSKey
---- | ------- | ------- | -------
Node 001 | 65F5EAC1 | E4246B5003F2C4CD0A759FE13848FCB9 | B830B7AA0C4229D80EFD7DDEA913B026
Node 002 | 6BD97D68 | C49DF125F32BD686CEE6AA5F7BA8E169 | 5CC78F56533D99F07B7226EA7111E7C3
Node 003 | 9D8B7452 | 0FC6D9DCE9F92971B5A98B0351C560C4 | 7F27AAF89D173CF2FC96B1E5C53459B8
Node 004 | C6764227 | 6FB096DFFF98AA7DD192E543C8DB3AC7 | A80C7FB2E953BCADF1629CBA15933904
Node 005 | EA52B415 | 62E8BA112614BCCC4E51B37AF5050695 | 692077D123D1D34A4856E6D2B30F1E2C