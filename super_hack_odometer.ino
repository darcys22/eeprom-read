#include <stdint.h>

#define CE 7
#define SK 6
#define DI 5
#define DO 4

void setup() {
    pinMode(CE, OUTPUT);
    digitalWrite(CE, HIGH);
    
    pinMode(SK, OUTPUT);
    digitalWrite(SK, LOW);
    
    pinMode(DI, OUTPUT);
    digitalWrite(DI, LOW);
    
    pinMode(DO, INPUT);
    
    Serial.begin(115200);
}

void pin(String value) {
  if (value = "HIGH"){
    digitalWrite(DI,HIGH);
  } else {
    digitalWrite(DI,LOW);}
  digitalWrite(SK, HIGH);
  digitalWrite(SK, LOW);
}

void Rcl(){
  pin("HIGH");  
  pin("HIGH");
  pin("HIGH");
  pin("LOW");
  pin("HIGH");
  pin("HIGH");
  pin("LOW");
  pin("HIGH");
}

void Read(){
    pin("HIGH");
    pin("HIGH");
    pin("HIGH");
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
  for (int i = 0; i<16; i++){
    addr[i] = i;}
  Rcl();
  for (int count = 0; count < 15; count++){
      pin("HIGH");
      int i = 0;
      uint8_t mask = 0x1000;
      while (i < 3){
        if (addr[count] && mask){
          pin("HIGH");
        } else {
          pin("LOW");
        }
        mask = mask >> 1;
        i++;
      }
      Read();
      uint16_t b = readByte();
      Serial.print(b, HEX);
      Serial.print(" ");
  }
}
      
    
