#include <LiquidCrystal.h>

#define charge 2

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

String c1 = "3600A6452DF8";
String c2 = "3600A50E79E4";
String c3 = "3600A660CA3A";
String rfid;

void setup() {
  Serial.begin(9600);
  pinMode(charge, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Mobile charging"); 
  lcd.setCursor(0, 1);
  lcd.print("System"); 
  delay(3000); 
  Serial.println("Setup Completed");
}

void loop() {
  char in[13];
  int count = 0;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Swipe Your"); 
  lcd.setCursor(0, 1);
  lcd.print("RFID card"); 
  Serial.println("Swipe your RFID Card");
  while(Serial.available() && count < 12)          
  {
    in[count]=Serial.read();
    count++;
    delay(5);
    if (count==12)
    {
      in[count] = '\0';
      Serial.println(in);
      count = 0;
      rfid=in;
    }
  }
  if(c1.equals(rfid))
  {
    Serial.println("card1 swiped");
    lcd.clear();
    lcd.home();
    lcd.print("Card1 Swiped");
    lcd.setCursor(0,1);
    lcd.print("1 minute");
    delay(2000);
    disp(1);
  }
  else if(c2.equals(rfid)){
    Serial.println("card2 swiped");
    lcd.clear();
    lcd.home();
    lcd.print("Card2 Swiped");
    lcd.setCursor(0,1);
    lcd.print("2 minutes");
    delay(2000);
    disp(2);
  }
  else if(c3.equals(rfid)){
    Serial.println("card3 swiped");
    lcd.clear();
    lcd.home();
    lcd.print("Card3 Swiped");
    lcd.setCursor(0,1);
    lcd.print("5 minutes");
    delay(2000);
    disp(5);
  }
  rfid.remove(0);
  delay(1000);
}

int disp(int check)
{
  unsigned int sec;
  sec = check*60;
  lcd.clear();
  lcd.home();
  lcd.print("Attach Cable");
  lcd.setCursor(0,1);
  lcd.print("to Mobile");
  delay(3000);
  digitalWrite(charge,1);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Total Min: ");
  lcd.print(check);
  lcd.setCursor(0, 1);
  lcd.print("Remaining: ");
  Serial.println("CHARGING STARTED...");
  while(sec > 0)
  {
    lcd.setCursor(10, 1);
    lcd.print(sec); 
    lcd.print(" ");
    delay(1000);sec--;
  }
  digitalWrite(charge,0);
  lcd.clear();
  lcd.home();
  lcd.print("Completed");
  delay(2000);
}
