/*
 * A simple hardware test. The test accepts USB audio, Bluetooth, and line-in from the audio shield and sends it out the audio shield. 
 * 
 *  - USB Audio Input and Output
 *  - STGL5000 (I2S) Input and Output
 *  - ESP32 Bluetooth Sink Input
 *  
 *  The T4 code is credited to Alex6679
 *  https://github.com/alex6679/ESP32_I2S_Teensy4
 *  
 *  The ESP code is credited to pschatzmann
 *  https://github.com/pschatzmann/ESP32-A2DP
 *  
 *  Set Arduino to USB Type: Serial + Midi + Audio
 *  
 * This example code is in the public domain.
 */

#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>

#include "async_input.h"
#include "input_i2s2_16bit.h"
#include "output_i2s2_16bit.h"

#include "plotter.h"
Plotter plotter(8);

//i2sSlaveInput parameters
 bool dither = false;
 bool noiseshaping = false;
 float attenuation = 100;
 int32_t minHalfFilterLength=80;
 int32_t maxHalfFilterLength=1;
 AsyncAudioInput<AsyncAudioInputI2S2_16bitslave> i2sSlaveInput(dither, noiseshaping, attenuation, minHalfFilterLength, maxHalfFilterLength);
//AsyncAudioInput<AsyncAudioInputI2S2_16bitslave> i2sSlaveInput;

AudioInputI2S            i2s1;
AudioOutputI2S           i2s2;
AudioInputUSB            usb1;
AudioOutputUSB           usb2;
AudioMixer4              mixer1;
AudioConnection          patchCord1(i2sSlaveInput, 0, mixer1, 0);
AudioConnection          patchCord2(i2sSlaveInput, 1, mixer1, 1);
AudioConnection          patchCord3(usb1, 0, mixer1, 2);
AudioConnection          patchCord4(usb1, 1, mixer1, 3);
AudioConnection          patchCord5(mixer1, 0, plotter, 0);
AudioConnection          patchCord6(mixer1, 1, plotter, 1);
AudioConnection          patchCord7(mixer1, 0, usb2, 0);
AudioConnection          patchCord8(mixer1, 1, usb2, 1);
AudioConnection          patchCord9(mixer1, 0, i2s2, 0);
AudioConnection          patchCord10(mixer1, 1, i2s2, 1);
AudioControlSGTL5000     sgtl5000_1;     //xy=302,184


const int myInput = AUDIO_INPUT_LINEIN;
//const int myInput = AUDIO_INPUT_MIC;


void setup() {
  // Audio connections require memory to work.  For more
  // detailed information, see the MemoryAndCpuUsage example
  AudioMemory(12);

  // Enable the audio shield, select input, and enable output
  sgtl5000_1.enable();
  sgtl5000_1.inputSelect(myInput);
  sgtl5000_1.volume(0.5);
  plotter.activate(true);
}

elapsedMillis volmsec=0;

void loop() {
  // every 50 ms, adjust the volume
  if (volmsec > 50) {
    float vol = analogRead(15);
    vol = vol / 1023.0;
    //audioShield.volume(vol); // <-- uncomment if you have the optional
    volmsec = 0;               //     volume pot on your audio shield
  }
}
