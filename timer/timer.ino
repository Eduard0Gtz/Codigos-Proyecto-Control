unsigned long tiempo1 = 0;
unsigned long tiempo2 = 0;
unsigned long tiempoSegundos = 0;
double last_time=0;
double current_time;
double delta_time;

void setup() {
  Serial.begin(9600);
  

}

void loop() {
  current_time = millis();
  delta_time = current_time - last_time;

if (delta_time >= 1000){
    Serial.println(current_time);
    Serial.println("Hola");
    Serial.println(delta_time);
    last_time=current_time;
  }
  

}
