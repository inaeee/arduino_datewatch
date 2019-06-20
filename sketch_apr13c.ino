#include <SoftwareSerial.h>

SoftwareSerial Serial7Segment(7, 8); //RX pin, TX pin

int cycles = 0;

#define APOSTROPHE  5
#define COLON       4                            // 점위치
#define DECIMAL4    3                            // DECIMAL4 = 왼쪽에서 네번째 점
#define DECIMAL3    2                            // DECIMAL3 = 왼쪽에서 세번째 점
#define DECIMAL2    1                            // DECIMAL2 = 왼쪽에서 두번째 점
#define DECIMAL1    0                            // DECIMAL1 = 왼쪽에서 첫번째 점

unsigned long pre_time = 0;
unsigned long now_time = 0;

long millisTimer;
byte seconds = 0;
byte minutes2 = 0;
byte minutes = 0;
//byte hours = 0;
boolean colonOn = false;                          // colonOn = false(꺼짐), true(켜짐)
int timef;

char tempString[100]; //Used for sprintf
char read = '0';
char read2[4] = {'0'};
int count = 0;
int timeset = 0;
int timecount = 0;


char temp[10];
char temp2[10];
char tempNum[4];

const int _a = 2;
const int _b = 3;
const int _c = 4;
const int _d = 5;
const int _e = 6;
const int _f = 7;
const int _g = 8;
const int _dot = 9;
int dig1 = 10;
int dig2 = 11;
int dig3 = 12;

int Fnd_seg[10][7] = {
  {1, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1},
  {0, 1, 1, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 0, 0},
  {0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 1, 0},
  {1, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0}
};

int a = 0;
int b = 1;
int c = 0;
int d = 1;
int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;
int first, second;

void setup() {

  Serial.begin(9600);
  //Serial.println("OpenSegment Example Code");

  Serial7Segment.begin(9600);                      // Serial7Segment 초기화
  Serial7Segment.write('v');                       // 화면 초기화

  Serial7Segment.print("0001"); //Send the hour and minutes to the display

  //millisTimer = millis();                          // 아두이노 코드 실행 시작점으로부터의 경과시간(0으로 초기화됨.)

  // 초기화 : 5957 나올것. => 여기다가 지금시간 써주면 될듯.
  //seconds = 58;
  //minutes = 23;
  Serial7Segment.write(0x77);                 // Decimal, colon, apostrophe control command
  Serial7Segment.write(1 << DECIMAL2);        // Turns on colon, apostrophoe, and far-right decimal

  pinMode(_a, OUTPUT);
  pinMode(_b, OUTPUT);
  pinMode(_c, OUTPUT);
  pinMode(_d, OUTPUT);
  pinMode(_e, OUTPUT);
  pinMode(_f, OUTPUT);
  pinMode(_g, OUTPUT);
  pinMode(_dot, OUTPUT);
  pinMode(dig1, OUTPUT);
  pinMode(dig2, OUTPUT);
  pinMode(dig3, OUTPUT);
}

void Fnd_Write(int row) {
  int seg_Pin = 2;

  for (int segPos = 0; segPos < 7; segPos++) {
    digitalWrite(seg_Pin, Fnd_seg[row][segPos]);
    seg_Pin++;
  }
}

void loop()
{
  if (a == 0)
    first = jTOs(a, b, c, d);
  else
    second = oTOd(a, b, c, d);

}

int jTOs(int a, int b, int c, int d) {
  int m1 = a, m2, d1, d2, timer;
  cnt1 = 0; cnt3 = 0;

  for (m2 = 1; m2 < 10; m2++) {
    if (cnt1 < 1) {
      m2 = b;
      cnt1++;
    }
    for (d1 = 0; d1 < 4; d1++) {
      if (cnt2 < 1) {
        d1 = c;
        cnt2++;
      }
      for (d2 = 0; d2 < 10; d2++) {
        if (cnt3 < 1) {
          d2 = d;
          cnt3++;
        }
        if (d1 == 0 && d2 == 0)
          continue;
        if ((m2 == 2 && d1 == 2 && d2 > 8) || (m2 == 2 && d1 == 3 && d2 >= 0))
          continue;
        else if ((m2 == 1 || m2 == 3 || m2 == 5 || m2 == 7 || m2 == 8) && d1 == 3 && d2 >= 2)
          continue;
        else if ((m2 == 4 || m2 == 6 || m2 == 9) && d1 == 3 && d2 > 0)
          continue;
        if (m2 == 9 && d1 == 3 && d2 > 1) {
          continue;
        }
        timecount = 0;
        timef = clock();
        int xx = 0;
        while (timef != 0 || timecount == 0) {
          //timef = clock();
          while (xx < 1010) {
            //timef = clock();
            digitalWrite(dig1, LOW);
            digitalWrite(dig2, LOW);
            digitalWrite(dig3, HIGH);
            digitalWrite(9, LOW);
            Fnd_Write(m2);
            delay(5);
            digitalWrite(dig1, LOW);
            digitalWrite(dig2, HIGH);
            digitalWrite(dig3, LOW);
            digitalWrite(9, HIGH);
            Fnd_Write(d1);
            delay(5);
            digitalWrite(dig1, HIGH);
            digitalWrite(dig2, LOW);
            digitalWrite(dig3, LOW);
            digitalWrite(9, HIGH);
            Fnd_Write(d2);
            delay(5);
            xx++;
          }
        }
         // timef = clock();
          if (clock() == 0) {
            timecount++;
          }
          //timef = clock();
          digitalWrite(dig1, LOW);
          digitalWrite(dig2, LOW);
          digitalWrite(dig3, HIGH);
          digitalWrite(9, LOW);
          Fnd_Write(m2);
          delay(5);
          digitalWrite(dig1, LOW);
          digitalWrite(dig2, HIGH);
          digitalWrite(dig3, LOW);
          digitalWrite(9, HIGH);
          Fnd_Write(d1);
          delay(5);
          digitalWrite(dig1, HIGH);
          digitalWrite(dig2, LOW);
          digitalWrite(dig3, LOW);
          digitalWrite(9, HIGH);
          Fnd_Write(d2);
          delay(5);
        
      }
    }
  }
  return oTOd(1, 0, 0, 1);
}

