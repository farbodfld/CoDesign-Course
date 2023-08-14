#include <stdio.h>




volatile unsigned int *starter = (int *) 0x80000000;
volatile unsigned int *theta_input = (int *) 0x80000004;
volatile unsigned int *iteration_input = (int *) 0x80000008;
volatile unsigned int *shift_input = (int *) 0x80000000C;
volatile unsigned int *cos_output = (int *) 0x80000010;
volatile unsigned int *sin_output = (int *) 0x80000001C;



#define ATAN_TAB_N 16

void HW_Connection(int theta, int iterations,int shift, int *sin , int *cos) {
      
      *iteration_input = iterations;
      *theta_input = theta;	
      *shift_input = shift;
      *starter = 1;	
   	
    
     while (*sin_output == 0 && *cos_output == 0);	

	

    *sin = *sin_output;
    *cos = *cos_output;	
    
    *starter = 0;	
}

int main() {
    int theta = 110;        		
    int iterations = 15;
    int quadAdj, shift, cos, sin; 
                                			
    		

    
    iterations = (iterations > ATAN_TAB_N) ? ATAN_TAB_N : iterations;

    
    while (theta < -180)
        theta += 360;

    while (theta > 180)
        theta -= 360;

    
    if (theta < -90) {
        theta = theta + 180;
        quadAdj = -1;
    } else if (theta > 90) {
        theta = theta - 180;
        quadAdj = -1;
    } else
        quadAdj = 1;

   
    if (theta < -45) {
        theta = theta + 90;
        shift = -1;
    } else if (theta > 45) {
        theta = theta - 90;
        shift = 1;
    } else
        shift = 0;

    
    if (theta < 0) {
        theta = -theta;
        theta = ((unsigned int) theta << 10) / 45;   
        theta = (unsigned int) theta << 4;
        theta = -theta;
    } else {
        theta = ((unsigned int) theta << 10) / 45;   
        theta = (unsigned int) theta << 4;
    }

    
    HW_Connection(theta, iterations, shift, &sin, &cos);

    
    sin *= quadAdj;
    cos *= quadAdj;

    
    printf("Software : sin = %x, cos = %x\n", sin, cos);


    return 0;
}
