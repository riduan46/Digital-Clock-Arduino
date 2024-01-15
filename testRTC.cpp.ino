
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <RTClib.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);
RTC_DS3231 rtc;
char daysOfTheWeek[7][4] = {" Sun", " Mon", " Tue", " Wed", " Thu", " Fri", " Sat"};
char buf[100];
String dofweek;
void setup()
{
  lcd.init();                      // initialize the lcd 
  lcd.init();
  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.begin(16, 2);
  Serial.begin(9600);
  Serial.println("Test Message...");

  Wire.begin();
  rtc.begin();
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 
  //rtc.adjust(DateTime(2024, 1, 13, 14, 8, 11));

}


void loop()
{
  DateTime now = rtc.now();

  sprintf(buf, "%02d / %02d / %02d \t %02d : %02d : %02d",now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());
  Serial.println(buf);
  lcd.clear();
  lcd.setCursor(0, 1);
  lcd.print("D:");
  lcd.print(now.day(), DEC);
  lcd.print("/");
  lcd.print(now.month(), DEC);
  lcd.print("/");
  lcd.print(now.year(), DEC);
  lcd.print(" ");
  lcd.print(rtc.getTemperature(), 0);
  lcd.print("\337C");
  

  lcd.setCursor(0, 0);
  lcd.print("T:");
  
  if (now.hour() > 12) {
    lcd.print(now.hour() - 12); // Convert to 12-hour format
    lcd.print(":");
  } else {
    lcd.print(now.hour());
    lcd.print(":");
  }
  if (now.minute() < 10) {
    lcd.print("0");
  }
  lcd.print(now.minute(), DEC);
  lcd.print(":");

  if (now.second() < 10) {
    lcd.print("0");
  }
    lcd.print(now.second(), DEC);
  if (now.hour() >= 12) {
    lcd.print("PM");
  } else {
    lcd.print("AM");
  }
  dofweek = daysOfTheWeek[now.dayOfTheWeek()];
  lcd.print(dofweek);

  delay(1000);
}
