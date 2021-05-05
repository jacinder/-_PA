#include "mbed.h"

PortOut led(PortB, 0x38);
InterruptIn button(PC_13);
int rRate = 1, gRate = 2, yRate = 4;
int rLed = 1, gLed = 1, yLed = 1;

void button_pressed(){
    int buf = rRate;
    rRate = yRate;
    yRate = gRate;
    gRate = buf;
}

int main(){
    int count = 0;
    int LED_MASK = 0x38;
    button.fall(&button_pressed);
    while(true){
        if(count % rRate ==0){
            if(rLed == 1){
                LED_MASK -= 8;
                rLed = 0;
            }
            else{
                LED_MASK += 8;
                rLed = 1;
            }
        }
        if(count % gRate ==0){
            if(gLed == 1){
                LED_MASK -= 32;
                gLed = 0;
            }
            else{
                LED_MASK += 32;
                gLed = 1;
            }
        }
        if(count % yRate ==0){
            if(yLed == 1){
                LED_MASK -= 16;
                yLed = 0;
            }
            else{
                LED_MASK += 16;
                yLed = 1;
            }
        }
        thread_sleep_for(500);
        led = LED_MASK;
        count++;
    }
}
