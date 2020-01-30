1. #include "mbed_events.h"
2. #include <stdio.h>
3. 
4. int main() {
5.     // creates a queue with the default size
6.     EventQueue queue;
7. 
8.     // events are simple callbacks
9.     queue.call(printf, "called immediately\n");  // [1]
10.    queue.call_in(2000, printf, "called in 2 seconds\n");  // [2]
11.    queue.call_every(1000, printf, "called every 1 seconds\n"); // [3]
12. 
13.    // events are executed by the dispatch method
14.    queue.dispatch();
15. }