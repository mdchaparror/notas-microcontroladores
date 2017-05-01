int PinX = A7;     // potentiometer on educational boosterpack connected to analog pin 5
int PinY = A6;                        // outside leads to ground and ~3V
unsigned int valX = 0;
unsigned int valY = 0; // variable to store the value read

void setup()
{
  Serial1.begin(115200);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(PinX, INPUT);
  pinMode(PinY, INPUT);
  analogReadResolution(10);
Serial1.println("hola mundo");// debug value
}

void loop()
{
  valX = analogRead(PinX);
  valY = analogRead(PinY);// read the input pin
  Serial1.print(valX);
  Serial1.print(",");
  Serial1.println(valY);// debug value
  analogWrite(BLUE_LED, valX / 4);
  delay(500);
}
