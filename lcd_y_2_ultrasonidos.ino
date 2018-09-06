//Codigo para el modulo manejado por el arduino NANO
#include <NewPing.h>//Libreria para el control de los sensores ultrasonicos
#include <LiquidCrystal.h>//libreria para controlar la pantalla lcd
#include <Wire.h>//libreria para conexion i2c

#define MAX_DISTANCE 33//distancia maxima medida por los sensores ultrasonicos

//definicion de los sensores ultrasonicos
NewPing Comida (6, 5, MAX_DISTANCE);
NewPing Agua (4, 3, MAX_DISTANCE);

//definicion de los puertos para el control de a pantalla lcd
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

byte val = 0;

void setup() {
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  
  Serial.begin(9600);                                              
  pinMode(13,OUTPUT);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.write("INICIALIZANDO...");
  delay(5000);
  lcd.begin(16, 2);
  lcd.setCursor(6, 0);
  lcd.write("UDLA");
  delay(5000);
}

void loop() {
  

  delay(100);
  
  int c, a, p1, p2;
  
  Serial.print("Comida: ");
  Serial.print(Comida.ping_cm());
  c=Comida.ping_cm();
  p1=100-((c*100)/MAX_DISTANCE);                          
  Serial.print(" cm     " );
  delay(50);

  Serial.print("Agua: ");
  Serial.print(Agua.ping_cm());
  a=Agua.ping_cm();
  p2=100-((a*100)/MAX_DISTANCE);                             
  Serial.println(" cm     " );
  delay(50);

  if(p1 > 90){
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.write("Comida: ");
    lcd.print("ALERTA");  
    Serial.print("Alerta");
  }
  else{
    lcd.begin(16, 2);
    lcd.setCursor(0,0);
    lcd.write("Comida: ");
    lcd.print(p1);
    lcd.print("%");
    Serial.print(p1);
  }

   
   
   if(p2 > 90){
    //lcd.begin(16, 2);
      lcd.setCursor(0,1);
      lcd.write("Agua: ");
      lcd.print("ALERTA");
    Serial.print("Alerta");
  }
  else{
    lcd.setCursor(0,1);
    lcd.write("Agua: ");
    lcd.print(p2);
    lcd.print("%");
    Serial.print(p2);
  }
    
}

void requestEvent(){
  Wire.write(1);
  }
