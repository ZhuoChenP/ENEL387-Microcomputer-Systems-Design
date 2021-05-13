
 #include "stm32f10x.h"
 #include "PWM.h"
 	

void confi_output_pa6_pa7_pb0_pb1(void){

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN |RCC_APB2ENR_AFIOEN |RCC_APB2ENR_ADC1EN|RCC_APB2ENR_IOPBEN ;
    GPIOA->CRL |= GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6_1 | GPIO_CRL_MODE6_0 ;
    GPIOA->CRL &= ~GPIO_CRL_CNF6_0 ;
	GPIOA->CRL |= GPIO_CRL_CNF7_1 | GPIO_CRL_MODE7_1 | GPIO_CRL_MODE7_0 ;
    GPIOA->CRL &= ~GPIO_CRL_CNF7_0 ;
	
	GPIOB->CRL |= GPIO_CRL_CNF0_1 | GPIO_CRL_MODE0_1 | GPIO_CRL_MODE0_0 ;
    GPIOB->CRL &= ~GPIO_CRL_CNF0_0 ;
	GPIOB->CRL |= GPIO_CRL_CNF1_1 | GPIO_CRL_MODE1_1 | GPIO_CRL_MODE1_0 ;
    GPIOB->CRL &= ~GPIO_CRL_CNF1_0 ;
}



void confi_Timer(void){
	RCC->APB1ENR|=RCC_APB1ENR_TIM3EN;//configure TIM3
	confi_output_pa6_pa7_pb0_pb1();

	TIM3->CR1 |= TIM_CR1_CEN; // Enable Timer3

	TIM3->EGR |= TIM_EGR_UG;  //Reinitialize the counter
	
	TIM3->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1|TIM_CCMR1_OC1PE | TIM_CCMR1_OC1FE;//PWM mode 1, Preload Enable, Fast Enable
	TIM3->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1|TIM_CCMR1_OC2PE | TIM_CCMR1_OC2FE;//PWM mode 1, Preload Enable, Fast 
	TIM3->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1|TIM_CCMR2_OC3PE | TIM_CCMR2_OC3FE;//PWM mode 1, Preload Enable, Fast Enable
	TIM3->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1|TIM_CCMR2_OC4PE | TIM_CCMR2_OC4FE;//PWM mode 1, Preload Enable, Fast Enable
	TIM3->CCER |= TIM_CCER_CC1E; //Enable CH1
	TIM3->CCER |= TIM_CCER_CC2E; //Enable CH2
	TIM3->CCER |= TIM_CCER_CC3E; //Enable CH3
	TIM3->CCER |= TIM_CCER_CC4E; //Enable CH4
	
	TIM3->PSC=0x095F;	// Divide 24 MHz by 2400 (PSC+1), PSC_CLK= 10000 Hz, 1 count = 0.1 ms
	TIM3->ARR = 100; //100 counts=10ms or 100hz	
	TIM3->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN; // Enable timer 3
}

void setDuty_Left_Forward(int duty){
	TIM3->CCR1 = duty;
//TIM3->EGR |= TIM_EGR_UG;
}
void setDuty_Left_Backward(int duty){
	TIM3->CCR2 = duty;
//TIM3->EGR |= TIM_EGR_UG;
}
void setDuty_Right_Forward(int duty){
	TIM3->CCR3 = duty;
//TIM3->EGR |= TIM_EGR_UG;
}
void setDuty_Right_Backward(int duty){
	TIM3->CCR4 = duty;
//TIM3->EGR |= TIM_EGR_UG;
}
void setforward(int left, int right)
{
	setDuty_Right_Backward(0);
	setDuty_Left_Backward(0);
	setDuty_Right_Forward(right);
	setDuty_Left_Forward(left);
}
void setbackward(int left, int right){

	setDuty_Right_Forward(0);
	setDuty_Left_Forward(0);
	setDuty_Right_Backward(right);
	setDuty_Left_Backward(left);
}

void turnLeft(int left, int right){
	setDuty_Right_Backward(0);
	setDuty_Left_Forward(0);
	setDuty_Left_Backward(left);
	setDuty_Right_Forward(right);
}
void turnRight(int left, int right){
	setDuty_Left_Backward(0);
	setDuty_Right_Forward(0);
	setDuty_Right_Backward(right);
	setDuty_Left_Forward(left);
}