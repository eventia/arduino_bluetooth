#include <SoftwareSerial.h>
SoftwareSerial BTSerial(4, 12); //7pin/D12(TX), 15pin/D4(RX)
 
void setup() 
{
  Serial.begin(9600);   //시리얼모니터
  Serial.println("Arduino is ready");
  Serial.println("Remember to select Both NL & CR in the serial monitor");
  BTSerial.begin(9600); //블루투스 시리얼
}
void loop()
{
  if (BTSerial.available()) 
    Serial.write(BTSerial.read());  //블루투스측 내용을 시리얼모니터에 출력
 
  if (Serial.available()) 
    BTSerial.write(Serial.read());  //시리얼 모니터 내용을 블루추스 측에 WRITE
 
}