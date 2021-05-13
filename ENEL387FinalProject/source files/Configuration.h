
 #include "stm32f10x.h"
  #include "PWM.h"
#include "distance_Sensor.h"
#include "LineSensorWithADC.h"

void clockInit(void);

void confi_output(void);

void delay(uint32_t cnt);
void navigate_line(void);
_Bool find_target1(void);
_Bool find_target2(void);
_Bool find_target3(void);
_Bool turn_around(void);

 #define NUC_Green_ON	0X00000020
 #define NUC_Green_OFF	0x00200000 
 #define NUC_Red_ON	0X00000200
 #define NUC_Red_OFF	0x02000000 
