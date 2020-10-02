#include <SFE_BMP180.h>
#include <Wire.h>

//Declaracin de Sensores
SFE_BMP180 bmp180;

//Datos iniciales
double PresionNivelMar=1013.25; //Presion sobre el nivel del mar en altura 0 m.s.n.m.

void setup() {
  //Velociad de comunicacion serial
  Serial.begin(9600);

  //Condicion que valida que el BMP180 se inicio correctamente
  if (bmp180.begin())
    Serial.println("BMP180 iniciado correctamente");
  else{
    Serial.println("Error al iniciar el BMP180");
    while(1); // bucle infinito
  }
}

void loop() {
  //Definicion de datos
  char status;
  double T,P,A;
  
  //Inicio de lectura de temperatura
  status = bmp180.startTemperature();
  
  //Condicion que valida el funcionamiento del BMP180
  if (status != 0) {   
    //Pausa para que finalice la lectura
    delay(status); 
    
    //Obtener la temperatura
    status = bmp180.getTemperature(T); 
    
    //Condicion que valida el funcionamiento del BMP180
    if (status != 0) {
      //Inicio lectura de presión
      status = bmp180.startPressure(3);
      if (status != 0) {        
        //Pausa para que finalice la lectura  
        delay(status);    
       
       //Obtenemos la presión 
        status = bmp180.getPressure(P,T);
        
        //Condicion que valida el funcionamiento del BMP180
        if (status != 0) { 
          //-------Calculamos la altitud--------
          A= bmp180.altitude(P,PresionNivelMar);
          
          //Impresion de datos
          Serial.print("Temperatura: ");
          Serial.print(T);
          Serial.print(" *C , ");
          Serial.print("Presion: ");
          Serial.print(P);
          Serial.print(" mb , ");     
          Serial.print("Altitud: ");
          Serial.print(A);
          Serial.println(" m s.n.m.");    
        }      
      }      
    }   
  } 
  //Espera de 1 segundo
  delay(1000);
}
