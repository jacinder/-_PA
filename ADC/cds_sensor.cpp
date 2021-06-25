#include "mbed.h"
#define MAXIMUM_BUFFER_SIZE 80
char buf[MAXIMUM_BUFFER_SIZE];
AnalogIn ain0(A0);
BufferedSerial pc(USBTX, USBRX, 115200);

int main(){
    float meas;
    sprintf(buf, "\r\n cds sensor lab.\r\n");
    pc.write(buf, strlen(buf));
    
    while(1){
        meas = ain0.read();
        meas = meas * 3300;
        sprintf(buf, "A0 input voltage = %.2f mV\r\n",meas);
        pc.write(buf,strlen(buf));
        ThisThread::sleep_for(chrono::milliseconds(1000));
    }
}
