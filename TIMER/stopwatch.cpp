#include "mbed.h"
InterruptIn button(USER_BUTTON);
Timer t;
Timer button_t;
int button_count, start_t, end_t, log_t[10], button_time;
int is_started=0, is_logged=0, is_finished=0;
void button_fall(void){
    button_t.start();
}
void button_rise(void){
    button_time = chrono::duration_cast<chrono::milliseconds>(button_t.elapsed_time()).count();
    button_t.stop();
    button_t.reset();
    if(button_time < 1000){ //when the button is pressed for a short time.
        if(button_count == 0){
            t.start();
            is_started=1;
            button_count++;
        }
        else{
            end_t = chrono::duration_cast<chrono::milliseconds>(t.elapsed_time()).count();
            log_t[button_count-1] = chrono::duration_cast<chrono::milliseconds>(t.elapsed_time()).count(); //create a new log
            button_count ++;
            is_logged = 1;
        }
    }
    else{  //  when the button is pressed for a long time.
        end_t = chrono::duration_cast<chrono::milliseconds>(t.elapsed_time()).count();
        t.stop();
        t.reset();
        button_count = 0;
        is_finished = 1;
    }
}

int main(){
    button.fall(&button_fall);
    button.rise(&button_rise);
    while(1){
        if(is_started){
            printf("start button\n\n");
            is_started = 0;
        }
        if(is_logged){
            printf("log button\n");
            printf("lab time: %dms\n",end_t); //print lab time
            for(int i=0;i<button_count-2;i++){ //print log time
                printf("log[%d]: %dms\n",i,log_t[i]);
            }
            printf("\n");
            is_logged = 0;
        }
        if(is_finished){
            printf("end button\n");
            printf("lab time: %dms\n\n", end_t);
            is_finished = 0;
        }
    }
}
