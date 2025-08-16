# Audio-Control-Car
An AI audio model that can control a car with voice inputs.

🧠 Voice-Controlled Traxxas RC Car
By Neil Savaliya
I am writing this at the time after my final prototype is built. This happened about 1.5 months ago.
Chapter 1
Summer Break, 8th Grade
📖 Story & Motivation
During my summer break of 8th grade, I got a remote control trail car for just $1 from a garage sale.
They had said that the car didn’t work anymore, which was not true. The car didn’t have a power button, but instead required you to remove the cover and plug a cable in to start it. (Video of how to start the car link here.)
So now I had a Traxxas car—fully working. I don’t know its exact model specifications, but it still has a good battery and power.
But, I didn’t like playing with a car using a remote control, because it gets boring after a while. So, I decided to make it run by voice commands.
Now, it is not some big new invention, but it was still a great learning opportunity for me to learn something about my favourite career of Artificial Intelligence.
🧪 Problem Breakdown
There were some steps required to do first before controlling the car with voice. I would first have to find a way to give the car commands electronically from my computer that would be running the AI model.
The way communication worked right now is that the remote used a 2.4GHz protocol to communicate with the car’s ESC. Since I don’t have a RF module, but only an Arduino Uno R3, I would have to find some other way.
I looked more closely at the insides of the remote (Image linked here. This image is from the FCC report, since I already have altered the insides of the remote quite a bit.) and saw that it sent inputs to the MCU of the chip by three potentiometers:
One for steering
One for throttle
One for trim correction
Plus a button for remote and ESC pairing
I decided that the best path to go would be to simulate potentiometer turning and button clicking with an Arduino using its GPIO pins.
🧠 System Design
I did not build the AI model yet, but I knew it will be running on my laptop, so I designed a prototype that would work like this:
Voice Command → Laptop (AI Model) → Serial Communication → Arduino Uno → Simulated Remote Inputs → Car ESC
My laptop would send commands to Arduino via serial, then Arduino would process it and simulate potentiometers and buttons via its GPIO pins. I planned to use PWM to simulate analog signals. Then the remote will send commands to the car.
Of course, my first main goal is to control the car with Arduino first.
⚠️ Voltage Compatibility Issue
There was another problem that came in the way. It was an easy fix, however, if I had not noticed it, then I would’ve had to buy another remote control.
See, the MCU onboard the remote control is a C2640F128RHB. It uses a 3.3V logic level, while Arduino uses 5V.
If I had used Arduino directly, I would have ended up frying the chip.
The problem was an easy fix:
 I just used a 220Ω (R1) and 330Ω (R2) voltage divider to reduce 5V logic to ~3V.
🔌 Circuit & Code
Now I had a circuit ready. (Schematic image linked here. I used tinkercad to make the schematic for me. Tinkercad virtual circuit image linked here. The leds are just the placeholders for what inputs would have been given to remotes. Physical circuit image linked here.)
I made cardboard housing for the PCB (Backside image link here. Frontside image link here.) ,and made a female head out of soda can strips for a quick breadboard prototyping accessible module. I kept the trim potentiometer and EzSet switch to the original circuit since I would rarely need to ever control those with an Arduino. And as we would later find out, that turns out to be a good idea. PCB housing video link here.
Then it was time to code it. The code documentation link is here.
🚀 Reflections
This wasn’t just about making a car move with voice—it was about learning how to reverse-engineer, how to simulate analog signals, how to protect components from voltage mismatch, how to read datasheets, and how to think like an engineer.
It was a small step toward my dream of working in an Artificial Intelligence career, and a reminder that even a $1 garage sale item can become a gateway to something much bigger.

## Collaboration

This repository is intended for documentation purposes only. I am not seeking collaborators at this time. Feel free to explore the content, but please refrain from submitting pull requests or collaboration requests.
