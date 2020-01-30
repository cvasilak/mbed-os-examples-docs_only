#include "mbed.h"

int main()
{
    // Initialize the digital pin LED1 as an output
    DigitalOut led(LED1);  // [1]
    
    while (true) { // [2]
        led = !led;
        printf("Blink! LED1 is now %d\r\n", led.read());
    }
}