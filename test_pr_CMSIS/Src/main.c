#include "main.h"


     volatile uint32_t  SysTick_Count = 0;


      void  SysTick_Handler(void)
     {
    	if (SysTick_Count > 0) SysTick_Count --;
    	}

       void delay_ms(int ms)
    	{
    		SysTick->LOAD = 16000-1;
    		SysTick_Count = ms;
    		while (SysTick_Count){}
    	}

     int main (void)
    	{
    		uint32_t SystemCoreClock = 16000000;

    		RCC->AHB1ENR	|= RCC_AHB1ENR_GPIOAEN; //RCC on for GPIO C
    		GPIOA->MODER &= ~0x00000C00; /* clear pin mode */
    		GPIOA->MODER |= GPIO_MODER_MODER5_0; /* set pin to output mode */

    		SysTick_Config(SystemCoreClock/1000); // set tick to every 1ms
    		DWT->CTRL |= 1;
    		DWT->CYCCNT = 0;

   		while(1) {
   				uint32_t start = DWT->CYCCNT;
   				GPIOA->BSRR = GPIO_BSRR_BS5;
   				uint32_t end = DWT->CYCCNT;
   				uint32_t cycles = end - start;
    			delay_ms(1000);
   				GPIOA->BSRR = GPIO_BSRR_BR5;
    			delay_ms(1000);
    		}
    	}
