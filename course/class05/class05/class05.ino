#define led 3
#define maximo 32
#define minimo 0
#define tmp 100



void setup() {
  pinMode(led, OUTPUT);

}

void loop() {
 for(int i=minimo;i<maximo;i++){
  analogWrite(led, i);
  //digitalWrite(led, HIGH);
  delay(tmp);
  }


for(int i=minimo;i<maximo;i--){
  analogWrite(led, i);
  //digitalWrite(led, LOW);
  delay(tmp);
  }


}
