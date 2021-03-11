# Blinking LED
 This repository contains a design of an embedded computer centered around the ATMega32 microcontroller.

Description
------
This is a starter project that help me get introduced to Atmel Studio.

| Input    | Output    |
| ---------|:---------:|
| Button   | LED       |  

The LED blinks on and off at a rate of 500ms on and 500ms off whenever the button is pressed.

Components Used
------
| Qty    | Item    | Part    | Digikey Part # | Link    | 
|:------:|:-------:|:-------:|:--------------:|:-------:|
| 1x     | Microcontroller | Atmega32-16PU | ATMEGA32-16PU-ND| [Digikey Link](https://www.digikey.com/en/products/detail/microchip-technology/ATMEGA32-16PU/739771?s=N4IgTCBcDaIIIBUCyBRA4nAzGAtARgDYAFAVRwDkAREAXQF8g) |
| 1x     | Programmer | ATATMEL-ICE-BASIC | ATATMEL-ICE-BASIC-ND | [Digikey Link](https://www.digikey.com/en/products/detail/microchip-technology/ATATMEL-ICE-BASIC/4753381?s=N4IgTCBcDaIIIBVEFkCiAZAtASQMKswCE4BlPTAOQBEQBdAXyA) | 
| 1x     | LED | SSL-LX5093GD-5V | 67-1100-ND | [Digikey Link](https://www.digikey.com/en/products/detail/lumex-opto-components-inc/SSL-LX5093GD-5V/270898?s=N4IgTCBcDaIGwHYC0BGFAGdSByAREAugL5A) |
| 1x     | Button | FSM8JRT | 450-2039-1-ND | [Digikey Link](https://www.digikey.com/en/products/detail/te-connectivity-alcoswitch-switches/FSM8JRT/4146916?s=N4IgTCBcDaICwFYAMBaMSDMBOFBGFAcgCIgC6AvkA) |
| 1x     | 8MHz Crystal | ATS08A | CTX406-ND | [Digikey Link](https://www.digikey.com/en/products/detail/cts-frequency-controls/ATS08A/280186?s=N4IgTCBcDaIMIBUAaAWADANgLQDkAiIAugL5A) |
| 1x     | 5V Voltage Regulator | MC7805CT-BP | MC7805CT-BPMS-ND | [Digikey Link](https://www.digikey.com/en/products/detail/micro-commercial-co/MC7805CT-BP/804682?s=N4IgTCBcDaILIGEDsAOADAVgQFQLQCEAFOAZVwDkAREAXQF8g) |
| 1x     | 0.1uF Capacitor | T350A104K035AT | 399-3526-ND | [Digikey Link](https://www.digikey.com/en/products/detail/kemet/T350A104K035AT/818388?s=N4IgTCBcDaIMwE4EFo4FYwDZkDkAiIAugL5A) |
| 1x     | 10k Resistor | CF14JT10K0 | CF14JT10K0CT-ND | [Digikey Link](https://www.digikey.com/en/products/detail/stackpole-electronics-inc/CF14JT10K0/1741265?s=N4IgTCBcDaIMIDECMAWAUgFSQBgNLbgwFoA5AERAF0BfIA) |
| 1x     | 9V Battery | 6LF22XWA/B | P687-ND | [Digikey Link](https://www.digikey.com/en/products/detail/panasonic-bsg/6LF22XWA-B/5067196?s=N4IgTCBcDaIAoDYAcB2AtAOQCIgLoF8g) | 
| 1x     | 9V Battery Connector | BS6I | BS6I-ND | [Digikey Link](https://www.digikey.com/en/products/detail/mpd-memory-protection-devices/BS6I/32055?s=N4IgTCBcDaIEIGUBsBJAtAOQCIgLoF8g) |
| 2x     | Breadboard | TW-E41-1020 | 438-1046-ND | [Digikey Link](https://www.digikey.com/en/products/detail/twin-industries/TW-E41-1020/643112?s=N4IgTCBcDaICwGYAcBaAjABjgNhQOQBEQBdAXyA) |

Visuals
------
![Blinking LED Schematics](https://github.com/DarrenLee280/Blinking-LED/blob/main/Pictures/BlinkingLEDSchematics.JPG "Blinking LED Schematics")
__How to connect a ATATMEL ICE to a ATmega32-16PU:__
![ATATMEL ICE Connection to an ATmega32-16PU](https://github.com/DarrenLee280/Blinking-LED/blob/main/Pictures/ATATMEL-ICE-BASIC%20Connector.png "ATATMEL Ice Connection to an Atmega32-16PU")

Initial Setup
------
IMPORTANT!!! Make sure to switch the ATmega32 internal timer to match the 8MHz crystal,

How To: 
1. On Microchip Studio, go to __Tools__ -> __Device Programming__
2. Choose the correct programmer, device, and interface.
3. Click on the __Fuses__ Tab
4. Scroll down to the __LOW.SUT_CKSEL__ section
5. From the Dropdown section, click on __Ext. Crystal/Resonator High Freq.; Start-up time: 16CK + 64 ms EXTHIFXTALRES_16KCK_64MS__
6. Press __Program__

Make sure your __Device Programming__ window looks like this BEFORE pressing __Program__
![Device Programming](https://github.com/DarrenLee280/Blinking-LED/blob/main/Pictures/Device%20Programming.JPG "Device Programming")

Source Code
------
__main.c:__ Contains the code that blinks the LED for 500ms on and off. There is also a function(not used!) that uses instruction timing to wait around 500ms. (NOTE: the instruction timing uses the ATmega32 internal 1MHz clock)

__avr.h:__ Contains the code that deals with bit manipulation. There is also a function declaration for a more accurate wait function

__avr.c:__ Contains the code for the more accurate wait function. (NOTE: this wait function utilizes the 8MHz crystal and remember to adjust the ATmega32 internal clock)

