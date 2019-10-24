#include <msp430.h>

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer
    P1DIR = BIT0;                           // P1.0 output, else input
    P1OUT =  BIT1;                          // P1.3 set, else reset
    P1REN |= BIT1;                          // P1.3 pullup
    P1IE |= BIT1;                           // P1.3 interrupt enabled
    P1IES |= BIT1;                          // P1.3 Hi/lo edge
    P1IFG &= ~BIT1;                         // P1.3 IFG cleared
    PM5CTL0 &= ~LOCKLPM5;                   // Disable the GPIO power-on default high-impedance mode

    __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4 w/interrupt
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) {
    P1OUT ^= BIT0;                          // P1.0 = toggle
    P1IFG &= ~BIT1;                         // P1.3 IFG cleared
}
