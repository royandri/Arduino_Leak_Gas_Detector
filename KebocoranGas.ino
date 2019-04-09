#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27 ,2,1,0,4,5,6,7,3, POSITIVE); 
SoftwareSerial SIM800L(8, 7); 
const int sensor_gas = 12;
const int alarm = 11;
const int led_hijau = 10;
const int led_merah = 9;

void setup() {
  // put your setup code here, to run once:
  lcd.begin (16,2); //LCD untuk ukuran 16x2
  pinMode(sensor_gas,INPUT);
  pinMode(alarm,OUTPUT);
  pinMode(led_hijau,OUTPUT);
  pinMode(led_merah,OUTPUT);
  kirimSMS("Sistem dijalankan");

}

void loop() {
  // put your main code here, to run repeatedly:
  int nilai = digitalRead(sensor_gas);
  if (nilai == LOW)
  {
    digitalWrite(alarm,HIGH);
    lcd.setCursor(0, 0); //baris pertama  
    lcd.print("Kondisi Ruangan:");    
    lcd.setCursor(0, 1); //baris kedua  
    lcd.print("Gas Bocor      ");
    digitalWrite(led_hijau,LOW);
    digitalWrite(led_merah,HIGH);
    kirimSMS("Gas Bocor");
  }
  if (nilai == HIGH)
  {
    digitalWrite(alarm,LOW);
    lcd.setCursor(0, 0); //baris pertama  
    lcd.print("Kondisi Ruangan:");    
    lcd.setCursor(0, 1); //baris kedua  
    lcd.print("Kadar Gas = Nol");
    digitalWrite(led_hijau,HIGH);
    digitalWrite(led_merah,LOW);
  }

}

void kirimSMS(String pesan){
  Serial.begin(9600);
  SIM800L.begin(9600);  
  SIM800L.println("AT+CMGF=1");
  Serial.println("SIM800L started at 9600");
  delay(1000);
  Serial.println("Setup Complete! SIM800L is Ready!");
  SIM800L.println("AT+CNMI=2,2,0,0,0");

  SIM800L.println("AT+CMGF=1");   
  delay(1000);  
  SIM800L.println("AT+CMGS=\"085643125167\"\r");
  delay(1000);
  SIM800L.println(pesan);
  delay(100);
  SIM800L.println((char)26);
  delay(1000);
}
