#define led 4
#define btn 3

int leitura = 0; // Variável para leitura do pushbutton
int armazena = 0; // Variável para armazenar valores do pushbutton

void setup() {
  pinMode(led, OUTPUT); // Define o pino do led como saída do Arduino
  pinMode(btn, INPUT); // Define o pino do pushbutton como entrada do Arduino
}

void loop() {
  leitura = digitalRead(btn); // Lê o estado do pushbutton: HIGH ou LOW

  if (leitura == HIGH) { // Verifica se o pushbutton está pressionado
    armazena = !armazena; // Inverte o valor da variável armazena
    delay(500); // Delay para debounce (evitar múltiplas leituras por um único pressionamento)
  }

  if (armazena == HIGH) {
    digitalWrite(led, HIGH); // Liga o led
  } else {
    digitalWrite(led, LOW); // Desliga o led
  }
}
