# bare-metal-ir-demo

Example of how to directly access the Blink IR LEDs to sense light levels. 

The color on the pixels will blinks to indicate the light level on each face...

| Color | Light Level |
|-|-|
| BLUE | Dark |
| Green | Twilight |
| Red | Light |


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