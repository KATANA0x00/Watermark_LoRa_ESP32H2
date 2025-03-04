#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>

#define BATTERY_V_PIN   1

#define BATTERY_VOLTAGE 6.0
#define RESISTOR_1      100000.0
#define RESISTOR_2      10000.0
#define RESISTOR_RATIO  RESISTOR_2 / ( RESISTOR_1 + RESISTOR_2 )
#define ADC_MARK        int(((BATTERY_VOLTAGE * RESISTOR_RATIO) / 3.3) * 4095)

#define SENSOR_Trigger  0
#define SENSOR_RAW_PIN  2

#define R_DEVIDER       10000.0

#define NEO_PIXEL       8

void pinInit() {
  pinMode( BATTERY_V_PIN ,  INPUT );
  pinMode( SENSOR_Trigger, OUTPUT );
  pinMode( SENSOR_RAW_PIN,  INPUT );
  pinMode( NEO_PIXEL     , OUTPUT );
}

float RS_calculate(int RAW_Val) {
  float voltage = ((RAW_Val * 1.0) / 4095.0) * 3.3 ;
  float Resistance = R_DEVIDER * (( 3.3 /  voltage) - 1);

  return isinf(Resistance) ? -1 : Resistance;
}

float getBattery(bool convert_flag = false) {
  int Batt_ADC = analogRead(BATTERY_V_PIN);

  if(convert_flag) { return Batt_ADC; }
  else { return constrain((map(Batt_ADC,0,ADC_MARK,0,10000) / 100),0,100); }
}

float getSensor(bool convert_flag = false) {
  int val_raw = 0;
  for(int count=0 ; count<5 ; count++){
    digitalWrite(SENSOR_Trigger, HIGH);
    delayMicroseconds(100);
    val_raw += analogRead(SENSOR_RAW_PIN);
    digitalWrite(SENSOR_Trigger, LOW);
    delayMicroseconds(200);
  }
  val_raw /= 5;

  if(convert_flag) { return val_raw * 1.0; }
  else { return RS_calculate(val_raw); }
}

#endif