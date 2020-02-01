// IR transceivers
// There are 6 IR LEDs - one for each face

// IMPORTANT: The design puts these cathodes on PORTC and the top 2 bits of PORC are unused
// If these cathodes are moved to a different port, or if the upper bits of PORTC are used,
// then this bits must be masked in ir_test_and_charge() in ir.cpp.

#define IR_CATHODE_PORT PORTC
#define IR_CATHODE_DDR  DDRC
#define IR_CATHODE_PIN  PINC

#define IR_ANODE_PORT PORTB
#define IR_ANODE_DDR  DDRB
#define IR_ANODE_PIN  PINB


// CONSTRAINTS:
// Note that all IR anodes must be on same port, as do all IR cathodes.
// Cathodes must have pin change interrupt
//
// Each anode must be on the same bit as the corresponding anode. (this could be relaxed with extra code)

// All of the 6 GPIO bits used by IR pins. Also assumes these are the same bits in the pin change mask register.

#define IR_BITS     (_BV( 0 )|_BV( 1 )|_BV( 2 )|_BV( 3 )|_BV( 4 )|_BV( 5 ))

// IR pin change interrupts are unused so far, but we will want them for waking from sleep soon...
// TODO: Wake on IR change.

// We want a pin change interrupt on the CATHODES since these will get charged up
// and then exposure will make them go low.
// PORTC is connected to the cathodes, and they are on PCINT0-PCINT5
// which is controlled by PCIE0

/*
    PCICR
    Bit 1 – PCIE1:?Pin Change Interrupt Enable 1
    When the PCIE1 bit is set and the I-bit in the Status Register (SREG) is set, pin change interrupt 1 is
    enabled. Any change on any enabled PCINT[14:8] pin will cause an interrupt. The corresponding interrupt
    of Pin Change Interrupt Request is executed from the PCI1 Interrupt Vector. PCINT[14:8] pins are
    enabled individually by the PCMSK1 Register.
*/

/*
    PCMSK1
    Bits 0, 1, 2, 3, 4, 5, 6 – PCINT8, PCINT9, PCINT10, PCINT11, PCINT12, PCINT13, PCINT14:?Pin
    Change Enable Mask
    Each PCINT[15:8]-bit selects whether pin change interrupt is enabled on the corresponding I/O pin. If
    PCINT[15:8] is set and the PCIE1 bit in PCICR is set, pin change interrupt is enabled on the
    corresponding I/O pin. If PCINT[15:8] is cleared, pin change interrupt on the corresponding I/O pin is
    disabled.
*/


#define IR_PCI_BIT      PCIE1            // Set this bit in PCICR to enable pin change INT on pins PCINT8-14 - the cathode pins on PORTC
#define IR_ISR          PCINT1_vect      // The vector called when pin change happens on cathode pins
#define IR_INT_MASK_REG PCMSK1           // Each bit here corresponds to 1 cathode pin

// From ir.h

#define IR_CHARGE_TIME_US  2         // How long to reverse charge the LED