int oTOd(int a, int b, int c, int d) {
  int m1 = a, m2, d1, d2, timer;
  cnt3 = 0;

  for (m2 = 0; m2 < 3; m2++) {
    if (cnt1 < 1) {
      m2 = b;
      cnt1++;
    }
    for (d1 = 0; d1 < 4; d1++) {
      if (cnt2 < 1) {
        d1 = c;
        cnt2++;
      }
      for (d2 = 0; d2 < 10; d2++) {
        if (cnt3 < 1) {
          d2 = d;
          cnt3++;
        }
        if (d1 == 0 && d2 == 0)
          continue;
        if ((m2 == 0 || m2 == 2) && d1 == 3 && d2 > 1)
          continue;
        else if (m2 == 1 && d1 == 3 && d2 > 0)
          continue;
        if (m1 == 1 && m2 == 2 && d1 == 3 && d2 > 1) {
          continue;
        }
        timer = 0;
        while (timer < 35) {



          if (timer < 18) {
            digitalWrite(dig1, LOW);
            digitalWrite(dig2, LOW);
            digitalWrite(dig3, HIGH);
            digitalWrite(9, HIGH);
            Fnd_Write(m1);
            delay(5);
            digitalWrite(dig1, LOW);
            digitalWrite(dig2, HIGH);
            digitalWrite(dig3, LOW);
            digitalWrite(9, LOW);
            Fnd_Write(m2);
            delay(5);
            digitalWrite(dig1, HIGH);
            digitalWrite(dig2, LOW);
            digitalWrite(dig3, LOW);
            digitalWrite(9, HIGH);
            Fnd_Write(d1);
            delay(5);
            timer++;
          }
          else if (timer >= 18) {
            digitalWrite(dig1, LOW);
            digitalWrite(dig2, LOW);
            digitalWrite(dig3, HIGH);
            digitalWrite(9, LOW);
            Fnd_Write(m2);
            delay(5);
            digitalWrite(dig1, LOW);
            digitalWrite(dig2, HIGH);
            digitalWrite(dig3, LOW);
            digitalWrite(9, HIGH);
            Fnd_Write(d1);
            delay(5);
            digitalWrite(dig1, HIGH);
            digitalWrite(dig2, LOW);
            digitalWrite(dig3, LOW);
            digitalWrite(9, HIGH);
            Fnd_Write(d2);
            delay(5);
            timer++;
          }
        }
      }
    }
  }
  return jTOs(0, 1, 0, 1);
}


int clock() {

  // 현재시간을 받아와서 계산 후에 출력되도록
  now_time = millis();
  if (now_time - pre_time > 1000) {
    seconds++;                                    // seconds = 초를 1씩 증가시켜줌.
    if (seconds > 59) {                           // seconds가 59보다 커지면(60초가 되면)
      seconds -= 60;                              // seconds 초기화해주고(-60),
      minutes++;                                  // minutes = 분을 1씩 증가함.
      if (minutes > 23) {                         // minutes가 23보다 커지면(23시이 되면)
        minutes -= 24;                            // minutes 초기화해주고(-60)
      }
    }


    // tempString에 시/분/초 string으로 바꿔줌.
    sprintf(tempString, "HH:MM %02d:%02d", minutes, seconds);
    if (seconds % 1 == 0)
      Serial.println(tempString);

    sprintf(tempString, "%02d%02d", minutes, seconds); // 분,초 숫자 -> 문자열로 변환
    Serial7Segment.print(tempString);                  // 이 문자열을 segment에 써줌.

    while (Serial.available()) {  //한글자 (한개의 숫자만 받으므로 while문 써서 한 줄로 변경)
      read = Serial.read();
      Serial.print(read);
      read2[count] = read;  //숫자하나하나 read2[count]에 저장
      count++;  //숫자 자리 이동
    }

    Serial7Segment.print(tempString);

    if (read != '0') {
      //Serial7Segment.begin(9600);                      // Serial7Segment 초기화
      //Serial7Segment.write('v');                       // 화면 초기화
      if (count > 0) {
        for (int i = 0; i < 4; i++) {
          if (i < 2) {
            sprintf(temp, "%c%c", read2[0], read2[1]);    // 시 첫번째 숫자와 두번째 숫자를 합침 -> temp에 저장(string)으로

            Serial.println(temp);

            minutes = atoi(temp);
          }
          else {
            sprintf(temp2, "%c%c", read2[2], read2[3]);    // 분 첫번째 숫자와 두번째 숫자를 합침 -> temp에 저장(string)으로

            Serial.print("분 설정 = ");
            Serial.println(temp2);

            seconds = atoi(temp2);
          }
        }
      }


      sprintf(tempNum, "%2s%2s", temp, temp2);    // temp 와 temp2 를 합침 -> tempNum에 저장(string)으로

      Serial7Segment.print(tempNum); //Send the hour and minutes to the display
      //Serial7Segment.write(0x77);                 // Decimal, colon, apostrophe control command
      //Serial7Segment.write(1 << DECIMAL2);

      read = '0';
      count = 0;
    }
    pre_time = now_time;
    timeset = minutes + seconds;
  }

  return timeset;
}
