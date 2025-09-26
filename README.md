# Magic Wand Project
[中文版](/README_CN.md)
## Project Overview
This project is a magic wand controller based on the UNIHIKER K10, including two sets of code for the magic wand (Transmitter) and the magic hat (Receiver). The project integrates machine learning inference functionality, using models trained with EdgeImpulse for gesture recognition.

## File Structure
```
├─Case  # Magic wand casing design files
├─doc   # Training process guidance
│  ├─edgeimpulse config tutorial # EdgeImpulse local forwarding environment configuration
│  ├─magicWond data forward # Data forwarding and model training tutorial
│  └─magicWond press releases # Magic wand press releases
├─resource # Resource files
│  ├─TrasmitterPic # Transmitter SD card files
│  ├─conv.cpp # Replace files in the Arduino library
│  └─depthwise_conv.cpp # Replace files in the Arduino library
├─src
│  ├─Hats # Magic hat project
│  ├─ModelTrain # Model training project
│  └─Wond # Magic wand project
```

## Hardware Requirements
- UNIHIKER K10 development board * 3
- NeoPixel LED strip * 1
- Button * 1

## Software Dependencies
- VSCode/CLion + Platform IO

## Installation Instructions
1. Copy the DFRobot_NeoPixel library, RMT library, and Edge Impulse machine learning inference library (magic-xhl_inferencing) to the Arduino IDE's libraries directory, and configure the UNIHIKER K10 Arduino compilation environment.
2. Open Arduino IDE, create any .ino file, and copy Transmitter.cpp or Receiver.cpp into the .ino file.
3. Copy all .png files from the `resource->TrasmitterPic` folder to an SD card and insert it into the K10 of the magic wand transmitter.

## Usage Instructions
1. Upload the Wond code to the K10 of the magic wand (code is pre-uploaded by default).
2. Upload the Hats code to the K10 of the magic hat, and switch between different hats by commenting/uncommenting the macro definitions at the beginning of the code:
```c++
#define blackHAT
//#define orangeHAT
```
3. Install 3 AA batteries into the hat and a single CR123A battery into the magic wand.
4. Press the button on the magic wand, and within 2 seconds, draw a circle, shake up and down, or shake left and right to control the magic hat:
   - Shake up and down to move the black hat.
   - Shake left and right to move the orange hat.
   - Draw a circle to stop both hats.

## Notes
- The magic wand button originally lacks a pull-down resistor, making it prone to false triggers. During production, a pull-down resistor was manually soldered to the back of the button.
- The P0 pin of the magic wand connects to the LED strip, and the P1 pin connects to the button.
- The magic wand is powered by a single CR123A battery, with a battery life of approximately 3 hours. When transmitting information using the ESPNOW protocol, which consumes significant power, the battery voltage may suddenly drop. A sign of low battery is a sudden white screen reboot when transmitting signals. Replace the battery by opening the magnetic battery compartment at the back.
- The three AA batteries in the magic hat power both the servo motor and the K10 itself. With the screen off, the battery life is approximately 1-2 hours.
- The magic hat is controlled via a relay, with the relay uniformly connected to the P0 pin inside the K10 of the magic hat.
- If you train your own model, you cannot compile the code using Platform IO. This is because EdgeImpulse recently updated the Arduino library format, which now only supports compilation with Arduino IDE.

## Training Website
EdgeImpulse: https://edgeimpulse.com/<br/>
Project Link: https://studio.edgeimpulse.com/studio/587543<br/>

Training Tutorial:
[EdgeImpulse Environment Configuration](doc/edgeimpulseConfigTutorial.md)
[EdgeImpulse Training Tutorial](doc/magicWondDataForward.md)

Training Process:
- To add new gestures later, log in to the EdgeImpulse website and open the project.
- Upload the [ModelTrain](src/ModelTrain/) code to the K10 of the magic wand and open the serial monitor to ensure that the serial output has accelerometer data.
- Configure the EdgeImpulse data upload environment (refer to the [EdgeImpulse Environment Configuration](doc/edgeimpulseConfigTutorial.md) document).
- Select data to upload to the magic-xhl project (refer to the [EdgeImpulse Training Tutorial](doc/magicWondDataForward.md)).
- After exporting the Arduino library, use the [conv.cpp](resource/conv.cpp) and [depthwise_conv.cpp](resource/depthwise_conv.cpp) files here to replace the files with the same names in the `magic-xhl_inferencing\src\edge-impulse-sdk\tensorflow\lite\micro\kernels` folder of the exported Arduino library.
- Upload [Wond](src/Wond/) to the UNIHIKER K10 of the magic wand.