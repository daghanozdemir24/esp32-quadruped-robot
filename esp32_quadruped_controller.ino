#include "BluetoothSerial.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

BluetoothSerial SerialBT;
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

// Her bacağın anlık konumunu takip eden değişkenler
int pos0 = 375, pos1 = 375, pos2 = 375, pos3 = 375;
const int ADIM = 50; // Her tuşa basışta motorun ne kadar döneceği
const int ORTA = 375; // 90 derece (Sıfırlama noktası)

void setup() {
  SerialBT.begin("Daghan_Robot_Master"); 
  pwm.begin();
  pwm.setPWMFreq(50); 
  dur(); 
}

void loop() {
  if (SerialBT.available()) {
    char k = SerialBT.read();
    
    switch(k) {
      // SAĞ ÖN BACAK (B0) - Ard arda basılabilir
      case 'a': pos0 += ADIM; if(pos0 > 600) pos0 = 600; pwm.setPWM(0, 0, pos0); break;
      case 'b': pos0 -= ADIM; if(pos0 < 150) pos0 = 150; pwm.setPWM(0, 0, pos0); break;

      // SOL ÖN BACAK (B1) - Ard arda basılabilir
      case 'c': pos1 += ADIM; if(pos1 > 600) pos1 = 600; pwm.setPWM(1, 0, pos1); break;
      case 'd': pos1 -= ADIM; if(pos1 < 150) pos1 = 150; pwm.setPWM(1, 0, pos1); break;

      // SAĞ ARKA BACAK (B2) - Ard arda basılabilir
      case 'e': pos2 += ADIM; if(pos2 > 600) pos2 = 600; pwm.setPWM(2, 0, pos2); break;
      case 'f': pos2 -= ADIM; if(pos2 < 150) pos2 = 150; pwm.setPWM(2, 0, pos2); break;

      // SOL ARKA BACAK (B3) - Ard arda basılabilir
      case 'g': pos3 += ADIM; if(pos3 > 600) pos3 = 600; pwm.setPWM(3, 0, pos3); break;
      case 'h': pos3 -= ADIM; if(pos3 < 150) pos3 = 150; pwm.setPWM(3, 0, pos3); break;

      // OTOMATİK HAREKETLER (Senin istediğin 3 adımlık seri hareketler)
      case 'F': for(int i=0; i<3; i++) yuruIleri(); break; 
      case 'B': for(int i=0; i<3; i++) yuruGeri();  break;
      
      // DÖNÜŞLER
      case '1': sagaDon(); break; // Sağa Dönüş
      case '2': solaDon(); break; // Sola Dönüş
      
      // DURDUR VE TÜMÜNÜ MERKEZLE (Sıfırla)
      case 'S': dur(); break; 
    }
  }
}

void dur() {
  pos0 = ORTA; pos1 = ORTA; pos2 = ORTA; pos3 = ORTA;
  for(int i=0; i<4; i++) pwm.setPWM(i, 0, ORTA);
}

void yuruIleri() {
  pwm.setPWM(0, 0, 420); pwm.setPWM(3, 0, 420); delay(200);
  pwm.setPWM(1, 0, 330); pwm.setPWM(2, 0, 330); delay(200);
  dur(); delay(100);
}

void yuruGeri() {
  pwm.setPWM(0, 0, 330); pwm.setPWM(3, 0, 330); delay(200);
  pwm.setPWM(1, 0, 420); pwm.setPWM(2, 0, 420); delay(200);
  dur(); delay(100);
}

void sagaDon() {
  pwm.setPWM(1, 0, 320); pwm.setPWM(3, 0, 320); delay(300);
  dur();
}

void solaDon() {
  pwm.setPWM(0, 0, 430); pwm.setPWM(2, 0, 430); delay(300);
  dur();
}