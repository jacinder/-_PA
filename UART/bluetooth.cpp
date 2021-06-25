//
// 1. 사용자가 pc에서 글자를 입력할 경우 pc terminal과 스마트폰 terminal에 입력한 텍스트가 출력되어야 한다.
// 2. 사용자가 스마트폰 terminal에 글자를 입력할 경우 pc terminal에 출력되어야 한다.
// 3. 스마트폰 앱을 통해서 rLed On, rLed Off, rLed Status, gLed On, gLed Off, gLed Status라는 명령어를 통해 보드에 연결된 red LED, green LED가 제어되어야 한다.
// 스마트폰 앱을 통해 명령어가 입력될 경우 상황에 맞게 "Red LED status : on 혹은 off" / "Green LED status : on 혹은 off" 의 텍스트로 LED의 상태가 표시되어야한다.
// 잘못된 명령어일 경우 "Undefined command"라고 출력되어야 한다.
// 
// HM-10모듈의 TX핀은 보드의 D2, RX핀은 D8에 연결하였다.
// Red LED는 보드의 D3, Green LED는 보드의 D4에 연결하였다.
//
#include "mbed.h"
#include <string.h>
#define MAXIMUM_BUFFER_SIZE 80

char buf[MAXIMUM_BUFFER_SIZE];
char command[MAXIMUM_BUFFER_SIZE];
int pointer = 0;
int rStat, gStat;
DigitalOut greenLed(D3);
DigitalOut redLed(D4);
static UnbufferedSerial pc(USBTX, USBRX, 9600);
static UnbufferedSerial bt(D8, D2, 9600);



void pc_rx_handler(){
    char c;
    if (pc.read(&c, 1)){
        pc.write(&c, 1);
        bt.write(&c, 1);
    }
}
void bt_rx_handler(){
    char c;
    if (bt.read(&c, 1)){
            pc.write(&c, 1);
            bt.write(&c, 1);
            //  When \n is entered, clear the command    
           
            if(c=='\r'){
                command[pointer] = '\0';
                if(strcmp(command,"gLed On")==0){
                    greenLed = 1;
                    gStat = 1;
                }
                else if(strcmp(command,"gLed Off")==0){
                    greenLed = 0;
                    gStat = 1;
                }
                else if(strcmp(command,"gLed Status")==0){
                    gStat = 1;
                }
                else if(strcmp(command,"rLed On")==0){
                    redLed = 1;
                    rStat = 1;
                }
                else if(strcmp(command,"rLed Off")==0){
                    redLed = 0;
                    rStat = 1;
                }
                else if(strcmp(command,"rLed Status")==0){
                    rStat = 1;
                }
                else{
                    sprintf(buf, "Undefined command\r\n");
                }
                
                if(gStat == 1){
                    if(greenLed == 1)
                        sprintf(buf, "Gled status: on\r\n");
                    else
                        sprintf(buf, "Gled status: off\r\n");
                    gStat = 0;
                }
                else if(rStat == 1){
                    if(redLed == 1)
                        sprintf(buf, "Rled status: on\r\n");
                    else
                        sprintf(buf, "Rled status: off\r\n");
                    rStat = 0;
                }
                
                bt.write(buf, strlen(buf));
                pc.write(buf, strlen(buf));
                
                command[0] = '\0';
                pointer = 0;
                
            }
            // else, combine the command
            else{
                command[pointer] = c;
                pointer ++;
            }
    }
}
int main(void){
    redLed=0;
    greenLed=0;
    pc.attach(pc_rx_handler, SerialBase::RxIrq);
    bt.attach(bt_rx_handler, SerialBase::RxIrq);
    sprintf(buf, "program start..!\r\n");
    pc.write(buf, strlen(buf));
    bt.write(buf, strlen(buf));
    
    while(1){

    }
}
