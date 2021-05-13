 #include "stm32f10x.h"
 #include "PWM.h"
#include "distance_Sensor.h"
#include "LineSensorWithADC.h"
#include "Configuration.h"


int main(void){
clockInit();
confi_output_pa6_pa7_pb0_pb1();
confi_ADC();

	confi_Timer();
	confi_output();
	confi_input_LineADC();

	Echo_Input_Enable();
	Trig_Output_Enable();
	uint32_t d=5000000;
	uint32_t dF = 0;
	int counter=0;
	_Bool end=1;
while(end){
		dF =(Get_Distance_Front()*0.014)*2;//get distance in cm
	
			if(find_target1())
			{
			GPIOA->BSRR|= NUC_Green_ON;
			GPIOA->BSRR|= NUC_Red_OFF;
				setforward(45,85);
				delay(500000);
			}
			else if(find_target2()){
			GPIOA->BSRR|= NUC_Green_OFF;
			GPIOA->BSRR|= NUC_Red_ON;
				setforward(45,85);
				delay(450000);
				}
			else if(find_target3())
			{
			GPIOA->BSRR|= NUC_Green_ON;
			GPIOA->BSRR|= NUC_Red_ON;
				setforward(45,85);
				delay(500000);
		
			}
			else if(dF<5&&turn_around()&&counter==0)
			{
					turnLeft(45,60);	
					delay(2830000);
					setbackward(0,0);
					counter=1;
			}
			else if(dF<5&&turn_around()&&counter==1)
			{
					setbackward(0,0);
					end=0;
			}
			else 
			{	GPIOA->BSRR|= NUC_Green_OFF;
				GPIOA->BSRR|= NUC_Red_OFF;
				navigate_line();
			}
		}

	while(1){
		GPIOA->BSRR|= NUC_Green_ON;
		GPIOA->BSRR|= NUC_Red_ON;
		delay(d);
		GPIOA->BSRR|= NUC_Green_OFF;
		GPIOA->BSRR|= NUC_Red_OFF;
		delay(d);
	}
}