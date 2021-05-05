#include "mbed.h"
DigitalOut led2(LED2);
DigitalIn button(USER_BUTTON);

int main()
{
    int interval = 500;
    
    while(true){
        if(button == 0){
            interval = interval << 1;
            if(interval > 4000)
                interval = 125;
        }
        led2 = !led2;
        thread_sleep_for(interval);

    
    }
}
