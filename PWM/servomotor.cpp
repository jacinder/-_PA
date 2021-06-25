//
// 각도를 입력하면 그에 맞게 servo motor가 조정되도록 하여라.
//
#include "mbed.h"
#include <stdlib.h>
#define PWM_MIN 550
#define PWM_MAX 2150

PwmOut servoMotor(D6);
UnbufferedSerial pc(USBTX, USBRX, 115200);

char rx_buffer[10];
char tx_buffer[80];
int index = 0;
volatile int flag=0;

void rx_ISR(void){
    char ch;
    pc.read(&ch,1);
    pc.write(&ch,1);
    rx_buffer[index++]=ch;
    if(ch=='\r'){
        pc.write("\n",1);
        rx_buffer[--index]='\0';
        index = 0;
        flag = 1;
    }
}
void control_servo(){
    flag = 0;
    int angle = atoi(rx_buffer);
    int pwm = PWM_MIN + 400 * (angle/45);
    if(pwm >= PWM_MIN && pwm <= PWM_MAX){
        servoMotor.pulsewidth_us(pwm); // for 0 degree
        sprintf(tx_buffer, "Pulse ON time = %d (%d)\r\n", pwm, angle);
        pc.write(tx_buffer, strlen(tx_buffer));
    }
    else{
        sprintf(tx_buffer, "Wrong input!\r\n");
        pc.write(tx_buffer, strlen(tx_buffer));
    }
}
int main(){
    sprintf(tx_buffer, "PWM Test Program (Servo Motor)!\r\n");
    pc.write(tx_buffer,strlen(tx_buffer));
    pc.attach(rx_ISR, SerialBase::RxIrq);
    servoMotor.period_ms(20); // PWM period = 20ms
    servoMotor.pulsewidth_us(PWM_MIN); // for 0 degree
    while(1){
        flag = 0;
        sprintf(tx_buffer, "  Enter the rotation degree [0-180]: ");
        pc.write(tx_buffer, strlen(tx_buffer));
        while(flag != 1);
        control_servo();
    }
}
