# SPCN Bracelet Prop
A prop made for Samahang Pilipino Cultural Night at UCLA.
The prop was modeled in CAD, and then fitted with an ATTiny85, CR2032, Shift Register, single button interaction, and a multiplexed 4x4 grid of LEDs in the colors of the Filipino Flag.

## The Code
The code is organized in a way which takes advantage of persistence of vision.
First I create a new Frame object, which holds the information of which LEDs should be on in that current frame. I call those LEDs segments within the class.

I then hold a bunch of frames inside a sequenceAnimation. This class holds an array of frames and information and functions for when each frame should be displayed. The FPS (Frames Per Second) can be modified with this class.
The ledGrid class connects it all together. This class reads the information from the sequenceAnimation class, which reads information from the frame class to return a byte which the ledGrid class shifts out to the shiftRegister.

## The Code (In-Depth)
When the code is run, the frame class will always return the segment which needs to be displayed (just one LED), and it is incremented in a loop at a pace so quick that it appears that all the LEDs are on. The sequence class manages which frames are displayed at a given time, which results in different LEDs that are returned.

The Frame class is also the class which converts High Level user input into low level byte code (literally, it generates a byte from coordinates). This byte holds the 8bits that correspond to the shift register's logic signals.

## CAD
Modeling the part took quite a few iterations. The first model was circular which fit just two leds and a button which blinked. The second iteration was square, with a 4x4 grid array of LEDs that were soldered on wires, with a slap bracelet for ease of use. The final iteration contained a self soldered circuit board with a full enclosure and velcro (because it flew off the first time).

The models were tailored to the liking of the costume designer. The final design was printed in black on a Zortrax M200 with a laser cut circular piece of acrylic as a top cover.

## Notes
While the CAD models are covered by creative commons, the firmware is licensed under GPL.

![Final Product](https://github.com/XDleader555/cad_models/raw/main/spcn_bracelet_prop/bracelet.jpg)