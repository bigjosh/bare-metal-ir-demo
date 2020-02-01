// Shows different colors base don how much light is hitting the IR LED on each face
// Note uses direct hardware access, not for the faint of heart.
// See README for details!

// We are talking directly to the hardware. so we will need these...

#include <avr/io.h>
#include <util/delay.h>
#include "bare-metal-ir.h"

void setup() {
  // No setup needed for this simple example!  
}

// Charge up all 6 IR LEDs

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

// Scan though the 6 IR LEDs and set the coresponding RGB pixel to `color` if the IR LED is still charged

void set_color_if_ir_led_charged( Color c ) {

    FOREACH_FACE( f ) {

      if ( IR_CATHODE_PIN & _BV( f ) ) {

        setColorOnFace( c  , f );
        
      }
    }

}

// Next time to do a light sample and update the display

Timer nextStep;

void loop() {

  if (nextStep.isExpired()) {

    // Turn off interrupts. This prevents the BlinkBIOS from messing with the IR LED while we 
    // use them, but also stops the RGB pixels from getting refreshed

    asm("cli");

    charge_ir_leds();

    // Any IR LED that see so much light that it discharges before the first time we check
    // will default to WHITE

    setColor( WHITE );


   // Now start checking the see which IR LEDs are still charged at various intervals
   // and update the colors apropriately. 
   // Note that I just guessed at these delays and they seems to work ok,
   // you can make them shorter to make the light thresholds brighter
   
   _delay_ms(10);

   set_color_if_ir_led_charged( RED );
  
   _delay_ms(20);

   set_color_if_ir_led_charged( GREEN );

   _delay_ms(30);

   set_color_if_ir_led_charged( BLUE );


   // And turn interrupts back on        
    asm("sei");
    
    nextStep.set(100);     // Leave the RGB pixels on for 100ms so the user can see the colors before starting our next sample round. 

  }

}
