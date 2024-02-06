//TIR 18.01.2024
//Laboratioria 4 - Kamil Kosmela


#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,20,4);
// Ustaw adres LCD na 0x27 po 16 znakow w 2 wierszach
double cm;
double cale;
const int PIN_RED   = 6;
const int PIN_GREEN = 5;
const int PIN_BLUE  = 4;
const int BUZZ = 8;
long readUltrasonicDistance(int triggerPin, int echoPin){
  pinMode(triggerPin, OUTPUT);
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  // Ustaw trigger na stan wysoki (HIGH) na 10 mikrosekund
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  // Odczytuje echo i zwraca czas powrotu fali
  // dzwiekowej w mikrosekundach
  return pulseIn(echoPin, HIGH);
}
void setup(){
  Serial.begin(9600);
  lcd.init(); // zainicjuj 
  pinMode(PIN_RED,   OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  pinMode(PIN_BLUE,  OUTPUT);
  pinMode(BUZZ, OUTPUT);
  // Wyswietl wiadomosc poczatkowa na LCD
  lcd.backlight();
  lcd.print("--> Odleglosc <--");
  
  lcd.clear();
}
void loop(){
  cm = 0.0344/2 * readUltrasonicDistance(3, 2);
  cale = (cm / 2.54);
  lcd.setCursor(0,0);
  lcd.print("Cale");
  lcd.setCursor(4,0);
  lcd.setCursor(12,0);
  lcd.print("Cm");
  lcd.setCursor(1,1);
  lcd.print(cale, 1);
  lcd.setCursor(11,1);
  lcd.print(cm, 1);
  lcd.setCursor(14,1);
  delay(1000);
  lcd.clear();
  if (cm > 80){
    analogWrite(PIN_GREEN, 255);
    analogWrite(PIN_BLUE, 0);
    analogWrite(PIN_RED, 0);
  }
  else if (cm <= 80 && cm > 40){
    analogWrite(PIN_GREEN, LOW);
    analogWrite(PIN_RED, LOW);
    analogWrite(PIN_BLUE, 255);
  }
  else if (cm <= 40){
    analogWrite(PIN_GREEN, LOW);
    analogWrite(PIN_RED, 255);
    analogWrite(PIN_BLUE, LOW);
    tone(8, 262, 250);
  }
}
