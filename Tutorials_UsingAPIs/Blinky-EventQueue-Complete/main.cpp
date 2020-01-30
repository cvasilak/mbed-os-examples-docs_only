#include "mbed.h"

DigitalOut led1(LED1);
InterruptIn sw(USER_BUTTON);
EventQueue queue(32 * EVENTS_EVENT_SIZE);
Thread t;

void rise_handler_user_context(void) {
    printf("rise_handler_user_context in context %p\r\n", osThreadGetId());
    printf("Blink! LED1 is now %d\r\n", led1.read());
}

void fall_handler_user_context(void) {
    printf("fall_handler_user_context in context %p\r\n", osThreadGetId());
    printf("Blink! LED1 is now %d\r\n", led1.read());
}

void rise_handler(void) {
    // Execute the time critical part first
    led1 = !led1;
    // The rest can execute later in user context (and can contain code that's not interrupt safe).
    // We use the 'queue.call' function to add an event (the call to 'rise_handler_user_context') to the queue.
    queue.call(rise_handler_user_context);
}

void fall_handler(void) {
    // Execute the time critical part first
    led1 = !led1;
    // The rest can execute later in user context (and can contain code that's not interrupt safe).
    // We use the 'queue.call' function to add an event (the call to 'fall_handler_user_context') to the queue.
    queue.call(fall_handler_user_context);
}

int main() {
    // Start the event queue
    t.start(callback(&queue, &EventQueue::dispatch_forever));  // [1]
    printf("Starting in context %p\r\n", osThreadGetId());
    // The 'rise' handler will execute in interrupt context  // [2]
    sw.rise(rise_handler);
    // The 'fall' handler will execute in interrupt context
    sw.fall(fall_handler);  // [3]
}