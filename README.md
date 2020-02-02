# bare-metal-ir-demo

Example of how to directly access the [Blink](https://move38.com/collections/blinks) IR LEDs to sense light levels. 

The color on the pixels will blinks to indicate the light level on each face...

| Color | Light Level |
|-|-|
| Blue | Dark |
| Green | Dim |
| Red | Normal |
| White | Bright |

Remember that these are Infrared LEDs (IR), so they will be much more sensitive to halogen and incandescent lights than LED and florescent ones. The sun is also a very bright IR source... but can be blocked by thermally coated windows! 

Also remember that IR light can reflect and transmit differently than visible light. A wall might look white but absorb IR, while a piece of black plastic might be clear to IR.  

Your blink is like a mini thermal camera!

## How the IR LEDs work

IR LEDs are like little capacitors, except that they discharge when lights hits them. The brighter the light, the faster they discharge. 

By charging an IR LED up and then counting how long it takes to discharge, we can measure how much light is hitting it. 

## How it works

We periodically charge up all the IR LEDs and then we start counting. 

Initially, we set all the pixels to WHITE. 

After 10ms, we check which IR LEDs nes are still charged and set those ones to RED. 

After an additional 20ms, we check again and set any that are still charged to GREEN.

After a final 30ms, we check one last time and set any that are still charged to BLUE.

See how that works?

If an IR LED is getting lots of light, then it will discharge very quickly and will already be discharged by the time we do our first check, so it will just stay WHITE.   

If an IR LED is not getting any light hitting it (dark), then it will not discharge and will still be charged when we do the final check, and so will get set to BLUE. 

Neat, right?

## Why does it blink so?

Normally the BlinkOS is accessing these IR LEDs hundreds of times per second to maintain communications. If we let it keep doing that, then it would be changing and discharging the LEDs while we are trying to get our light readings. 

To stop the BlinkBIOS from accessing the IR LEDs, we turn off interrupts. This prevents the BlinkBIOS from doing *anything* so we have a chance do our IR business uninterrupted. 

But when we turn off interrupts we are also stopping the BlinkBIOS from refreshing the RGB pixel LEDs. This why the pixels go dark while we are taking our samples. 

Is it possible to do IR samples while still having the RGB LEDs stay lit? Sure, anything is possible if we want to talk directly to the hardware, but this example is meant to be the simplest possible approach. Other approaches would take much more work.

You can, however, minimize the time the pixels are off by picking a higher threshold of light you want to sense. It takes less time to detect a bright light source, so if you are OK with only seeing bright light then you can sample for a much shorter time. For example, I can sense the light from a 60 watt incandescent bulb 10 feet away in like 5ms.  

## Fun tricks to impress your friends	

Play target practice by shooting at your blink with a TV remote controller from across the room. It will turn colors when you hit it!

Make a motion detector by setting up a blink on your desk to point at an incandescent bulb. No one can sneak up on you because the blink will change colors as soon as they break the beam!

Convince your friends you can psychically control your blink by pointing your phone at it and secretly covering and uncovering the IR illuminator with your finger as you make spooky incantations!     
