//
// cds 조도센서를 이용하여 특정 밝기 이하일 경우 led가 켜지도록 하여라.
//
#include "mbed.h"
#define MAXIMUM_BUFFER_SIZE 80
char buf[MAXIMUM_BUFFER_SIZE];
AnalogIn ain0(A0);
DigitalOut greenLed(D3);
BufferedSerial pc(USBTX, USBRX, 115200);

int main(){
    float meas;
    sprintf(buf, "\r\n Welcome to Analog In Lab.\r\n");
    pc.write(buf, strlen(buf));
    
    while(1){
        meas = ain0.read();
        meas = meas * 3300;
        sprintf(buf, "A0 input voltage = %.2f mV\r\n",meas);
        pc.write(buf,strlen(buf));
        if(meas < 100)
            greenLed = 1;
        else
            greenLed = 0;
        ThisThread::sleep_for(chrono::seconds(5));
    }
}
