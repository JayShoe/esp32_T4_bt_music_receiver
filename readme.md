# esp32_T4_bt_music_receiver
 
A simple hardware test. The test accepts USB audio, Bluetooth, and line-in from the audio shield and sends it out the audio shield. 
 - USB Audio Input and Output
 - STGL5000 (I2S) Input and Output
 - ESP32 Bluetooth Sink Input

![Breadboard Image](image.png?raw=true "Title")

The T4 code is credited to Alex6679
https://github.com/alex6679/ESP32_I2S_Teensy4

The ESP code is credited to pschatzmann
https://github.com/pschatzmann/ESP32-A2DP

Set Arduino to USB Type: Serial + Midi + Audio


# Connections
The connections between the two boards are customizable on the ESP32 side. But this example relies on the second SAI (I2S2) port on the Teensy. 
```
#define CONFIG_EXAMPLE_I2S_BCK_PIN 26 // (A0 on huzzah32, BCLK2 pin 4 on T4.1)
#define CONFIG_EXAMPLE_I2S_LRCK_PIN 25 // (A1 on huzzah32, LRCK2 pin 3 on T4.1)
#define CONFIG_EXAMPLE_I2S_DATA_PIN 21 // (21 on huzzah32, IN2 pin 5 on T4.1)
// T4.1 GND is connected to huzzah32 GND (down 4 on left side)
```
