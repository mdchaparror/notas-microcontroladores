int PinX = A7;     // potentiometer on educational boosterpack connected to analog pin 5
int PinY = A6;                        // outside leads to ground and ~3V
unsigned int valX = 0;
unsigned int valY = 0; // variable to store the value read

void setup()
{
  Serial.begin(9600);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(PinX, INPUT);
  pinMode(PinY, INPUT);
  analogReadResolution(10);

}

void loop()
{
  valX = analogRead(PinX);
  valY = analogRead(PinY);// read the input pin
  Serial.print(valX);
  Serial.print(",");
  Serial.println(valY);// debug value
  analogWrite(BLUE_LED, valX / 4);
  delay(500);
}
