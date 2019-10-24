#include <msp430.h>

int main(void) {
    WDTCTL = WDTPW + WDTHOLD;               // Stop watchdog timer
    P1DIR = BIT0;                           // P1.0 output, else input
    P1OUT =  BIT3;                          // P1.3 set, else reset
    P1REN |= BIT3;                          // P1.3 pullup
    P1IE |= BIT3;                           // P1.3 interrupt enabled
    P1IES |= BIT3;                          // P1.3 Hi/lo edge
    P1IFG &= ~BIT3;                         // P1.3 IFG cleared

    __bis_SR_register(LPM4_bits + GIE);     // Enter LPM4 w/interrupt
}

#pragma vector = PORT1_VECTOR
__interrupt void Port_1(void) {
    P1OUT ^= BIT0;                          // P1.0 = toggle
    P1IFG &= ~BIT3;                         // P1.3 IFG cleared
}
