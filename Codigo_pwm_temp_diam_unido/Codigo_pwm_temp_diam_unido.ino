
//////////////////////////////////////////////////////////////
//Constantes de PWM
#define RELAY1 13 //Defining the pin 7 of the Arduino for the 4 relay module
//////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////
//Constantes para el sensor de Temperatura
int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//Constantes de Sensor de diámetro
#define CLOCK_PIN 12
#define DATA_PIN  11
//////////////////////////////////////////////////////////////

void setup()
 {
 //////////////////////////////////////////////////////////////  
  // Serial Begin
  Serial.begin(9600);
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
  //Pin PWM
  pinMode(RELAY1, OUTPUT); //Defining the pin 7 of the Arduino as output3
 ////////////////////////////////////////////////////////////// 

 ////////////////////////////////////////////////////////////// 
  // Pin Sensor de diámetro
  pinMode(CLOCK_PIN, INPUT);
  pinMode(DATA_PIN, INPUT);
////////////////////////////////////////////////////////////// 
 
 }

////////////////////////////////////////////////////////////// 
//Mas constantes de Sensor de diámetro
char buf[20];
unsigned long tmpTime;
int sign;
int inches;
long value;
float result;
float result_final;
bool mm = true; //define mm to false if you want inces values
////////////////////////////////////////////////////////////// 


void loop()
 {

  ////////////////////////////////////////////////////////////// 
  //While de Sensor de temperatura
  while(digitalRead(CLOCK_PIN)==LOW) {}
  tmpTime=micros();
  while(digitalRead(CLOCK_PIN)==HIGH) {}
  if((micros()-tmpTime)<500) return;
  readCaliper(); 
  buf[0]=' ';
  dtostrf(result,6,3,buf+1); strcat(buf," in ");  
  dtostrf(result*2.54,6,3,buf+1); strcat(buf," cm "); 

  //Condicional para imprimir en mm ek diámetro del filamento
  if(mm)
  {
    Serial.print("Diámetro: "); 
    Serial.print(result_final); 
    Serial.println(" mm");    
    delay(1000);
  }
   ////////////////////////////////////////////////////////////// 
 
 
 
 
 ////////////////////////////////////////////////////////////// 
  //programa Sensor Temperatura con PWM
  Vo = analogRead(ThermistorPin);
  R2 = R1 * (1023.0 / (float)Vo - 1.0);
  logR2 = log(R2);
  T = (1.0 / (c1 + c2*logR2 + c3*logR2*logR2*logR2));
  T = T - 273.15;

     if (T<=185){
       //Serial.println("Encender");
       digitalWrite(RELAY1,LOW); // This will Turn ON the relay 1
       }else{
         digitalWrite(RELAY1,HIGH); // This will Turn OFF the relay 1
         //Serial.println("Apagar");
       }

       Serial.print("Temperature: "); 
       Serial.print(T);
       Serial.println(" C"); 
       delay(1000);
 ////////////////////////////////////////////////////////////// 
   }


////////////////////////////////////////////////////////////// 
  //Función diámetro de filamento
   void readCaliper()
{
  sign=1;
  value=0;
  inches=0;
  for(int i=0;i<24;i++) {
    while(digitalRead(CLOCK_PIN)==LOW) {}
    while(digitalRead(CLOCK_PIN)==HIGH) {}
    if(digitalRead(DATA_PIN)==HIGH) {
      if(i<20) value|=(1<<i);
      if(i==20) sign=-1;
      if(i==23) inches=1; 
    }
  }
  if(mm)
  {
    result=-1.0*(value*sign)/100.0;
    result_final=result+0.48;
  }
}
//////////////////////////////////////////////////////////////7

