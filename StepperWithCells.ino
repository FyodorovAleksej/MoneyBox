#include <TM1638.h>

TM1638 model(7, 8, 6);

float current_angle1 = 0;
int in5 = 14;
int in6 = 15;
int in7 = 16;
int in8 = 17;

int in1 = 2;
int in2 = 3;
int in3 = 4;
int in4 = 5;
const int dl = 2;


bool direct = true;

void rotor(int in1, int in2, int in3, int in4, float angle)
{
  if (angle > 0)
  {
    while (angle > 0)
    {
      digitalWrite( in1, LOW );
      digitalWrite( in2, LOW );
      digitalWrite( in3, HIGH );
      digitalWrite( in4, HIGH );
      delay(dl);
      angle -= 0.087890625;
      current_angle1 -= 0.087890625;
      if (angle <= 0)
        break;

      digitalWrite( in1, LOW );
      digitalWrite( in2, LOW );
      digitalWrite( in3, HIGH );
      digitalWrite( in4, LOW );
      delay(dl);
      angle -= 0.087890625;
      current_angle1 -= 0.087890625;
      if (angle <= 0)
        break;

      digitalWrite( in1, LOW );
      digitalWrite( in2, HIGH );
      digitalWrite( in3, HIGH );
      digitalWrite( in4, LOW );
      delay(dl);
      angle -= 0.087890625;
      current_angle1 -= 0.087890625;
      if (angle <= 0)
        break;

      digitalWrite( in1, LOW );
      digitalWrite( in2, HIGH );
      digitalWrite( in3, LOW );
      digitalWrite( in4, LOW );
      delay(dl);
      angle -= 0.087890625;
      current_angle1 -= 0.087890625;
      if (angle <= 0)
        break;

      digitalWrite( in1, HIGH );
      digitalWrite( in2, HIGH );
      digitalWrite( in3, LOW );
      digitalWrite( in4, LOW );
      delay(dl);
      angle -= 0.087890625;
      current_angle1 -= 0.087890625;
      if (angle <= 0)
        break;

      digitalWrite( in1, HIGH );
      digitalWrite( in2, LOW );
      digitalWrite( in3, LOW );
      digitalWrite( in4, LOW );
      delay(dl);
      angle -= 0.087890625;
      current_angle1 -= 0.087890625;
      if (angle <= 0)
        break;

      digitalWrite( in1, HIGH );
      digitalWrite( in2, LOW );
      digitalWrite( in3, LOW );
      digitalWrite( in4, HIGH );
      delay(dl);
      angle -= 0.087890625;
      current_angle1 -= 0.087890625;
      if (angle <= 0)
        break;

      digitalWrite( in1, LOW );
      digitalWrite( in2, LOW );
      digitalWrite( in3, LOW );
      digitalWrite( in4, HIGH );
      delay(dl);
      angle -= 0.087890625;
      current_angle1 -= 0.087890625;
      if (angle <= 0)
        break;
    }
  }
  else
  {
    while (angle < 0)
    {
      digitalWrite( in1, LOW );
      digitalWrite( in2, LOW );
      digitalWrite( in3, LOW );
      digitalWrite( in4, HIGH );
      delay(dl);
      angle += 0.087890625;
      current_angle1 += 0.087890625;
      if (angle >= 0)
        break;

      digitalWrite( in1, HIGH );
      digitalWrite( in2, LOW );
      digitalWrite( in3, LOW );
      digitalWrite( in4, HIGH );
      delay(dl);
      angle += 0.087890625;
      current_angle1 += 0.087890625;
      if (angle >= 0)
        break;

      digitalWrite( in1, HIGH );
      digitalWrite( in2, LOW );
      digitalWrite( in3, LOW );
      digitalWrite( in4, LOW );
      delay(dl);
      angle += 0.087890625;
      current_angle1 += 0.087890625;
      if (angle >= 0)
        break;

      digitalWrite( in1, HIGH );
      digitalWrite( in2, HIGH );
      digitalWrite( in3, LOW );
      digitalWrite( in4, LOW );
      delay(dl);
      angle += 0.087890625;
      current_angle1 += 0.087890625;
      if (angle >= 0)
        break;

      digitalWrite( in1, LOW );
      digitalWrite( in2, HIGH );
      digitalWrite( in3, LOW );
      digitalWrite( in4, LOW );
      delay(dl);
      angle += 0.087890625;
      current_angle1 += 0.087890625;
      if (angle >= 0)
        break;

      digitalWrite( in1, LOW );
      digitalWrite( in2, HIGH );
      digitalWrite( in3, HIGH );
      digitalWrite( in4, LOW );
      delay(dl);
      angle += 0.087890625;
      current_angle1 += 0.087890625;
      if (angle >= 0)
        break;

      digitalWrite( in1, LOW );
      digitalWrite( in2, LOW );
      digitalWrite( in3, HIGH );
      digitalWrite( in4, LOW );
      delay(dl);
      angle += 0.087890625;
      current_angle1 += 0.087890625;
      if (angle >= 0)
        break;

      digitalWrite( in1, LOW );
      digitalWrite( in2, LOW );
      digitalWrite( in3, HIGH );
      digitalWrite( in4, HIGH );
      delay(dl);
      angle += 0.087890625;
      current_angle1 += 0.087890625;
      if (angle >= 0)
        break;
    }
  }
}

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
}
int cyl = 0;
bool sign = false;
void loop() {
  byte keys = model.getButtons();
  if (sign)
  {
    model.setLEDs(keys | (0b00000001 << (cyl - 1)) | 0b10000000);
  }
  else
  {
    model.setLEDs(keys | (0b00000001 << (cyl - 1)));
  }
  
  if (keys & 0b00000001)
  {
    cyl = 1;
  }
  if (keys & 0b00000010)
  {
    cyl = 2;
  }
  if (keys & 0b00000100)
  {
    cyl = 3;
  }
  if (keys & 0b00001000)
  {
    cyl = 4;
  }
  if (keys & 0b00010000)
  {
    cyl = 5;
  }
  if (keys & 0b00100000)
  {
    cyl = 6;
  }
  while (current_angle1 >= 360)
    current_angle1 -= 360;
  while (current_angle1 <= -360)
    current_angle1 += 360;
  float deltaangle = (current_angle1 - (22.5 + (cyl - 1)*45));
  while (deltaangle >= 360)
    deltaangle -= 360;
  while (deltaangle <= -360)
    deltaangle += 360;
  if (deltaangle < 0)
  {
    sign = true;
  }
  else
  {
    sign = false;
  }
  model.setDisplayToString("1234");
  //model.setDisplayToDecNumber(abs(deltaangle), 0b00001000);
  delay(400);
  if (keys & 0b01000000)
  {
    if (deltaangle <= 180 && deltaangle >= -180)
    {
      rotor(in1, in2, in3, in4, deltaangle);
    }
    else
    {
      if (deltaangle > 0)
      {
       rotor(in1, in2, in3, in4, -(360 - deltaangle)); 
      }
      else
      {
        rotor(in1, in2, in3, in4, 360 + deltaangle);
      }
    }
  }
}

