//
// ticker.cpp와 같은 기능을 수행하되, on/off주기가 완료된 다음 점멸주기가 바뀌어야 한다.
//
#include "mbed.h"

DigitalOut led2(PA_5);
InterruptIn button(PC_13);
Ticker led2_ticker;
Timer t;
Timeout timeout;
float interval = 0.5;
int timeout_flag, interval_change;
int ticker_log, current, left;

void ticker_cb(void){
    led2 = !led2;
    ticker_log=chrono::duration_cast<chrono::seconds>(t.elapsed_time()).count();
}
void timeout_cb(void){
    // change interval.
    led2_ticker.detach();
    interval = interval * 2;
    if(interval > 4){
        interval = 0.125;
    }
    led2_ticker.attach(&ticker_cb, interval);
    timeout_flag = 1;
}
void button_onpressed_cb(void){
    current = chrono::duration_cast<chrono::seconds>(t.elapsed_time()).count();
    left = interval - (ticker_log-current);
    interval_change = 1;
    if (led2 == 0){
        timeout.attach(&timeout_cb, left);
    }
    else{
        timeout.attach(&timeout_cb, left+interval);
    }
}

int main(){
    button.mode(PullUp);
    button.fall(&button_onpressed_cb); //When button is falled, call 'button_onpressed_cb'
    led2_ticker.attach(&ticker_cb, interval); //interval을 주기로 'timeout_cb'가 실행된다.
    t.start();
    while(1){
        if(timeout_flag){
            timeout.detach();
            timeout_flag = 0;
        }
        if(interval_change){
            printf("ticker_log: %d, current: %d, left: %d\n",ticker_log, current, left);
            printf("interval has changed\n");
            printf("interval:%d\n\n",interval);
            interval_change = 0;
        }
    }
}
