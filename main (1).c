#include <lpc17xx.h>
#include <string.h>

#include "servo.c"
#include "delay.c"
#include "KEY_TEST.c"

#define PASSWORD "123"   // Predefined password
#define MAX_LENGTH 3     // Max password length

void enterPassword(char *input);

  char input[4];  // Store entered password
int main(void) {
    lcd_init();
    Servo_Init();
	Keypad_Init();
    
  

    while (1) {
        lcd_cmd_write(0x01);         // Clear LCD
        lcd_cmd_write(0x80);         
        lcd_str("ENTER PASSWORD");
        lcd_cmd_write(0xC0);         // Move to second row

        enterPassword(input);        // Read password

        // Check password validation
        if (strcmp(input, PASSWORD) == 0) {
            lcd_cmd_write(0x01);
            lcd_str("DOOR OPENED");

            // Rotate servo to open door
            Servo_Rotate(90);
            delay_ms(3000);
            
            // Close the door
            Servo_Rotate(0);
            lcd_cmd_write(0x01);
        } else {
            lcd_cmd_write(0x01);
            lcd_str("INVALID PASSWORD");
            lcd_cmd_write(0xC0);
            lcd_str("TRY AGAIN");
            delay_ms(2000);
        }
    }
}

void enterPassword(char *input) {
    int i = 0;
    while (i < MAX_LENGTH) {
        char key = Keypad_Scan();  // Scan for keypad input
        if (key != '\0') {      // Valid key detected
            input[i++] = key;   // Store the digit
            lcd_data_write(key);  
        }
    }
    input[i] = '\0';  // Null-terminate the string
}


