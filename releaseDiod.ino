//#include <TM1638.h>

//TM1638 model(8, 9, 7);

byte steps[8] = {B00001100, B00000100, B00000110, B00000010, B00000011, B00000001, B00001001, B00001000};
float current_angle[4] = {0.0, 0.0, 0.0, 0.0};


#define dataPin 2

#define latchPin 3
#define clockPin 4

#define dl 2

#define diod 5

#define analog1IN 14
#define analog2IN 15


int CLEAR = 820;
#define DELTA 40
#define DELTACOIN 25

byte currentCoin = 0;
int old = 1023;
int coin[8] = {255, 255, 255, 255, 255, 255, 255, 255};

#define N 8

struct Coin
{
  byte count;
  byte capacity;
};

byte dp(short money);
short FullSum(struct Coin *ans);
void copyData();

Coin copilka[N];
Coin ans[N];
Coin typoiAns[N];

void vudelMemory(Coin* newMemory) {
  newMemory[0].count = 0;       
  newMemory[0].capacity = 0.01 * 100;

  newMemory[1].count = 0;            
  newMemory[1].capacity = 0.02 * 100;

  newMemory[2].count = 0;            
  newMemory[2].capacity = 0.05 * 100;

  newMemory[3].count = 0;            
  newMemory[3].capacity = 0.1 * 100; 

  newMemory[4].count = 0;            
  newMemory[4].capacity = 0.2 * 100; 

  newMemory[5].count = 0;            
  newMemory[5].capacity = 0.5 * 100; 

  newMemory[6].count = 0; 
  newMemory[6].capacity = 1.0 * 100;

  newMemory[7].count = 0;  
  newMemory[7].capacity = 2.0 * 100;
}

struct Coin* execMoney(short getMoney)
{
  vudelMemory(ans);
  vudelMemory(typoiAns);

  if (dp(getMoney)) {
    return ans;
  }
  else {             
    return typoiAns;
  }
}

byte dp(short money) {
  if (money == 0) {
    return 1;
  }
  else {
    for (int i = N - 1; i >= 0; i--) {
      if ((FullSum(typoiAns) == 0 || FullSum(typoiAns) > money + copilka[i].capacity) && money - copilka[i].capacity < 0)
      {
        copyData();
        typoiAns[i].count++;
      }
      if (copilka[i].count != 0 && money - copilka[i].capacity >= 0) {
        ans[i].count++;
        copilka[i].count--;
        if (dp(money - copilka[i].capacity)) {
          return 1;
        }
        copilka[i].count++;
        ans[i].count--;
      }
    }
  }
  return 0;
}

void copyData() {
  for (int i = 0; i < N; i++) {
    typoiAns[i].count = ans[i].count;
  }
}

short FullSum(struct Coin *ans) {
  short sum = 0;
  for (int i = 0; i <= N; i++) {
    sum += ans[i].count * ans[i].capacity;
  }
  return sum;
}


byte detectCoin() {
  while (true) {
    int value = 1023;
    int analog1 = analogRead(analog1IN);
    if (analog1 == analogRead(analog2IN)) {
      value = analog1;
    }
    if (value < old) {
      old = value;
    }
    if ((value >= CLEAR - DELTA) && (value <= CLEAR + DELTA) && (old < CLEAR - DELTA)) {
//      model.setDisplayToDecNumber(old, 0B00001000);
      for (int  i = 0; i < 8; i++) {
        if ((old >= coin[i] - DELTACOIN) && (old <= coin[i] + DELTACOIN)) {
  //        model.setLEDs(~(0B00000001 << i));
  //        model.setDisplayToDecNumber(old, 0B00001000);
          delay(1500);
          old = 1023;
          return i;
        }
      }
      old = 1023;
    }
  }
}

