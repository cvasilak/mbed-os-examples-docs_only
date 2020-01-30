#include "mbed.h"

// Blinking rate in milliseconds
#define BLINKING_RATE_LED1_MS  500
#define BLINKING_RATE_LED2_MS  1000

DigitalOut led1(LED1);
DigitalOut led2(LED2);
Thread thread;

void led2_thread() {
    while (true) {
        led2 = !led2;
        printf("Blink! LED2 is now %d\r\n", led1.read());
        thread_sleep_for(BLINKING_RATE_LED2_MS);
    }
}
 
int main() {
    thread.start(led2_thread);
    
    while (true) {
        led1 = !led1;
        printf("Blink! LED1 is now %d\r\n", led1.read());
        thread_sleep_for(BLINKING_RATE_LED1_MS);
    }
}
