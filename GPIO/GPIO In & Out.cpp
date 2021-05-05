#include "mbed.h"
#include "core_cm4.h"

void led2_init(void);
void button_init(void);
uint32_t button_input(void);
void led2_toggle(void);

int main()
{
    
    
    
    int interval = 500;
    uint32_t val;
    led2_init();
    button_init();

    while (true) {
        val = button_input();
        
        if(val == 0){
            interval = interval << 1;
            if(interval > 2000)
                interval = 500;
        }
        
        led2_toggle();
        thread_sleep_for(interval);
    }
    
}
void led2_init(void){
    //PA_5 output init(01)
    __HAL_RCC_GPIOA_CLK_ENABLE();
  
    GPIOA->MODER &= ~(0b11 << 10);
    GPIOA->MODER |= 0b01 << 10;
}
void button_init(void){
   //PC_13 input init(00)
   __HAL_RCC_GPIOC_CLK_ENABLE();
   GPIOC->MODER &= ~(0b11 << 26);

}
uint32_t button_input(void){
    return (GPIOC->IDR >> 13) & 0b1;
}
void led2_toggle(void){
    GPIOA->ODR ^= (0b1<<5);
}
