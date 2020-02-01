
// We are talking directly to the hardware. so we will need these...

#include <avr/io.h>
#include <util/delay.h>
#include "bare-metal-ir.h"

void setup() {
  // No setup needed for this simple example!  
}


void charge_ir_leds() {

    PINC = 0;

    IR_CATHODE_PIN =  charge_bits;       // This enables pull-ups on charge pins. If we set the DDR first, then we would drive the low pins to ground.
                                         // REMEBER: Writing a 1 to a PIN register actually toggles the PORT bit!

    IR_CATHODE_DDR =  charge_bits;       // This will drive the charge pins high

    // Empirically this is how long it takes to charge

    _delay_us( IR_CHARGE_TIME_US );     // Recharge the LEDs that just fired so they are ready to see the next pulse

    // Stop charging LED cathode pins

    IR_CATHODE_DDR = 0;                 // Back to the way we started, charge pins now input, but still pulled-up

    IR_CATHODE_PIN = charge_bits;       // toggle pull-ups off, now cathodes pure inputs
                                        // REMEBER: Writing a 1 to a PIN register actually toggles the PORT bit!  
}

byte hue=0;

Timer nextStep;

void loop() {

  if (nextStep.isExpired()) {

    // Spin the hue while keeping color saturation and brightness at max  
    setColor( makeColorHSB( hue , 255 , 255 ) );
    
    // Becuase we are using an 8-bit byte for the `hue` variable, 
    // this will automatically roll over from 255 back down to 0  
    // (255 is 11111111 in binary, and 11111111 + 00000001 = 00000000)
    hue++;      

    nextStep.set(10);     // Step to (slightly) different color 100 times per second - whole cycle will take 255 steps *10ms = ~2.5 seconds. 

  }

}
