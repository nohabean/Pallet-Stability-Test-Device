#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_MotorShield.h>

#define fwdButton 11
#define bwdButton 13

//1 step is approximately 0.197 in. based on motor speed set to 255 mm/s and no weight for 20 s
//1 step is approximately 0.178 in. based on motor speed set to 255 mm/s and weight at 10 lbs for 20 s
int steps = 0;

LiquidCrystal_I2C lcd(0x27,20,4);
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *myMotor = AFMS.getMotor(1);

void setup() 
{
  //initializes buttons
  pinMode(fwdButton, INPUT_PULLUP);
  pinMode(bwdButton, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  // initialize the lcd
  lcd.init();               
  lcd.backlight();
  lcd.setCursor(1,1);

  AFMS.begin();  // create with the default frequency 1.6KHz
 
  delay(500);
  
  // turn on motor
  myMotor->setSpeed(255);
  myMotor->run(FORWARD);
  
  //stop motor
  myMotor->run(RELEASE);
}

void loop() 
{
  while(digitalRead(fwdButton) == LOW)
  { 
    delay(1000);
    myMotor->setSpeed(255);      
    myMotor->run(FORWARD);
    delay(1000);
      
    for(int i = 0; i<1; i++)
    {
      steps--;
      if(steps <= 0)
      {
        steps = 0;
      }

      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Steps: ");
      lcd.print(steps);
    }
  }
  while(digitalRead(bwdButton) == LOW)
  {
    delay(1000);
    myMotor->setSpeed(255);
    myMotor->run(BACKWARD);
    delay(1000);
      
    for(int i = 0; i<1; i++)
    {
      steps++;

      lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("Steps: ");
      lcd.print(steps);
    }
  }

  myMotor->run(RELEASE);
}
