/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Variables de medición e indicaciones sonoras
   Dev: Profe. Alejandro Lopez Navas
   Fecha: 15 de julio.
   link de la simulacion: 
*/

#include <Wire.h>                 //libreria para usar el protocolo i2c
#include <SparkFun_ADXL345.h>     //libreria para usar el acelerometro ADXL345
#include <SoftwareSerial.h>       //libreria para emular otro puerto serie
#include <DFRobotDFPlayerMini.h>  //libreria para usar el reproductor MP3

#define A 2
#define B 3
#define C 4
#define D 5
#define E 8
#define F 9

//Constructores
ADXL345 acc_sismo = ADXL345();        //constructor para usar el acelerometro
SoftwareSerial mp3_sismo(6, 7);       //RX 6 y TX 7
DFRobotDFPlayerMini reproductor_MP3;  //constructor para el reproductor MP3
//Variables
/*
Declaro las 3 variables, donde guardo los valores de aceleracion de caada eje
*/
unsigned int acc_X;  //aceleracion en el eje x
unsigned int acc_Y;  //aceleracion en el eje y
unsigned int acc_Z;  //aceleracion en el eje z

//Variable donde guardo la magnitud del vector aceleracion
float magnitud_acc;

//Configuraciones
void setup() {
  Serial.begin(9600);            //Inicio la comunicacion serial del arduino hacia la computadora
  mp3_sismo.begin(9600);         //Inicio la comunicacion serial emulada para el mp3
  acc_sismo.powerOn();           //Enciendo el acelerometro
  acc_sismo.setRangeSetting(8);  //Configuro la sensibbilidad del acelerometro

  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);

  //Compruebo si hay conexion con el modulo mp3
  if (!reproductor_MP3.begin(mp3_sismo)) {
    //Si no existe, me quedo aqui siempre. Ya no avanzo en el codigo
    Serial.println("No he podido comunicarme con el modulo MP3");

    while (1)
      ;
  }
  //Si la comunicacion ha sido exitosa, avanzo
  reproductor_MP3.volume(23);  //volumen al maximo
  Serial.println("Comunicacion exitosa con el reproductor MP3");
  Serial.println("Practic 2 - Ayuda profe Alejandro");
  Serial.println("reproduzco la primera cancion");
}

void loop() {

  //Leo las variables medidas por el acelerometro
  acc_sismo.readAccel(&acc_X, &acc_Y, &acc_Z);


  //obtengo la magnitud del vector aceleracion
  magnitud_acc = sqrtf((acc_X * acc_X) + (acc_Y * acc_Y) + (acc_Z * acc_Z));

  Serial.print("La magnitud del vector aceleracion es de: ");
  Serial.println(magnitud_acc);
  int mapeo_intensidad = map(magnitud_acc, 47, 75, 0, 10);


  Serial.print("El valor mapeo es de: ");
  Serial.println(mapeo_intensidad);

  if (mapeo_intensidad >= 0 && mapeo_intensidad < 2) {
    Serial.println("Primera escala de Mercalli");
    digitalWrite(A, HIGH);
    digitalWrite(B, LOW);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);

  } else if (mapeo_intensidad >= 2 && mapeo_intensidad < 4) {
    Serial.println("Segunda escala de Mercalli");
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, LOW);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);

  } else if (mapeo_intensidad >= 4 && mapeo_intensidad < 6) {
    Serial.println("Tercera escala de Mercalli");
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, LOW);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);

  } else if (mapeo_intensidad >= 6 && mapeo_intensidad < 7) {
    Serial.println("Cuarta escala de Mercalli");
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, LOW);
    digitalWrite(F, LOW);

  } else if (mapeo_intensidad >= 7 && mapeo_intensidad < 9) {
    Serial.println("Quinta escala de Mercalli");
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, LOW);

  } else if (mapeo_intensidad >= 9 && mapeo_intensidad < 100) {
    Serial.println("Sexta escala de Mercalli");
    digitalWrite(A, HIGH);
    digitalWrite(B, HIGH);
    digitalWrite(C, HIGH);
    digitalWrite(D, HIGH);
    digitalWrite(E, HIGH);
    digitalWrite(F, HIGH);

    reproductor_MP3.play(1);  //reproduzco la primera cancion
    delay(100);
  }

  else {
    Serial.println("Ay mi casa");
  }
  delay(1000);
}
