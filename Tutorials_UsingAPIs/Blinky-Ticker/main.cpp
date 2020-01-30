#include "mbed.h"

Ticker flipper;
DigitalOut led1(LED1);
 
void flip() {  // [1]
    led1 = !led1;
    //printf("Blink! LED1 is now %d\r\n", led1.read());  // [2]
}
 
int main() {
    led1 = 1;
    flipper.attach(&flip, 1.0); // the address of the function to be attached (flip) and the interval (1 seconds)
}