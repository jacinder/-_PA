//
// 한동대학교 로고송을 피에조 부저를 이용하여 음악을 생성하여라
//
#include "mbed.h"
PwmOut buzzer(PB_3);
float freq[]={329.63, 329.63, 349.23, 392.00, 440.00, 493.88, 587.33, 523.25, 523.25, 493.88, 523.25, 392.00, 392.00, 392.00, 392.00, 440.00, 440.00, 392.00, 349.23, 329.63, 293.66, 329.63, 329.63, 349.23, 392.00, 392.00, 440.00, 493.88, 587.33, 523.25, 587.33, 659.26, 587.33, 440.00, 523.25, 493.88, 523.25};
int beat[]={2,2,2,4,2,2,2,2,3,1,2,4,1,1,4,2,10,2,2,2,10,2,2,2,2,2,2,2,2,2,2,12,4,2,4,4,3};
int main(){
    int period_us;
    int beat_ms;
    
    while(true){
        for(int i=0;i<37;i++){
            buzzer = 1.0-0.1;
            period_us = 1000000/freq[i];
            beat_ms = 125*beat[i];
            buzzer.period_us(period_us);
            ThisThread::sleep_for(chrono::milliseconds(beat_ms));
            buzzer = 0.0;
            ThisThread::sleep_for(chrono::milliseconds(100));
        }
    }
}
    
