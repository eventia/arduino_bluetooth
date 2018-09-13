#include <SoftwareSerial.h>

SoftwareSerial BTSerial(4, 12); //7pin/D12(TX), 15pin/D4(RX)

//LEFT A,B 앞(디지털핀 쪽)
int LEFT_AOUT_ONE=6; //9pin
int LEFT_BOUT_ONE=5; //8pin

//LEFT A,B 뒤(아날로드핀 쪽)
int LEFT_AOUT_TWO=15; //20pin, A1
int LEFT_BOUT_TWO=14; //19pin, A0

//RIGHT A,B 앞(디지털핀 쪽)
int RIGHT_AOUT_ONE=10; //13pin;
int RIGHT_BOUT_ONE=9; //12pin;

//int RIGHT_AOUT_ONE=11; //13pin;
//int RIGHT_BOUT_ONE=3; //12pin;

//RIGHT A,B (아날로드핀 쪽)
int RIGHT_AOUT_TWO=17; //22pin, A3
int RIGHT_BOUT_TWO=16; //21pin, A2

//Sub Motor
int freq = 20000; // 20 milliseconds (50Hz);
int minPulse = 600; // 600 microseconds
int maxPulse = 2400; //2400 microseconds
int SUB_MOTOR1 = 3; //3pin
int SUB_MOTOR2 = 11; //11pin

//Sensor
int TrigPin = 20;
int EchoPin = 2;

int compareValue;

int MotorSpeed = 0;
int SubMotorSpeed = 0;
int SubMotorTemp = 0;
int MotorNameValue;

