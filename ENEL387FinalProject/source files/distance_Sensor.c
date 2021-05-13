
 #include "stm32f10x.h"
 #include "distance_Sensor.h"

 void Echo_Input_Enable(){
	GPIOB->CRH &=  ~GPIO_CRH_MODE9 & ~GPIO_CRH_CNF9_0 ;
    GPIOB->CRH |=  GPIO_CRH_CNF9_1 ;
	 
	GPIOB->CRH &=  ~GPIO_CRH_MODE10 & ~GPIO_CRH_CNF10_0 ;
    GPIOB->CRH |=  GPIO_CRH_CNF10_1 ;
 }
 
 void Trig_Output_Enable(){
    GPIOB->CRH |= GPIO_CRH_MODE8;
    GPIOB->CRH &= ~GPIO_CRH_CNF8;
	GPIOB->CRL |= GPIO_CRL_MODE5;
	GPIOB->CRL &= ~GPIO_CRL_CNF5;
 
	 
	GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH &= ~GPIO_CRH_CNF9;
    GPIOB->CRL |= GPIO_CRL_MODE6;
	GPIOB->CRL &= ~GPIO_CRL_CNF6;
}
  int Read_PB9(){

	if((GPIOB->IDR)&0x200){
		return 1;
		}
	else{
		return 0;
		}
	 
 }

   int Read_PB10(){

	if((GPIOB->IDR)&0x400){
		return 1;
		}
	else{
		return 0;
		}
	 
 }

uint32_t Get_Distance_Front(){
	uint32_t t =0;
	GPIOB_Write_Zero(5);
	delay(2);
	GPIOB_Write_One(5);//turn on trig pin
	delay(10);
	GPIOB_Write_Zero(5);//turn off trig pin
	while(!Read_PB10());
	while(Read_PB10()){
		t++;//count time
		delay(1);
	}
	return t;
}

uint32_t Get_Distance_End(){
	uint32_t t =0;
	GPIOB_Write_Zero(8);
	delay(2);
	GPIOB_Write_One(8);//turn on trig pin
	delay(10);
	GPIOB_Write_Zero(8);//turn off trig pin
	while(!Read_PB9());
	while(Read_PB9()){
		t++;//count time
		delay(1);
	}
	return t;
}
	void GPIOB_Write_Zero(int x){
		
		uint32_t Mask = 0xffff;
		uint32_t Mask2 = 0x0001;
		Mask2 = Mask2<<x;
		uint32_t Temp = Mask^Mask2;
		GPIOB->ODR &=Temp;
}
	void GPIOB_Write_One(int x){
		
		
		uint32_t Mask2 = 0x0001;
		Mask2 = Mask2<<x;

		GPIOB->ODR |=Mask2;
}