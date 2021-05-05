#include "mbed.h"
// toggle the red LED when a user button is pressed.
// blinking green LED at a rate of 1sec

InterruptIn button(PC_13);
DigitalOut gled(D3);
DigitalOut rled(D2);

void button_pressed(void){
    rled = !rled;
}
int main(){
    button.fall(&button_pressed);
    while(true){
        gled = !gled;
        thread_sleep_for(500);
    }
}
