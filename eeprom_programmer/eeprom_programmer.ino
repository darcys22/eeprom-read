#include <stdint.h>

#define CE 8
#define SK 9
#define DI 10
#define DO 11

void setup() {
    pinMode(CE, OUTPUT);
    digitalWrite(CE, HIGH);
    
    pinMode(SK, OUTPUT);
    digitalWrite(SK, LOW);
    
    pinMode(DI, OUTPUT);
    digitalWrite(DI, LOW);
    
    pinMode(DO, INPUT);
    
    Serial.begin(4800);
}

void pin(bool value) {
  if (value){
    digitalWrite(DI,HIGH);

  } else {
    digitalWrite(DI,LOW);}

  delay(2);
  digitalWrite(SK, HIGH);
  delay(2);
  digitalWrite(SK, LOW);
}

void Rcl(){
  pin(true);  
  pin(true);
  pin(true);
  pin(false);
  pin(true);
  pin(true);
  pin(false);
  pin(true);

}

void Read(){
    pin(true);
    pin(true);
    pin(true);
}


uint16_t readByte() {
  uint16_t data = 0;
  uint16_t mask = 0x1;
  for (int i = 0; i < 16; i++) {
    digitalWrite(SK, HIGH);
    if (digitalRead(DO) == HIGH) {
      data |= mask;
    }
    mask = mask << 1;
    digitalWrite(SK, LOW);
  }
  return data;
}
  

void loop() {
    uint8_t addr[16];
    Rcl();
    for (int count = 0; count < 16; count++){
      addr[count] = count;
      pin(true);
      int i = 0;
      uint8_t mask = 0x8;
      while (i < 4){
        if ((addr[count] & mask) != 0){
          pin(true);
        } else {
          pin(false);
        }
        mask = mask >> 1;
        i++;
      }
      Read();
      uint16_t b = readByte();
      Serial.print("0x");
      Serial.print(addr[count]);
      Serial.print(": ");
      Serial.print(b, HEX);
      Serial.print(" ");
      delay(10);
  }
  delay(200);
  Serial.println();
  Serial.println(); 
}
      
    