void rotor(byte number, float angle)
{
  if (angle > 0)
  {
    while (angle > 0)
    {
      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001100 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001100 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle -= 0.087890625;
      current_angle[number] = current_angle[number] - 0.087890625;
      if (angle <= 0)
        break;


      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000100 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000100 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle -= 0.087890625;
      current_angle[number] = current_angle[number] - 0.087890625;
      if (angle <= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000110 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000110 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle -= 0.087890625;
      current_angle[number] = current_angle[number] - 0.087890625;
      if (angle <= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000010 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000010 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle -= 0.087890625;
      current_angle[number] = current_angle[number] - 0.087890625;
      if (angle <= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000011 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000011 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle -= 0.087890625;
      current_angle[number] = current_angle[number] - 0.087890625;
      if (angle <= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000001 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000001 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle -= 0.087890625;
      current_angle[number] = current_angle[number] - 0.087890625;
      if (angle <= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001001 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001001 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle -= 0.087890625;
      current_angle[number] = current_angle[number] - 0.087890625;
      if (angle <= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001000 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001000 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle -= 0.087890625;
      current_angle[number] = current_angle[number] - 0.087890625;
      if (angle <= 0)
        break;
    }
  }
  else
  {
    while (angle < 0)
    {
      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001000 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001000 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle += 0.087890625;
      current_angle[number] = current_angle[number] + 0.087890625;
      if (angle >= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001001 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001001 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle += 0.087890625;
      current_angle[number] = current_angle[number] + 0.087890625;
      if (angle >= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000001 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000001 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle += 0.087890625;
      current_angle[number] = current_angle[number] + 0.087890625;
      if (angle >= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000011 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000011 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle += 0.087890625;
      current_angle[number] = current_angle[number] + 0.087890625;
      if (angle >= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000010 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000010 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle += 0.087890625;
      current_angle[number] = current_angle[number] + 0.087890625;
      if (angle >= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000110 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000110 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle += 0.087890625;
      current_angle[number] = current_angle[number] + 0.087890625;
      if (angle >= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000100 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000100 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle += 0.087890625;
      current_angle[number] = current_angle[number] + 0.087890625;
      if (angle >= 0)
        break;

      if (number >= 2)
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001100 << ((number - 2) * 4));
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        digitalWrite(latchPin, HIGH);
      }
      else
      {
        digitalWrite(latchPin, LOW);
        shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
        shiftOut(dataPin, clockPin, LSBFIRST, B00001100 << (number * 4));
        digitalWrite(latchPin, HIGH);
      }
      delay(dl);
      angle += 0.087890625;
      current_angle[number] = current_angle[number] + 0.087890625;
      if (angle >= 0)
        break;
    }
  }
}

void toCyl(byte engine, byte cyl)
{
  float deltaangle = current_angle[engine] - ((cyl - 1) * 45);
  while (deltaangle >= 360)
    deltaangle -= 360;
  while (deltaangle <= -360)
    deltaangle += 360;

  if (engine == 0) {
    deltaangle = -deltaangle;
  }
  rotor(engine, deltaangle);
}

void tolk(byte engineAngle, byte engineRing, byte cyl)
{
  toCyl(engineAngle, cyl);
  rotor(engineRing, 180);
  rotor(engineRing, -180);
}

void getArray(struct Coin* answer)
{
  for (int i = 0; i < N; i++) {
    for (int j = answer[i].count; j > 0; j--) {
      tolk(3, 4, i);
    }
  }
}

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(diod, OUTPUT);

  pinMode(analog1IN, INPUT);
  pinMode(analog2IN, INPUT);

  digitalWrite(diod, HIGH);
  delay(100);
  CLEAR = analogRead(analog1IN);
 // model.setLEDs(0B00000001);

  vudelMemory(copilka);
}

void loop() {
  while (currentCoin <= 7) {
    int value = 1023;
    int analog1 = analogRead(analog1IN);
    if (analog1 == analogRead(analog2IN)) {
      value = analog1;
    }
    if (value < old) {
      old = value;
//      model.setDisplayToDecNumber(old, 0B00001000);
    }
    if ((value >= CLEAR - DELTA) && (value <= CLEAR + DELTA)  && (old < CLEAR - DELTA)) {
//      model.setDisplayToDecNumber(old, 0B00001000);
      delay(600);
      coin[currentCoin] = old;
      old = 1023;
      currentCoin++;
//      model.setLEDs(0B00000001 << currentCoin);
    }
  }

  byte cyl = detectCoin();
  digitalWrite(diod, LOW);
  toCyl(1, cyl);
  rotor(0, 180.0);
  rotor(0, -180.0);
  cyl = 1;
  toCyl(1, cyl);
  digitalWrite(diod, HIGH);
}
