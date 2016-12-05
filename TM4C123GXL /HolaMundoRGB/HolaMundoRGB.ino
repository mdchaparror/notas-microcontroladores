/*Hola mundo TivaC RGB*/
#define MASK_R 0X01
#define MASK_G 0X02
#define MASK_B 0X04

void setup() {
 pinMode(RED_LED,OUTPUT);
 pinMode(GREEN_LED,OUTPUT);
 pinMode(BLUE_LED,OUTPUT);
}

void loop() {
  unsigned i;
  for(i=0;i<8;i++){
    writeRGB(i);
    delay(500);
  }
  
}
void writeRGB(unsigned int num){
  digitalWrite(RED_LED, num & MASK_R);
  digitalWrite(GREEN_LED, num & MASK_G);
  digitalWrite(BLUE_LED, num & MASK_B);
}

