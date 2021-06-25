//
// 자동차의 충돌 방지 센서와 같이 물체가 1m 이내에 존재하면 경고음을 발생시키고 물체가 가까이 존재할수록 빠른 비트의 경고음을 발생시켜라.
// 거리측정은 ultrasonic sensor을 이용하고 경고음은 piezo buzzer를 사용하였다.
//
#include "mbed.h"
#include "SRF05.h"

SRF05 srf05(ARDUINO_UNO_D3, ARDUINO_UNO_D2);
PwmOut buzzer(ARDUINO_UNO_D5);
BufferedSerial pc(CONSOLE_TX, CONSOLE_RX, 115200);

char buffer[80];

int main(){
    sprintf(buffer, "\r\nWelcome to Ultrasonic Sensor LAb. 9-3!\r\n");
    pc.write(buffer, strlen(buffer));
    int period_us = 1000000/261.626;
    buzzer = 0;
    while(true){
        float distance = srf05.read();
        sprintf(buffer, "Distance = %.2f[cm]\r\n", distance);
        pc.write(buffer, strlen(buffer));
        if(distance < 100){
            buzzer = 0.5;
            buzzer.period_us(period_us);
            ThisThread::sleep_for(chrono::milliseconds(int(distance)));
        }
        buzzer = 0;
        ThisThread::sleep_for(100ms);
    }
}
