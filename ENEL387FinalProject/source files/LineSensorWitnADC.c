
 #include "stm32f10x.h"
 #include "LineSensorWithADC.h"
#include "Configuration.h"
double Vref=3.6;
void confi_input_LineADC(void){
	GPIOA->CRL&=~GPIO_CRL_MODE4;
	GPIOA->CRL&=~GPIO_CRL_CNF4;
		GPIOA->CRL&=~GPIO_CRL_MODE0;
	GPIOA->CRL&=~GPIO_CRL_CNF0;
		GPIOA->CRL&=~GPIO_CRL_MODE1;
	GPIOA->CRL&=~GPIO_CRL_CNF1;
}


void confi_ADC(void){

	ADC1->CR2 |=ADC_CR2_ADON;
}
uint32_t read_ADC(char CH){
	if(CH=='r')
		ADC1->SQR3=0x0;
	else if(CH=='l')
		ADC1->SQR3= ADC_SQR3_SQ1_0;
	else if(CH=='c')
		ADC1->SQR3= ADC_SQR3_SQ1_2;
	
	ADC1->CR2|=ADC_CR2_ADON;
	while((ADC1->SR & ADC_SR_EOC) != ADC_SR_EOC){}
	return ADC1->DR;
}

uint32_t conver_digital(double input){
	double temp=3.3/4095;
	double result=input/temp;
	return (uint32_t)result;
}
_Bool rightIsBlack(){
	uint32_t convet_value=conver_digital(0.8*Vref);
uint32_t	analog_left=read_ADC('l');
	if(convet_value<analog_left)
		return 1;
	else
		return 0;

}
_Bool centerIsBlack(){
uint32_t convet_value=conver_digital(0.8*Vref);
uint32_t	analog_center=read_ADC('c');
	if(convet_value<analog_center)
		return 1;
	else
		return 0;
}
_Bool leftIsBlack(){
		uint32_t convet_value=conver_digital(0.8*Vref);
uint32_t	analog_right=read_ADC('r');
	if(convet_value<analog_right)
		return 1;
	else
		return 0;
}


