
// We are talking directly to the hardware. so we will need these...

#include <avr/io.h>
#include <util/delay.h>
#include "bare-metal-ir.h"

void setup() {
  // No setup needed for this simple example!  
}


void charge_ir_leds() {

    PINC = 0;

    IR_CATHODE_PIN =  IR_BITS;       // This enables pull-ups on charge pins. If we set the DDR first, then we would drive the low pins to ground.
                                     // REMEBER: Writing a 1 to a PIN register actually toggles the PORT bit!

    IR_CATHODE_DDR =  IR_BITS;       // This will drive the charge pins high

    // Empirically this is how long it takes to charge

    _delay_us( IR_CHARGE_TIME_US );     // Recharge the LEDs that just fired so they are ready to see the next pulse

    // Stop charging LED cathode pins

    IR_CATHODE_DDR = 0;                 // Back to the way we started, charge pins now input, but still pulled-up

    IR_CATHODE_PIN = IR_BITS;           // toggle pull-ups off, now cathodes pure inputs
                                        // REMEBER: Writing a 1 to a PIN register actually toggles the PORT bit!  
}

void set_color_if_ir_led_charged( Color c ) {

    FOREACH_FACE( f ) {

      if ( IR_CATHODE_PIN & _BV( f ) ) {

        setColorOnFace( c  , f );
        
      }
    }

}


Timer nextStep;

void loop() {

  if (nextStep.isExpired()) {

    asm("cli");

    charge_ir_leds();

     _delay_ms(10);

     set_color_if_ir_led_charged( RED );
    
     _delay_ms(20);

     set_color_if_ir_led_charged( GREEN );

     _delay_ms(30);

     set_color_if_ir_led_charged( BLUE );

        
    asm("sei");
    
    nextStep.set(100);     // Step to (slightly) different color 100 times per second - whole cycle will take 255 steps *10ms = ~2.5 seconds. 

  }

}
