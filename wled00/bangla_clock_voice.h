#ifndef BANGLA_CLOCK_VOICE_H
#define BANGLA_CLOCK_VOICE_H

#include <HardwareSerial.h>
#include <DFRobotDFPlayerMini.h>

#define DF_RX 16  // DFPlayer TX to ESP32 RX
#define DF_TX 17  // DFPlayer RX to ESP32 TX

#define AM_LED_PIN  18
#define PM_LED_PIN  19

HardwareSerial dfSerial(1);
DFRobotDFPlayerMini mp3;

void initBanglaVoice() {
  dfSerial.begin(9600, SERIAL_8N1, DF_RX, DF_TX);
  if (!mp3.begin(dfSerial)) {
    Serial.println("DFPlayer Mini not responding!");
    while (1);
  }
  mp3.volume(25);  // Set volume

  // Setup AM/PM LED pins
  pinMode(AM_LED_PIN, OUTPUT);
  pinMode(PM_LED_PIN, OUTPUT);
}

// Play 12h hour-based voice from 24h format
void playHourVoice12AMPM(int hour24) {
  if (hour24 == 0) {
    mp3.play(24);  // 12 AM
  } else if (hour24 >= 1 && hour24 <= 23) {
    mp3.play(hour24);  // 001–023
  }
}

// Turn on AM or PM LED
void updateAMPMIndicator(int hour24) {
  if (hour24 < 12) {
    digitalWrite(AM_LED_PIN, HIGH);
    digitalWrite(PM_LED_PIN, LOW);
  } else {
    digitalWrite(AM_LED_PIN, LOW);
    digitalWrite(PM_LED_PIN, HIGH);
  }
}
#endif
