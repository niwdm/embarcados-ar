#include <Wire.h>
#include "ADXL345.h"
#include "Adafruit_BMP085.h"
#define tempo 10
int frequencia;
int Pinofalante = 10;

ADXL345 acel = ADXL345();
Adafruit_BMP085 bmp;

struct Eixos { // necessário inserir todos os eixos dos sensores
  int acelX, acelY, acelZ, terremoto; // acelerômetro
  int temp, altitude; // barometro
};

Eixos eixos;

int chkTerremoto(byte interrupcao) {
  acel.setInterruptMapping( ADXL345_INT_ACTIVITY_BIT,   ADXL345_INT1_PIN );
  bool test = ((interrupcao >> ADXL345_INT_ACTIVITY_BIT  ) & 1);

  if (test == true ) {
    //sirene();
    digitalWrite(13, HIGH);
    return 1;
  } else {
    digitalWrite(13, LOW);
    return 0;
  }
}

/*void sirene () {
  for (frequencia = 550; frequencia < 1800; frequencia += 4)
  {
    tone(Pinofalante, frequencia, tempo);
    delay(1);
  }
  for (frequencia = 1800; frequencia > 550; frequencia -= 2)
  {
    tone(Pinofalante, frequencia, tempo);
    delay(1);
  }
}*/

void enviarEixos() {
  int tam = sizeof(eixos); // retorna o tamanho total em bytes
  char buff[tam]; // cria um buffer que recebe o tamanho

  memcpy(&buff, &eixos, tam); // envia o endereço do buffer, o endereço dos eixos e o tamanho total

  Serial.write('I'); // inicializar
  Serial.write((uint8_t*)&buff, tam); // converte o buff para
  Serial.write('F'); // finalizar
}

void setup() {
  pinMode(13, OUTPUT);
  Serial.begin(9600); // velocidade da forma de escrita
  pinMode(Pinofalante, OUTPUT); //Pino do buzzer
  bmp.begin(); // ligando barometro
  acel.powerOn(); // ligando o acelerômetro

  acel.setActivityX(1);
  acel.setActivityY(1);
  acel.setActivityZ(1);
  acel.setInactivityX(1);
  acel.setInactivityY(1);
  acel.setInactivityZ(1);
  acel.setActivityThreshold(60);
  acel.setInactivityThreshold(60);
  acel.setTimeInactivity(10);
  acel.setInterrupt( ADXL345_INT_ACTIVITY_BIT, 1);
  /*Serial.print("ActivityThreshold: ");
  Serial.println(acel.getActivityThreshold());
  Serial.print("InactivityThreshold: ");
  Serial.println(acel.getInactivityThreshold());*/
  //Serial.println(sizeof(eixos)); //Teste Tamanho do buffer
}

void loop() {
  acel.readAccel(&eixos.acelX, &eixos.acelY, &eixos.acelZ); // utiliza o & para obter o endereço
  eixos.terremoto = chkTerremoto(acel.getInterruptSource());
  eixos.temp = (int)bmp.readTemperature();
  eixos.altitude = (int)bmp.readAltitude();
  enviarEixos();
  
  /* //Testes
  Serial.print("Sensor byte: ");
  Serial.println(acel.getInterruptSource());
  Serial.print("X = ");
  Serial.print(eixos.acelX);
  Serial.print("\t\tY = ");
  Serial.print(eixos.acelY);
  Serial.print("\t\tZ = ");
  Serial.print(eixos.acelZ);
  Serial.print("\t\tTerremoto: ");
  Serial.println(eixos.terremoto);
  Serial.print("Temperatura: ");
  Serial.print((int)bmp.readTemperature());
  Serial.print("\t\tAltitude: ");
  Serial.println((int)bmp.readAltitude());*/


  delay(100);
}
