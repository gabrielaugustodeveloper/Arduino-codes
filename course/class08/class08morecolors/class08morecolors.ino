#define ledR 2
#define ledB 3
#define ledG 4
#define maximo 7
#define botao 7

int btnclicado = 0;
int btnliberado = 0;
int ciclo = 0;

void vermelho(){
  digitalWrite(ledR,1);
  digitalWrite(ledB,0);
  digitalWrite(ledG,0);

}

void azul(){
  digitalWrite(ledR,0);
  digitalWrite(ledB,1);
  digitalWrite(ledG,0);

}

void verde(){
  digitalWrite(ledR,0);
  digitalWrite(ledB,0);
  digitalWrite(ledG,1);

}

void amarelo(){
  digitalWrite(ledR,1);
  digitalWrite(ledB,0);
  digitalWrite(ledG,1);

}

void branco(){
  digitalWrite(ledR,1);
  digitalWrite(ledB,1);
  digitalWrite(ledG,1);

}

void magenta(){
  digitalWrite(ledR,1);
  digitalWrite(ledB,1);
  digitalWrite(ledG,0);

}

void ciano(){
  digitalWrite(ledR,0);
  digitalWrite(ledB,1);
  digitalWrite(ledG,1);

}


void trocaLed(){
  if(ciclo == 0){
   vermelho();
    
  }	else if(ciclo == 1){
    azul();
    
  }else if(ciclo == 2){
    verde();
    
  }else if(ciclo == 3){
    amarelo();
    
  }else if(ciclo == 4){
     branco();
    
  }else if(ciclo == 5){
     magenta();
    
  }else if(ciclo == 6){
     ciano();
  }
  
  ciclo++;
  if(ciclo > maximo - 1){
    ciclo = 0;
  }
}

void checabtn(){
  if(digitalRead(botao)== HIGH){
    btnclicado = 1;
    btnliberado = 0;  
  }else {
     btnliberado = 1;
  }
  if((btnclicado == 1 and btnliberado == 1)){
    btnclicado = 0;
    btnliberado = 0;  
    trocaLed();
  }
}

void setup(){
  
  pinMode(ledR, OUTPUT);  
  pinMode(ledB, OUTPUT);  
  pinMode(ledG, OUTPUT);
  pinMode(botao, INPUT);
}

void loop(){

  checabtn();

}