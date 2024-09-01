#include <LiquidCrystal_I2C.h>      //Library LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2); //Alamat I2C

#define SensorpH A0                 //Sensor pH pada pin A0
#define pHup 8
#define pHdown 9

float teganganPh7 = 2.73;   //Nilai kalibrasi
float teganganPh4 = 3.3;    //Nilai kalibrasi
float Po;

void setup() {
  lcd.init();                 //Mulai LCD
  lcd.backlight();            //Nyalakan backlight
  pinMode(pHup, OUTPUT);      //Setting I/O
  pinMode(pHdown, OUTPUT);
  digitalWrite(pHup, HIGH);   //Kondisi awal relay
  digitalWrite(pHdown, HIGH);
}

void loop() {
  int sensorValue = analogRead(SensorpH);         //Baca Sensor
  float voltage = sensorValue * (5.0 / 1023.0);   //Konversi menjadi nilai tegangan
  //Rumus mencari pH
  Po = 7.00 + ((teganganPh7 - voltage) / ((teganganPh4 - teganganPh7)/3));
  lcd.setCursor(0,0);
  lcd.print("Nilai pH = ");
  lcd.print(Po);                              //Tampilkan nilai pH

  if(Po < 6){                                 //Jika pH < 6, maka
    digitalWrite(pHup, LOW);                  //Pompa pH up menyala
    digitalWrite(pHdown, HIGH);
  }
  else if(Po > 8){
    digitalWrite(pHup, HIGH);
    digitalWrite(pHdown, LOW);
  }
  else{
    digitalWrite(pHup, HIGH);
    digitalWrite(pHdown, HIGH);
  }
  
  delay(500);
  lcd.clear();
}
