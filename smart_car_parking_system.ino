
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;


#define inSensor 2
#define outSensor 3

int inStatus;
int outStatus;

int countin = 4;
int countout = 0;

int in;
int out;
int now;
int pos = 0;

#define relay 5

void setup()
{
  lcd.init();
  lcd.backlight();
  //  delay(2000);
  pinMode(inSensor, INPUT);
  pinMode(outSensor, INPUT);
  myservo.attach(9);
  lcd.setCursor(0, 0);
  lcd.print("*PARKING SYSTEM*    ");
  Serial.begin(9600);
  //  lcd.setCursor(0, 0);
  //  lcd.print(" ");
  //  lcd.setCursor(0, 1);
  //  lcd.print("");
  delay(2000);

}

void loop()
{
  inStatus =  digitalRead(inSensor);
  outStatus = digitalRead(outSensor);
  if (inStatus == 0)
  {
    in = countin--;
    Serial.println("In : ");
    Serial.println(in);
    if (now > 0 && now < 5)
    {
      for (pos = 90; pos <= 180; pos += 1) {
        myservo.write(pos);
        delay(15);
      }
      delay(3000);
      for (pos = 180; pos >= 90; pos -= 1) {
        myservo.write(pos);
        delay(15);
      }
    }
//    else if (now < 0)
//    {
//in=0;
//    }
  }

  if (outStatus == 0)
  {
    out = countout--;
    Serial.println("OUT : ");
    Serial.println(out);

  }

  now = in - out;
  Serial.println(now);
  if (now <= 0)
  {
   
    lcd.setCursor(0, 0);
    lcd.print("*** SLOT FULL ***");
    lcd.setCursor(0, 1);
    lcd.print("****************");
    //    in = 0;
    //    out = 6;
    delay(500);
  }
  else if(now > 4)
  {
        lcd.setCursor(0, 0);
    lcd.print("****************");
    lcd.setCursor(0, 1);
    lcd.print("****************");
    delay(500);
  }
  else 
  {
    lcd.clear();
   

    lcd.setCursor(0, 0);
    lcd.print("TOTAL SLOT : 4");

    lcd.setCursor(0, 1);
    lcd.print("SLOT FREE : ");
    lcd.print(now);


    delay(1000);
  }
}
