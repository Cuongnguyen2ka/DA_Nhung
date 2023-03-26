
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8)
void Send_SMS(unsigned char style);
void Waiting_SIM(void);
void Configuration_Sim();

VOID SETUP_SIM()
{   
   Waiting_SIM();
   Configuration_Sim();
   Delay_ms(3000);
   Send_SMS(4);
   Delay_ms(500);
}

/***************************************************************/


void Send_SMS(unsigned char style)
{
   printf("AT+CMGS=\"+84364803742\"\r\n"); // Cấu hình số điện thoại gửi đến
   Delay_ms(1000);
   switch(style)
   {  
      case 1:
      {
         printf("CO CHAY!!!");
         break;
      }
      case 2:
      {
         printf("NGUY HIEM! ");
         break;
      }
      case 3:
      {
         printf("CO KHOI ");
         break;
      }
      case 4:
      {
         printf("He thong khoi dong");
         break;
      }
      case 5:
      {
         printf("AN TOAN");
         break;
      }
   }
     Delay_ms(1000);
     putc(26);
     Delay_ms(1000);
}


void Waiting_SIM(void)
{
   lcd_gotoxy(1,1);
    lcd_putc("\fKHOI DONG SIM ");
   Delay_ms(3000);
     lcd_gotoxy(1,1);
   lcd_putc("KHOI DONG SIM. ");
   Delay_ms(3000);
     lcd_gotoxy(1,1);
   lcd_putc("KHOI DONG SIM.. ");
   Delay_ms(3000);
     lcd_gotoxy(1,1);
   lcd_putc("KHOI DONG SIM... ");
   Delay_ms(3000);
}

void Configuration_Sim()  //thiet lap tap lenh at cho sim
{
   printf("AT\r\n");  // kiểm tra module sim có hoạt động hay không                                                                       Delay_ms(4000);
   printf("ATZ\r\n");  	           /*lcd_gotoxy(1,1);       lcd_putc("ATZ               "); */   Delay_ms(4000);
   printf("ATE1\r\n");//kích hoạt module            /* lcd_gotoxy(1,1);       lcd_putc("ATE0              "); */   Delay_ms(4000);
   printf("AT+ICF=3,3\r\n");      /*  lcd_gotoxy(1,1);       lcd_putc("AT+ICF=3,3        "); */   Delay_ms(4000);
   printf("AT+IPR=9600\r\n");     /*  lcd_gotoxy(1,1);       lcd_putc("AT+IPR=9600       "); */   Delay_ms(4000);
   printf("AT&W\r\n");             /* lcd_gotoxy(1,1);       lcd_putc("AT&W              "); */   Delay_ms(4000);
   printf("AT+CMGF=1\r\n");//cấu hình tin nhắn        /* lcd_gotoxy(1,1);       lcd_putc("AT+CMGF=1         "); */   Delay_ms(4000);
   printf("AT+CNMI=2,2,0,0,0\r\n");//hiển thị ra ngay tin nhắn        /*lcd_gotoxy(1,1);       lcd_putc("AT+CNMI=2,1,0,0,0 "); */   Delay_ms(4000);
   printf("AT+CSAS\r\n");          /* lcd_gotoxy(1,1);       lcd_putc("AT+CSAS           ");*/    Delay_ms(4000);
   printf("AT+CMGD=1,4\r\n");// Xóa tin nhắn      /* lcd_gotoxy(1,1);       lcd_putc("AT+CMGD=1,4       ");*/    Delay_ms(4000);
   printf("AT+CMGR=1,2\r\r");// đọc tin nhắn     /*  lcd_gotoxy(1,1);       lcd_putc("AT+CMGR=1,2       "); */   Delay_ms(4000);
  // lcd_gotoxy(1,1);    lcd_putc("an toan");
}




