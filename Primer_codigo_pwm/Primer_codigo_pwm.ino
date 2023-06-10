#define RELAY1 13 //Defining the pin 7 of the Arduino for the 4 relay module

//Constantes de prueba
#define LONGITUD 70
#define CONSTANTE 165.0
float valor;
float Array[LONGITUD];


void setup()
 {
  Serial.begin(9600);

  pinMode(RELAY1, OUTPUT); //Defining the pin 7 of the Arduino as output
   
  //Asignar valores de las matrices e imprimirlos
  for(int i=0; i<LONGITUD; i++){
  valor = CONSTANTE + i;
  Array[i]=valor;
  }
 
 }

void loop()
 {

   for(int i=0; i<LONGITUD; i++){
     Serial.println(Array[i]);
     delay(1000);

     if (Array[i]<=185){
       //Serial.println("Encender");
       digitalWrite(RELAY1,HIGH); // This will Turn ON the relay 1
       }else{
         digitalWrite(RELAY1,LOW); // This will Turn OFF the relay 1
         //Serial.println("Apagar");
       }

   }
}
   

