#include <16F877A.h>
#include<DHT11.H>//khai bao thu vien DHT11
#define LCD_ENABLE_PIN  PIN_D3
#define LCD_RS_PIN      PIN_D1
#define LCD_RW_PIN      PIN_D2                               
#define LCD_DATA4       PIN_D4                                    
#define LCD_DATA5       PIN_D5                                
#define LCD_DATA6       PIN_D6                            
#define LCD_DATA7       PIN_D7   
#include <lcd.c>
#include "sim800l.h"
int t = 40; // khai bao nhiet do chinh kieu so nguyen
/***************************************************************/
void main()
{
   set_tris_b(0); // thiet lap trang thai chan B0
   lcd_init(); // thiet lap LCD
   unsigned int8 dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2; // khai bao nhiet do,do am cua DHT11 khong am                
   unsigned int8 str[20]; // khai bao bien chuoi 20 ky tu khong am.
   lcd_gotoxy(4,1);//dua con tro toi vi tri cot 4 hang 1
   printf(lcd_putc,"TEN CUONG");// in ra "TEN CUONG" tai vi tri cot 4 hang 1 trong lcd
   lcd_gotoxy(1,2);//dua con tro toi vi tri cot 1 hang 2
   printf(lcd_putc,"MSSV 41800993");//in ra "MSSV 41800993" tai vi tri cot 1 hang 2
   delay_ms(1000);//do tre 1000ms
   printf(lcd_putc,"\f"); // xoa lcd
   while(true)// vong lap vo han
{
   
   if(input(pin_A2) == 0 )// neu nhan dau vao chan A2 muc thap
   {
      t++;// nhiet do chinh tang len 1 (t=t+1)
      delay_ms(500);//do tre 500ms
   }
   if(input(pin_A3) == 0 )// neu nhan dau vao chan A3 muc thap
   {
      t--;//nhiet do chinh giam di 1 (t=t-1)
      delay_ms(500);//do tre 500ms
   }
   lcd_gotoxy(1,1);//dua con tro toi vi tri cot 1 hang 1
   printf(lcd_putc,"T BAO CHAY"); // in ra "T bao chay" tai vi tri cot 1 hang 1
   lcd_gotoxy(13,1);// dua con tro toi vi tri cot 13 hang 1
   printf(lcd_putc,"%d",t); // in ra "%d la so nguyen he thap phan co dau" la t
   lcd_putc(223);// in ra do
   lcd_putc("C");// in ra "C"
   if(DHT_GetTemHumi(dh_nhiet_do,dh_nhiet_do2,dh_do_am,dh_do_am2)) // neu DHT11 phat hien nhiet do, do am
   {
      lcd_gotoxy(1,2);//dua con tro toi vi tri cot 1 hang 2
      sprintf(str,"T=%u",dh_nhiet_do); // truyen nhiet do vao chuoi~ str , voi %u la so nguyen he thap phan khong dau
      printf(lcd_putc,"%s",str); // in ra nhiet do trong chuoi~ str
      lcd_putc(223);// in ra do
      lcd_putc("C");// in ra "C"
        if(input(pin_A0) == 0)
        {   
         output_high(PIN_C5); //xuat ra chan C5 tich cuc muc cao  (dung coi)    
         lcd_gotoxy(9,2);//dua con tro toi vi tri cot 9 hang 2
         printf(lcd_putc,"CO GAS     ");// in ra "CO GAS"
         delay_ms(1000);// do tre 1000ms         
        }
          if(dh_nhiet_do > t )  // neu nhiet do lon hon t chinh 
      { 
         output_high(PIN_C4); //xuat ra chan C4 tich cuc muc cao (dung led)
         delay_ms(100);
         output_low(PIN_C4); //xuat ra chan C4 tich cuc muc thap
         delay_ms(100);         
         lcd_gotoxy(9,2);//dua con tro toi vi tri cot 9 hang 2
         printf(lcd_putc,"CANH BAO        ");// in ra "CANH BAO" 
         output_low(PIN_C5); //xuat ra chan C5 tich cuc muc thap   
         delay_ms(1000);// do tre 500ms
         }
          if(dh_nhiet_do > t && input(pin_A0)==0)  // neu nhiet do lon hon nhiet do tuy chinh, và cam bien khoi phat hien khoi
      {
         output_high(PIN_C5); //xuat ra chan C5 tich cuc muc cao
         output_high(PIN_C4); //xuat ra chan C5 tich cuc muc cao         
         lcd_gotoxy(9,2);//dua con tro toi vi tri cot 10 hang 2
         printf(lcd_putc,"CO CHAY!      ");// in ra "CO CHAY" 
         delay_ms(3000);// do tre 1000ms
      }
      else//nguoc lai
      {
      lcd_gotoxy(9,2);//dua con tro toi vi tri cot 10 hang 2
      printf(lcd_putc,"                "); // xoa tu co chay 
      }
      output_low(PIN_C4); //xuat ra chan C4 tich cuc muc thap   
      output_low(PIN_C5); //xuat ra chan C5 tich cuc muc thap
       DELAY_MS(500);// do tre 500ms
   }

   }
}
