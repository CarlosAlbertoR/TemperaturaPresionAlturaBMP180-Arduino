#include <SFE_BMP180.h> //Include the library by barometric presion sensor
#include <Wire.h>

//Sensor declaration
SFE_BMP180 bmp180;

//Initial data
double SeaLevelPresion=1013.25; //Sea level presion in height of 0 m.a.s.l.

void setup() {
  //Serial comunication speed
  Serial.begin(9600);

  //Condition that validates that the BMP180 started correctly
  if (bmp180.begin())
    Serial.println("BMP180 started successfully.");
  else{
    Serial.println("Error starting BMP180.");
    while(1); //Infinite loop
  }
}

void loop() {
  //Data definition
  char status;
  double T,P,H;
  
  //Temperature reading start
  status = bmp180.startTemperature();
  
  //Condition that validates the operation of the BMP180
  if (status != 0) {   
    //Pause to finish reading
    delay(status); 
    
    //Get the temperature
    status = bmp180.getTemperature(T); 
    
    //Condition that validates the operation of the BMP180
    if (status != 0) {
      //Pressure reading start
      status = bmp180.startPressure(3);
      if (status != 0) {        
        //Pause to finish reading 
        delay(status);    
       
       //Get the pressure
        status = bmp180.getPressure(P,T);
        
        //Condition that validates the operation of the BMP180
        if (status != 0) { 
          /*------Calculate the altitude--------*/
          H= bmp180.altitude(P,SeaLevelPresion);
          
          //Data printing
          Serial.print("Temperature: ");
          Serial.print(T);
          Serial.print(" *C, ");
          Serial.print("Presion: ");
          Serial.print(P);
          Serial.print(" hPa, ");     
          Serial.print("Height: ");
          Serial.print(H);
          Serial.println(" m.a.s.l.");    
        }      
      }      
    }   
  } 
  //Delay of 1 second
  delay(1000);
}
