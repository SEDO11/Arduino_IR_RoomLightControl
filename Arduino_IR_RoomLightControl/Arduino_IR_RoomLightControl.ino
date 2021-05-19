#include <Servo.h> //서보모터 라이브러리
#include <LiquidCrystal_I2C.h> //i2c모듈을 사용하는 lcd라이브러리
#include <Wire.h> //lcd라이브러리
#include <IRremote.h> //IR 리모컨 라이브러리.
IRrecv irrecv(7); // IR리모컨을 사용하기 위해 7번핀 사용 선언
decode_results results; //IR리모컨으로부터 받은 신홋값

// 0x3F I2C 주소를 가지고 있는 16x2 LCD객체를 생성합니다.
// I2C 주소는 각자가 사용하는 LCD에 맞게 수정해야 합니다.
LiquidCrystal_I2C lcd(0x27, 16, 2);
int timeset = 150; //서보 모터 움직임 시간 설정
int servoPin = 9;  //서보 모터 사용 핀 설정
Servo servo;       //서보 모터 변수 선언

void setup() 
{ 
  lcd.init();                // I2C LCD를 초기화 합니다.
  lcd.backlight();           // 초기에 I2C LCD의 백라이트를 켜줍니다.
  irrecv.enableIRIn();       // 7번핀을 통해 IR신호를 읽는다.
} 

void loop() 
{ 
   if (irrecv.decode(&results)==true){
      switch(results.value){
          case 0xFFA25D: // 불을 킨다
          servo.attach(servoPin);
          lcd.clear();                  // lcd에 있던 글자를 지운다(안쓰면 글자가 중첩됩니다.)
          lcd.setCursor(3,0);           // 0번째 줄 3번째 셀부터 입력하게 합니다.
          lcd.print("SEDO Room");       // 문구를 출력합니다.
          lcd.setCursor(3,1);           // 1번째 줄 3번째 셀부터 입력하게 합니다.
          lcd.print("Turn Off");        // 문구를 출력합니다.
          servo.write(120);             // 서보 모터로 불을 킬 수 있는 각도까지 돌린다. 
          delay(timeset);
          servo.write(80);              // 서보 모터를 초기상태(중간)로 돌린다.
          delay(timeset);
          break;
          
          case 0xFF629D: // 불을 끈다
          servo.attach(servoPin);
          lcd.clear();                  // lcd에 있던 글자를 지운다(안쓰면 글자가 중첩됩니다.)
          lcd.setCursor(3,0);           // 0번째 줄 3번째 셀부터 입력하게 합니다.
          lcd.print("SEDO Room");       // 문구를 출력합니다.
          lcd.setCursor(3,1);           // 1번째 줄 3번째 셀부터 입력하게 합니다.
          lcd.print("Turn On");         // 문구를 출력합니다.
          servo.write(50);              // 서보 모터로 불을 끌 수 있는 각도까지 돌린다. 
          delay(timeset);
          servo.write(80);              // 서보 모터를 초기상태(중간)로 돌린다.
          delay(timeset);
          break;
          
          case 0xFF6897: //절전 모드
          lcd.noBacklight(); //lcd를 끊다
          break;
      
          case 0xFF30CF: //일반 모드
          lcd.backlight(); //lcd를 킨다
          break;
      }
      servo.detach();
      irrecv.resume(); // 다음 신호 수신
  } 
}
