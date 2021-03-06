#include <math.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  //Set the LCD I2C address

int moistureOutput = 0;

double Thermistor1(int RawADC1) {
 double temp1;
 temp1 = log(10000.0*((1024.0/RawADC1-1))); 
 temp1 = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp1 * temp1 ))* temp1 );
 temp1 = temp1 - 273.15;            //Convert Kelvin to Celcius
 return temp1;
}

double Thermistor2(int RawADC2) {
 double temp2;
 temp2 = log(10000.0*((1024.0/RawADC2-1))); 
 temp2 = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * temp2 * temp2 ))* temp2 );
 temp2 = temp2 - 273.15;            //Convert Kelvin to Celcius
 return temp2;
}



void setup()
{
  Serial.begin(9600);
  lcd.begin(16,4);   //Initialize the lcd for 16 chars 2 lines, turn on backlight
}


void loop() {
  int moistureValue = analogRead(A1);
  moistureOutput = map(moistureValue, 530, 667, 0, 99);
 Serial.println(moistureOutput);
 Serial.println(float(Thermistor1(analogRead(0))));  //Display Celsius;
 Serial.println(float(Thermistor2(analogRead(2))));  //Display Celsius;


 lcd.setCursor(0,0);
   lcd.print("Ute: "); lcd.print(Thermistor1(analogRead(0)), 1); //Print to LCD
 
 lcd.setCursor(0,1);
   lcd.print("Inne: "); lcd.print(Thermistor2(analogRead(2)), 1); //Print to LCD

 lcd.setCursor(0,2);
  lcd.print("    Jordfukt: "); lcd.print(moistureOutput); lcd.print("%"); //Print to LCD

  if(moistureOutput<20)
    {
    lcd.setCursor(0,3);
    lcd.print("       !!!ADVARSEL!!!");
    }
 
 delay(1000);
}
