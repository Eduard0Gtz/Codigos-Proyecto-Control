//MOVER MOTORES CON 0,1-->Motor Spooling      2,3-->Extrusor

//Velocidad de los motores
int velocidad;

#define X_DIR_PIN 5
#define X_STEP_PIN  6
#define X_ENABLE_PIN 4
//
#define E_DIR_PIN 9 
#define E_STEP_PIN 8
#define E_ENABLE_PIN 7

#define stepsPerRevolution_ext 100
#define stepsPerRevolution_spol 1000
int input;

void setup() {
  // Declare pins as output:
  Serial.begin(9600);
  
  pinMode(X_DIR_PIN, OUTPUT);
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_ENABLE_PIN, OUTPUT);

  pinMode(E_DIR_PIN, OUTPUT);
  pinMode(E_STEP_PIN, OUTPUT);
  pinMode(E_ENABLE_PIN, OUTPUT);

  digitalWrite(X_ENABLE_PIN , LOW);
  digitalWrite(E_ENABLE_PIN , LOW);
  
}

void loop() {

  // Motor 1
  
    input=Serial.read();

           //Definimos la velocidad
           velocidad=800000;
    
          // Motor EJE X
            digitalWrite(X_DIR_PIN, LOW);
          
           //Motor EXTRUSOR
            digitalWrite(E_DIR_PIN, LOW);

        // Spin the stepper motor 1 revolution slowly:
        for (int i = 0; i < stepsPerRevolution_ext; i++) {
          // These four lines result in 1 step:
          digitalWrite(X_STEP_PIN, HIGH);
          delayMicroseconds(velocidad);
          digitalWrite(X_STEP_PIN, LOW);
          delayMicroseconds(velocidad);

          digitalWrite(E_STEP_PIN, HIGH);
          delayMicroseconds(velocidad);
          digitalWrite(E_STEP_PIN, LOW);
          delayMicroseconds(velocidad);

        }

}