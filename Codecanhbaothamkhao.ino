#include <16F877A.h>
#fuses HS,NOWDT,NOPROTECT,NOLVP
#use delay(clock=20000000)

// Khai báo sử dụng module SIM800L và khai báo số điện thoại để nhận tin nhắn cảnh báo
#include <SIM800L.h>
#define PHONE_NUMBER "0123456789"

// Khai báo pin kết nối với cảm biến cháy
#define FIRE_SENSOR PIN_B0

// Khai báo thời gian chờ trước khi cảnh báo và thời gian đếm để gửi tin nhắn SMS
#define WAIT_TIME 30
#define SEND_TIME 300

// Biến đếm thời gian và trạng thái của cảm biến cháy
int16 wait_counter = 0;
int16 send_counter = 0;
int1 fire_detected = 0;

void main() {
   // Khởi tạo module SIM800L
   sim800_init();

   // Thiết lập chế độ input cho pin kết nối cảm biến cháy
   set_tris_b(FIRE_SENSOR);

   // Vòng lặp chính của chương trình
   while (TRUE) {
      // Kiểm tra trạng thái của cảm biến cháy
      if (input(FIRE_SENSOR) == 0) {
         fire_detected = 1;
      }

      // Nếu đã phát hiện cháy, bắt đầu đếm thời gian và chờ cho đủ thời gian
      if (fire_detected) {
         delay_ms(1000);
         wait_counter++;

         // Nếu đếm thời gian chờ đã đủ, tiến hành gửi tin nhắn SMS cảnh báo
         if (wait_counter >= WAIT_TIME) {
            send_counter++;
            if (send_counter == 1) {
               sim800_send_sms(PHONE_NUMBER, "Cháy nhà! Nguy hiểm!");
            }
            if (send_counter >= SEND_TIME) {
               send_counter = 0;
               fire_detected = 0;
            }
         }
      } else {
         wait_counter = 0;
         send_counter = 0;
      }
   }
}
