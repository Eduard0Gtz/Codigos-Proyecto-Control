//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
//Variables manejables

//"diametro" (Diámetro)
//"control_signal" (velocidad)

//////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////
//motores
// Declaro mis variables y nombre de conexiones
#define dirPinspool 5 //Pin dirección de giro
#define dirPinY 9 //Pin dirección de giro

#define stepPinspool 6 //Pulsos al motor
#define stepPinY 8 //Pulsos al motor


int switchState = 0; 
//#define stepsPerRevolution 200
//////////////////////////////////////////////////////////////





//////////////////////////////////////////////////////////////
//Constantes para el PID (diametro vs velocidad)
double Kp; //proportional gain
double Ki; //integral gain
double Kd; //derivative gain
double control_signal;
int T_sampling=1000; //sample time in milliseconds (ms)
unsigned long last_time;
double total_error, last_error;
int max_control;
int min_control;
int delta_time;
int errorint;
//int input1;
int SETPOINT=1.55;
//////////////////////////////////////////////////////////////
double last_time1=0;
double current_time1;
double delta_time1;

double last_time2;
double current_time2;
double delta_time2;

double last_time3;
double current_time3;
double delta_time3;

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
  /*Serial.println("Ingresa el díametro para extruir: ");
 Serial.available();
  input1=Serial.read();
  SETPOINT=input1;*/
//////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////
// Declarar pines de salida/entrada
  pinMode(dirPinspool, OUTPUT);
 
  pinMode(stepPinspool, OUTPUT);
  

    pinMode(dirPinY, OUTPUT);
 
  pinMode(stepPinY, OUTPUT);
  ///////////////////////////////////////////////////////////

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
float diametro;
bool mm = true; //define mm to false if you want inces values
int velocidad;
////////////////////////////////////////////////////////////// 


void loop()
 {

  ////////////////////////////////////////////////////////////// 
  //While sensor de diametro
  while(digitalRead(CLOCK_PIN)==LOW) {}
  tmpTime=micros();
  while(digitalRead(CLOCK_PIN)==HIGH) {}
  if((micros()-tmpTime)<T_sampling) return;
  readCaliper(); 
  buf[0]=' ';
  dtostrf(result,6,3,buf+1); strcat(buf," in ");  
  dtostrf(result*2.54,6,3,buf+1); strcat(buf," cm "); 

  //Condicional para imprimir en mm ek diámetro del filamento
  current_time1 = millis();
  delta_time1 = current_time1 - last_time1;
  if(mm)
  {
   if (delta_time >= 1000){
    //Serial.print("Diámetro: "); 
    Serial.println(diametro); 
    //Serial.println(" mm");    
    //delay(T_sampling);
    last_time1=current_time1;
   }
  }
////////////////////////////////////////////////////////////// 

//////////////////////////////////////////////////////////////
//funcion de control
PID_Control(); //calls the PID function every T interval and outputs a control signal 
////////////////////////////////////////////////////////////// 

/////////////////////////////////////////////////////////////
// motores
   digitalWrite(dirPinspool, HIGH);
   digitalWrite(dirPinY, LOW);


  for (int i=0; i<1 ;i++){
   
   
    digitalWrite(stepPinspool, HIGH);
    
    
    last_time2=0;
    delta_time2 = 0;
    while(delta_time2<=100){
      current_time2 = millis();
      delta_time2 = current_time2 - last_time2;
      last_time2=current_time2;
    }
    //delayMicroseconds(100000);
    digitalWrite(stepPinspool, LOW);
   
    current_time3 = millis();
    last_time3=0;
    delta_time3 = current_time3 - last_time3;
    while(delta_time3<=100){
      last_time3=current_time2;
    }
    delayMicroseconds(100000);

  for (int j=0; j<velocidad ;j++){
        digitalWrite(stepPinY, HIGH);
        
        delayMicroseconds(100000);
        digitalWrite(stepPinY, LOW);
       
        delayMicroseconds(100000);
        
        }
         delay(1);
  
 }
   delay(1);
//////////////////////////////////////////////////////////
 
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
    diametro=result+0.48;
  }
}
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// función 
void PID_Control(){

unsigned long current_time = millis(); //returns the number of milliseconds passed since the Arduino started running the program

delta_time = current_time - last_time; //delta time interval 

if (delta_time >= T_sampling){

double error = SETPOINT - diametro;

/*total_error += error; //accumalates the error - integral term
if (total_error >= max_control) total_error = max_control;
else if (total_error <= min_control) total_error = min_control;*/

// double delta_error = error - last_error; //difference of error for derivative term

//control_signal = Kp*error; // + (Ki*T_sampling)*total_error + (Kd/T_sampling)*delta_error; //PID control compute
/*if (control_signal >= max_control) control_signal = max_control;
else if (control_signal <= min_control) control_signal = min_control;*/

if(0<=error<=0.02){
  errorint=1;
}else{
  if(0.02<error<=0.04){
    errorint=2;
  }else{
    if (0.04<error<=0.06){
      errorint=3;
    }else{
      if (0.06<error<=0.08){
        errorint=4;
      }else{
        if (0.08<error){
          errorint=5;
        }
      }
    }
  }
}

switch (errorint)
{
  case 1:
    //Error entre 0 y 0.02 mm.
    velocidad=10;
    //Serial.println("1");
  break;

  case 2:
    //Error entre 0.02 y 0.04 mm.
    velocidad=11;
    //Serial.println("2");
    
  break;

  case 3:
    //Error entre 0.04 y 0.06 mm.
    velocidad=12;
    //Serial.println("3");
  break;

  case 4:
    //Error entre 0.06 y 0.08 mm.
    velocidad=13;
    Serial.println("4");
  break;

  case 5:
    //Error mayor a 0.08 mm.
    velocidad=14;
    //Serial.println("5");
  break;

  default:
    //Cuando el error es negativo
    velocidad=9;
    //Serial.println("1/2");
  break;
}

//last_error = error;
last_time = current_time;
} 
}


