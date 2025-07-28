#include "delay.h"

void delay_ms(int ms) {
int i;
    for ( i = 0; i < ms * 3000; i++) {
        __NOP();
    }
}

void delay_us(int us) {
int i;
    for (i = 0; i < us * 3; i++) {
        __NOP();
    }
}
