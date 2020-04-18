#include <Arduino.h>
#include <TaskScheduler.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#define PIN D7
String texto = "CADENA DE PRUEBAS";
String cadenaCharEntrada = "";
bool fin_cadena = false;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
                                               NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
                                               NEO_GRB + NEO_KHZ800);

const uint16_t colors[] = {
    matrix.Color(255, 102, 0),
    matrix.Color(255, 204, 0),
    matrix.Color(128, 0, 128),
    matrix.Color(255, 0, 255)};

int x = matrix.width();
int longitud = texto.length() * 5 + 64;

int pass = 0;
void t1Callback();
void t2Callback();
void serialEvent();

Task t1(120, TASK_FOREVER, &t1Callback);
Task t2(100, TASK_FOREVER, &t2Callback);

Scheduler runner;

void setup()
{

  Serial.begin(115200);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  matrix.setTextColor(colors[0]);
  // put your setup code here, to run once:

  runner.init();
  runner.addTask(t1);
  runner.addTask(t2);
  delay(5000);
  t1.enable();
  t2.enable();
}
void loop()
{
  runner.execute();
}

void serialEvent()
{
  //Recepción de datos Seriales

  while (Serial.available())
  {                                       
    char CaracterEntrada = Serial.read(); 

    cadenaCharEntrada += CaracterEntrada; 
    if (CaracterEntrada == '\n')
    {                    
      fin_cadena = true; 
    }
  }
}

void t1Callback()
{
  matrix.fillScreen(0);
  matrix.setCursor(x, 1);
  matrix.print(texto);
  if (--x < -1 * longitud)
  {
    x = matrix.width();
    if (++pass >= 4)
      pass = 0;
    matrix.setTextColor(colors[pass]);
  }
  matrix.show();
}

void t2Callback()
{

  if (Serial.available())
  {
    serialEvent();
  }
  if (fin_cadena)
  {
    Serial.println(cadenaCharEntrada);
    texto = cadenaCharEntrada;
    cadenaCharEntrada = "";
    longitud = texto.length() * 5;
    longitud += (texto.length() % 32);
    fin_cadena = false;
    x = matrix.width();
  }
}