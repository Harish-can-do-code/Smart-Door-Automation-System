#include<lpc17xx.h>
#include<stdint.h>
#define RS (1<<10)
#define RW (1<<12)
#define EN (1<<11)
#define DATA (0xFF<<15)

void lcd_cmd_write(uint8_t);
void lcd_data_write(uint8_t);
void delay(uint32_t);
void lcd_init(void);
void lcd_str(char *ptr);
void lcd_num(unsigned int num);


void lcd_init(void)
{
LPC_GPIO0->FIODIR=RS|RW|EN|DATA;
lcd_cmd_write(0x01);
lcd_cmd_write(0x38);
lcd_cmd_write(0x0E);
lcd_cmd_write(0x80);
}

void lcd_cmd_write(uint8_t cmd)
{
LPC_GPIO0->FIOCLR=DATA;
LPC_GPIO0->FIOSET=(uint32_t)cmd<<15;
LPC_GPIO0->FIOCLR=RS;
LPC_GPIO0->FIOCLR=RW;
LPC_GPIO0->FIOSET=EN;
delay(50);
LPC_GPIO0->FIOCLR=EN;
}

void lcd_data_write(uint8_t data)
{
LPC_GPIO0->FIOCLR=DATA;
LPC_GPIO0->FIOSET=(uint32_t)data<<15;;
LPC_GPIO0->FIOSET=RS;
LPC_GPIO0->FIOCLR=RW;
LPC_GPIO0->FIOSET=EN;
delay(50);
LPC_GPIO0->FIOCLR=EN;
}

void delay(uint32_t millis)
{
uint32_t i,j;
for(i=0;i<millis;i++)
for(j=0;j<6000;j++);
}

void lcd_str(char *ptr)
{
while(*ptr!='\0')
{
lcd_data_write(*ptr);
ptr++;
}
}
void lcd_num(unsigned int num)
{
	if(num)
	{
	lcd_num(num/10);
	lcd_data_write(num%10+0x30);
	}
}
