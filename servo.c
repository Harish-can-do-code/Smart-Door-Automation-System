#include "LPC17xx.h"
#include <stdint.h>

#define PWM_PIN 20  // P1.20 used for PWM1.2

void PWM_Init(void) {
    // Configure P1.20 as PWM1.2
    LPC_PINCON->PINSEL3 |= (0x02 << 8);   // Select PWM1.2 function for P1.20

    // Reset PWM settings
    LPC_PWM1->TCR = (1 << 1);             // Reset PWM TC and PC
    LPC_PWM1->PR = 0;                      // Prescaler = 0 (no division)

    // Set PWM frequency to 50Hz (20ms period)
    LPC_PWM1->MR0 = 20000;                 // 20ms period at 1us resolution
    LPC_PWM1->MR2 = 1500;                   // Initial pulse width ~1.5ms (neutral position)

    LPC_PWM1->MCR = (1 << 1);              // Reset on match with MR0
    LPC_PWM1->PCR = (1 << 10);             // Enable PWM1.2 output
    LPC_PWM1->LER = (1 << 0) | (1 << 2);   // Latch MR0 and MR2

    // Start PWM
    LPC_PWM1->TCR = (1 << 0) | (1 << 3);   // Enable counter and PWM mode
}

void Servo_Rotate(int angle) {
    // Map the angle to PWM pulse width
    uint32_t pulse_width = 500 + ((2000 * angle) / 180);   // Map 0° to 180° to 0.5ms to 2.5ms
    LPC_PWM1->MR2 = pulse_width;            // Set PWM duty cycle
    LPC_PWM1->LER |= (1 << 2);              // Latch the new value
}

int main(void) {
volatile int i;
    PWM_Init();
    
    while (1) {
        Servo_Rotate(0);    // Move to 0°
        for ( i = 0; i < 1000000; i++){}  // Delay
       
        Servo_Rotate(90);   // Move to 90°
        for (i = 0; i < 1000000; i++){}  // Delay
        
        Servo_Rotate(180);  // Move to 180°
        for ( i = 0; i < 1000000; i++){} // Delay
    }
}
