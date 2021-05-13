
 #include "stm32f10x.h"
 #include "Configuration.h"

	int left_motor_power=45;
	int right_motor_power=60;
void clockInit(void)
{
    RCC->CR |= 0x00000001;
    while (((RCC->CR) & 0x00000003) == 0);

    RCC->CR |= 0x00050000;
    while (((RCC->CR) & 0x0007000) == 0);
				

    RCC->CFGR = 0x04000001;
    while (((RCC->CFGR) & 0x00000005) == 0);
		RCC->CR &= ~RCC_CR_PLLON;

		RCC->CFGR = 0x00050000;// 24 MHz **** MAX SPEED for VLDISCOVERY *****


    RCC->CR |= RCC_CR_PLLON;
    while (((RCC->CR) & 0x03000000) == 0);
		
    RCC->CFGR |= 0x00000002;
    while (((RCC->CFGR) & 0x00000008) == 0);
			
			
		RCC->CFGR |= RCC_CFGR_MCO_PLL;

    RCC->APB2ENR |=  RCC_APB2ENR_IOPAEN | RCC_APB2ENR_AFIOEN;
}



void confi_output(void){

		GPIOA->CRL |= GPIO_CRL_MODE5;// test LED
		GPIOA->CRL &= ~GPIO_CRL_CNF5;//test LED
}


void delay(uint32_t cnt)
{
    while(cnt--)
        __nop();
}

void navigate_line(void){
	
	if (!leftIsBlack()&&!rightIsBlack())
	{
		setforward(left_motor_power,right_motor_power);
		
	}
	else if (leftIsBlack()&&!rightIsBlack())
	{
			turnLeft(0,80);
	}
	else if (!leftIsBlack()&&rightIsBlack())
	{
		turnRight(60,0);
	
	}
}
_Bool find_target1(void){
	if (!leftIsBlack()&&rightIsBlack()&&centerIsBlack())
		return 1;
		else 
		return 0;
}

_Bool find_target2(void){
	if (leftIsBlack()&&!rightIsBlack()&&centerIsBlack())
		return 1;
		else 
		return 0;
}

_Bool find_target3(void){
	if (leftIsBlack()&&rightIsBlack()&&centerIsBlack())
		return 1;
		else 
		return 0;
}

_Bool turn_around(void){
	if (!leftIsBlack()&&!rightIsBlack()&&!centerIsBlack())
		return 1;
		else 
		return 0;

}

