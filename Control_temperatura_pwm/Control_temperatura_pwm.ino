#define RELAY1 13 //Defining the pin 7 of the Arduino for the 4 relay module

//Constantes del sesor3
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
int count=0;

void setup()
 {
  Serial.begin(9600);

  pinMode(RELAY1, OUTPUT); //Defining the pin 7 of the Arduino as output3
 
 }

void loop()
 {

   ////////////////////////////////////
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;
  ////////////////////////////////////7

     if (T<=150){
       //Serial.println("Encender");
       digitalWrite(RELAY1,LOW); // This will Turn ON the relay 1
       }else{
         digitalWrite(RELAY1,HIGH); // This will Turn OFF the relay 1
         //Serial.println("Apagar");
       }

       //Serial.print("Temperature: "); 
    
       if (count<=23){
       Serial.println(T);
       count=count+1;
       }else{
         Serial.println("******************************");
         Serial.println(T);
         count=0;
       }
       //Serial.println(" C"); 
       delay(1000);

   }

