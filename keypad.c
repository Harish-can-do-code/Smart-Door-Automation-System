#include "LCD_fun.c"
#define p LPC_GPIO2

int main() 
{
int val;
    lcd_init();
    p->FIODIR=(0xf0<<0);    //keypad pins direction: Row is fixed, columns scan

    while (1) 
	{
	  p->FIOPIN=(0x7f);
	  val=(p->FIOPIN & (0xff));
	  switch(val)
	  {
	  case 0x77:  lcd_data_write('0');  delay(100);	 break;
	  case 0x7b: lcd_data_write('1'); delay(100);	 break;
	  case 0x7d: lcd_data_write('2'); delay(100);	 break;
	  case 0x7e: lcd_data_write('3');  delay(100);	 break;
	  }

	  p->FIOPIN=(0xbf);
	  val=(p->FIOPIN & (0xff));
	  switch(val)
	  {
	  case 0xb7: lcd_data_write('4'); delay(100);	 break;
	  case 0xbb: lcd_data_write('5');  delay(100);	 break;
	  case 0xbd: lcd_data_write('6');  delay(100);	 break;
	  case 0xbe: lcd_data_write('7'); delay(100);	 break;
	  }

	  p->FIOPIN=(0xdf);
	  val=(p->FIOPIN & (0xff));
	  switch(val)
	  {
	  case 0xd7: lcd_data_write('8'); delay(100);	 break;
	  case 0xdb: lcd_data_write('9');  delay(100);	 break;
	  case 0xdd: lcd_data_write('a');  delay(100);	 break;
	  case 0xde: lcd_data_write('b');  delay(100);	 break;
	  }

	  p->FIOPIN=(0xef);
	  val=(p->FIOPIN & (0xff));
	  switch(val)
	  {
	  case 0xe7:  lcd_data_write('c');  delay(100);	 break;
	  case 0xeb: lcd_data_write('d'); delay(100);	 break;
	  case 0xed: lcd_data_write('e');  delay(100);	 break;
	  case 0xee:  lcd_data_write('f'); delay(100);	 break;
	  }
    }   
}
