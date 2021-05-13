#include <stdint.h>

void confi_Timer(void);

void confi_output_pa6_pa7_pb0_pb1(void);

void setDuty_Left_Forward(int);
void setDuty_Left_Backward(int);
void setDuty_Right_Forward(int);
void setDuty_Right_Backward(int);
void setforward(int left, int right);
void setbackward(int left, int right);
void initilize_motor(void);
void turnLeft(int left, int right);
void turnRight(int left, int right);