void setup() {
  Serial.begin(9600); // Arduino to Computer
  BTSerial.begin(9600); // BLE to Arduino
  Serial.println("Enter AT Commands");
  
  //Pin Setting
  //앞바퀴
  pinMode(LEFT_AOUT_ONE, OUTPUT);
  pinMode(LEFT_BOUT_ONE, OUTPUT);
  pinMode(RIGHT_AOUT_ONE, OUTPUT);
  pinMode(RIGHT_BOUT_ONE, OUTPUT);
  //뒷바퀴
  pinMode(LEFT_AOUT_TWO, OUTPUT);
  pinMode(LEFT_BOUT_TWO, OUTPUT);
  pinMode(RIGHT_AOUT_TWO, OUTPUT);
  pinMode(RIGHT_BOUT_TWO, OUTPUT);
  
  //sub motor
  pinMode(SUB_MOTOR1, OUTPUT);
  pinMode(SUB_MOTOR2, OUTPUT);
  digitalWrite(SUB_MOTOR1, LOW);
  digitalWrite(SUB_MOTOR2, LOW);

  //sensor
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop() {
  //setSensor();
  
  if(BTSerial.available()>0){
    compareValue = BTSerial.read();
    Serial.println(compareValue);
    if(compareValue >= 49 && compareValue <= 122){
      MotorNameValue = compareValue;
    }
  }
  
  //Servo Motor 첫번째
  if(compareValue == 'A'){ setSubMotor(0, SUB_MOTOR1); } //0도
  if(compareValue == 'B'){ setSubMotor(45, SUB_MOTOR1); } //45도
  if(compareValue == 'C'){ setSubMotor(90, SUB_MOTOR1); } //90도
  if(compareValue == 'D'){ setSubMotor(135, SUB_MOTOR1); } //135도
  if(compareValue == 'E'){ setSubMotor(180, SUB_MOTOR1); } //180도
  
  //Servo Motor 두번째
  if(compareValue == 'F'){ setSubMotor(0, SUB_MOTOR2); } //0도
  if(compareValue == 'G'){ setSubMotor(45, SUB_MOTOR2); } //45도
  if(compareValue == 'H'){ setSubMotor(90, SUB_MOTOR2); } //90도
  if(compareValue == 'I'){ setSubMotor(135, SUB_MOTOR2); } //135도
  if(compareValue == 'J'){ setSubMotor(180, SUB_MOTOR2); } //180도
  
  //Main Motor Speed
  if(compareValue == 'j') { MotorSpeed = 50; }
  if(compareValue == 'k') { MotorSpeed = 100; }
  if(compareValue == 'l') { MotorSpeed = 140; }
  if(compareValue == 'm') { MotorSpeed = 180; }
  if(compareValue == 'n') { MotorSpeed = 220; }
  if(compareValue == 'o') { MotorSpeed = 255; }
  
  //Main Motor
  //앞으로 왼쪽으로 눌렀을 때.
  if(MotorNameValue == 'a' && MotorSpeed >= 0){
    MotorControl_Front(0, 0, 180, 0);
    MotorControl_Back(0, 0, 180, 0);
  }
  //앞으로 눌렀을때
  if(MotorNameValue == 'b' && MotorSpeed >= 0){
    MotorControl_Front(MotorSpeed, 0, MotorSpeed, 0);
    MotorControl_Back(255, 0, 255, 0);
  }
  //앞으로 오른쪽으로 눌렀을 때.
  if(MotorNameValue == 'c' && MotorSpeed >= 0){
    MotorControl_Front(180, 0, 0, 0);
    MotorControl_Back(180, 0, 0, 0);
  }
  //왼쪽 눌렀을 때
  if(MotorNameValue == 'd' && MotorSpeed >= 0){
    MotorControl_Front(0, 180, 180, 0);
    MotorControl_Back(0, 180, 180, 0);
  }
  //중지 눌렀을 때
  if(MotorNameValue == 'e' && MotorSpeed >= 0){
    MotorControl_Front(0, 0, 0, 0);
    MotorControl_Back(0, 0, 0, 0);
  }
  //오른쪽 눌렀을 때
  if(MotorNameValue == 'f' && MotorSpeed >= 0){
    MotorControl_Front(180, 0, 0, 180);
    MotorControl_Back(180, 0, 0, 180);
  }
   //뒤로 왼쪽 눌렀을 때
  if(MotorNameValue == 'g' && MotorSpeed >= 0){
    MotorControl_Front(0, 0, 0, 180);
    MotorControl_Back(0, 0, 0, 180);
  }
   //뒤로 눌렀을 때
  if(MotorNameValue == 'h' && MotorSpeed >= 0){
    MotorControl_Front(0, MotorSpeed, 0, MotorSpeed);
    MotorControl_Back(0, 255, 0, 255);
  }
   //뒤로 오른쪽 눌렀을 때
  if(MotorNameValue == 'i' && MotorSpeed >= 0){
    MotorControl_Front(0, 180, 0, 0);
    MotorControl_Back(0, 180, 0, 0);
  }
  //컨트롤 3번 _ 1
   if(MotorNameValue == 'p' && MotorSpeed >= 0){
      analogWrite(LEFT_AOUT_ONE, MotorSpeed);
  }
   if(MotorNameValue == 'q' && MotorSpeed >= 0){
      analogWrite(LEFT_BOUT_ONE, MotorSpeed);
  }
   if(MotorNameValue == 'x' && MotorSpeed >= 0){
      analogWrite(LEFT_BOUT_ONE, 0);
       analogWrite(LEFT_AOUT_ONE, 0);
  }
  //컨트롤 3번 _ 2
  if(MotorNameValue == 'r' && MotorSpeed >= 0){
      analogWrite(RIGHT_AOUT_ONE, MotorSpeed);
  }
   if(MotorNameValue == 's' && MotorSpeed >= 0){
      analogWrite(RIGHT_BOUT_ONE, MotorSpeed);
  }
  if(MotorNameValue == 'y' && MotorSpeed >= 0){
      analogWrite(RIGHT_AOUT_ONE, 0);
       analogWrite(RIGHT_BOUT_ONE, 0);
  }
  //컨트롤 3번 _ 3
  if(MotorNameValue == 't' && MotorSpeed >= 0){
      analogWrite(LEFT_AOUT_TWO, MotorSpeed);
  }
   if(MotorNameValue == 'u' && MotorSpeed >= 0){
      analogWrite(LEFT_BOUT_TWO, MotorSpeed);
  }
  if(MotorNameValue == 'z' && MotorSpeed >= 0){
      analogWrite(LEFT_AOUT_TWO, 0);
       analogWrite(LEFT_BOUT_TWO, 0);
  }
   //컨트롤 3번 _ 4
  if(MotorNameValue == 'v' && MotorSpeed >= 0){
      analogWrite(RIGHT_AOUT_TWO, MotorSpeed);
  }
   if(MotorNameValue == 'w' && MotorSpeed >= 0){
      analogWrite(RIGHT_BOUT_TWO, MotorSpeed);
  }
  if(MotorNameValue == '1' && MotorSpeed >= 0){
      analogWrite(RIGHT_AOUT_TWO, 0);
       analogWrite(RIGHT_BOUT_TWO, 0);
  }

   //컨트롤 4번 _ 1
  if(MotorNameValue == '2' && MotorSpeed >= 0){
       analogWrite(LEFT_AOUT_ONE, MotorSpeed);
       analogWrite(RIGHT_AOUT_ONE, MotorSpeed);
  }
   if(MotorNameValue == '3' && MotorSpeed >= 0){
      analogWrite(LEFT_BOUT_ONE, MotorSpeed);
       analogWrite(RIGHT_BOUT_ONE, MotorSpeed);
  }
  if(MotorNameValue == '6' && MotorSpeed >= 0){
       analogWrite(LEFT_BOUT_ONE, 0);
       analogWrite(RIGHT_BOUT_ONE, 0);
       analogWrite(LEFT_AOUT_ONE, 0);
       analogWrite(RIGHT_AOUT_ONE, 0);
  }
  //컨트롤 4번 _ 2
  if(MotorNameValue == '4' && MotorSpeed >= 0){
      analogWrite(LEFT_AOUT_TWO, MotorSpeed);
       analogWrite(RIGHT_AOUT_TWO, MotorSpeed);
  }
   if(MotorNameValue == '5' && MotorSpeed >= 0){
      analogWrite(LEFT_BOUT_TWO, MotorSpeed);
       analogWrite(RIGHT_BOUT_TWO, MotorSpeed);
  }
  if(MotorNameValue == '7' && MotorSpeed >= 0){
     analogWrite(LEFT_AOUT_TWO, 0);
       analogWrite(RIGHT_AOUT_TWO, 0);
       analogWrite(LEFT_BOUT_TWO, 0);
       analogWrite(RIGHT_BOUT_TWO, 0);
  }
  
  
}

//sensor
void setSensor(){
  long duration, distance;    //기본 변수 선언
 
  //Trig 핀으로 10us의 pulse 발생
  digitalWrite(TrigPin, LOW);        //Trig 핀 Low
  delayMicroseconds(2);            //2us 유지
  digitalWrite(TrigPin, HIGH);    //Trig 핀 High
  delayMicroseconds(10);            //10us 유지
  digitalWrite(TrigPin, LOW);        //Trig 핀 Low
 
  //Echo 핀으로 들어오는 펄스의 시간 측정
  duration = pulseIn(EchoPin, HIGH);        //pulseIn함수가 호출되고 펄스가 입력될 때까지의 시간. us단위로 값을 리턴.
 
  //음파가 반사된 시간을 거리로 환산
  //음파의 속도는 340m/s 이므로 1cm를 이동하는데 약 29us.
  //따라서, 음파의 이동거리 = 왕복시간 / 1cm 이동 시간 / 2 이다.
  distance = duration / 29 / 2;        //센치미터로 환산
  
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
 
  delay(300);
}

//Servo Motor
void setSubMotor(int Speed, int pin){
  SubMotorSpeed = Speed;
  if(SubMotorTemp <= SubMotorSpeed){
    for (int angle = SubMotorTemp; angle < SubMotorSpeed; angle++){
      setServo(angle, pin);
      Serial.println(angle);        //각도 값 출력
      delay(10);                    //delay로 각도의 변화 속도를 조절
    }
  }else {
    for (int angle = SubMotorTemp; angle > SubMotorSpeed; angle--){
      setServoDown(angle, pin);
      Serial.println(angle);        //각도 값 출력
      delay(10);                    //delay로 각도의 변화 속도를 조절
    }
  }
  SubMotorTemp = SubMotorSpeed;
}

//Main Motor A
void MotorControl_Front(int front_left_a, int front_left_b, int front_right_a, int front_right_b){
  //앞바퀴 왼쪽
  analogWrite(LEFT_AOUT_ONE, front_left_a);
  analogWrite(LEFT_BOUT_ONE, front_left_b);
        
  //앞바퀴 오른쪽
  analogWrite(RIGHT_AOUT_ONE, front_right_a);
  analogWrite(RIGHT_BOUT_ONE, front_right_b);
}

//Main Motor B
void MotorControl_Back(int back_left_a, int back_left_b, int back_right_a, int back_right_b){
  //뒷바퀴 왼쪽
  analogWrite(LEFT_AOUT_TWO, back_left_a);
  analogWrite(LEFT_BOUT_TWO, back_left_b);

  //뒷바퀴 오른쪽
  analogWrite(RIGHT_AOUT_TWO, back_right_a);
  analogWrite(RIGHT_BOUT_TWO, back_right_b);
}

void setServo(int degree, int servoPin) {
  int hTime = 0;
  int lTime = 0;
  
  if(degree < 0) degree = 0;
  if(degree > 180) degree = 180;
  
  hTime = (int)(minPulse + ((maxPulse-minPulse) / 180.0 * degree));
  lTime = freq - hTime;

  Serial.println(hTime);
  Serial.println(lTime);
  
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(hTime);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(lTime);
}

void setServoDown(int degree, int servoPin) {
  int hTime = 0;
  int lTime = 0;
  
  if(degree < 0) degree = 0;
  if(degree > 180) degree = 180;
  
  hTime = (int)(minPulse + ((maxPulse-minPulse) / 180.0 * degree));
  lTime = freq - hTime;

  Serial.println(hTime);
  Serial.println(lTime);

  
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(hTime);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(lTime);
}

