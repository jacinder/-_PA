#include "mbed.h"

DigitalOut rled(D2);
DigitalOut gled(D3);
DigitalOut yled(D4);


int main(){
    int count = 0;
    while(true){
        if(count % 4 ==0){
            gled = !gled;
        }
        if(count % 2 ==0){
            yled = !yled;
        }
        rled = !rled;
        thread_sleep_for(500);
        count++;
    }
}
