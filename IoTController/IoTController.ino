#define RED_LED 10
#define GREEN_LED 11
#define RED_BUTTON 9
#define GREEN_BUTTON 8
#define BUZZER A0

char *messages[] = {"Valid Identity0", "Invalid Identity1", "RED LED ON", "RED LED OFF", "GREEN LED ON", "GREEN LED OFF", "ALARM ON", "ALARM OFF"}; // Textos exibidos no terminal do PC
String serialInput = ""; // Esse é o caractere lido pelo Arduino
char printout[20]; // Ainda não entendi para que serve

const int buzzerFrequency = 1000; // Frequência de 1000 Hz

void setup()
{
  // Faço o setup das portas usadas
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_BUTTON, INPUT);
  pinMode(GREEN_BUTTON, INPUT);
  pinMode(BUZZER, OUTPUT); // Configura a porta do buzzer como saída

  // Inicia a porta serial em 9600
  Serial.begin(9600);

  // Mostra o comando de conexão estabelecida
  delay(250);
  Serial.println("Connection Established");
}

void activateButton(int pin, char *message, bool activateBuzzer)
{
  digitalWrite(pin, HIGH); // Ele ativa o led
  if (activateBuzzer)
  {
    tone(BUZZER, buzzerFrequency); // Ativa o buzzer com a frequência especificada
  }
  Serial.println(message);      // Ele envia a mensagem de confirmação junto do ID para salvar na tabela de eventos
  delay(2000);                  // Tem um delay de 2s
  digitalWrite(pin, LOW);       // Desliga o led
  if (activateBuzzer)
  {
    noTone(BUZZER); // Desativa o buzzer
  }
}

void controlLed(int pin, char *message, int state)
{
  digitalWrite(pin, state); // Ele vai acender o led
  Serial.println(message);  // E vai mandar a mensagem de confirmação
}

void controlBuzzer(char *message, int state)
{
  if (state == HIGH)
  {
    tone(BUZZER, buzzerFrequency); // Ativa o buzzer com a frequência especificada
    delay(2000);                   // Mantém o buzzer ativado por 2s
    noTone(BUZZER);                // Desativa o buzzer após o delay
  }
  else
  {
    noTone(BUZZER); // Desativa o buzzer
  }
  Serial.println(message); // E vai mandar a mensagem de confirmação
}

void controlBuzzerCommand(char *message, int state)
{
  if (state == HIGH)
  {
    tone(BUZZER, buzzerFrequency); // Ativa o buzzer com a frequência especificada
  }
  else
  {
    noTone(BUZZER); // Desativa o buzzer
  }
  Serial.println(message); // E vai mandar a mensagem de confirmação
}


void loop()
{
  while (Serial.available()) // Faz a leitura dos comandos dados ao PC
  {
    char charRead = Serial.read();
    serialInput.concat(charRead);
  }

  // Abaixo são os comandos de interação do Arduino (Veja o README para entender os comandos do Arduino)

  if (digitalRead(GREEN_BUTTON)) // Se o botão do led verde for pressionado
  {
    activateButton(GREEN_LED, messages[0], false); // Vai acender o led verde por 2s e enviar a mensagem de confirmação junto com o ID do evento
  }

  if (digitalRead(RED_BUTTON)) // Se o botão do led vermelho for pressionado
  {
    activateButton(RED_LED, messages[1], true); // Vai acender o led vermelho por 2s, ativar o buzzer e enviar a mensagem de confirmação junto com o ID do evento
  }

  // Abaixo são os comandos controlados pelo PC (Veja o README para entender os comandos do PC)

  if (serialInput != "") // Caso tenha alguma entrada de dados vinda do PC
  {
    if (serialInput == "i") // Caso essa entrada seja o caractere i
    {
      controlLed(RED_LED, messages[2], HIGH); // Vai acender o led vermelho e enviar a mensagem de confirmação
    }

    if (serialInput == "o") // Caso essa entrada seja o caractere o
    {
      controlLed(RED_LED, messages[3], LOW); // Vai apagar o led vermelho e enviar a mensagem de confirmação
    }

    if (serialInput == "k") // Caso essa entrada seja o caractere k
    {
      controlLed(GREEN_LED, messages[4], HIGH); // Vai acender o led verde e enviar a mensagem de confirmação
    }

    if (serialInput == "l") // Caso essa entrada seja o caractere l
    {
      controlLed(GREEN_LED, messages[5], LOW); // Vai apagar o led verde e enviar a mensagem de confirmação
    }

    if (serialInput == "n") // Caso essa entrada seja o caractere b
    {
      controlBuzzerCommand(messages[6], HIGH); // Vai ativar o buzzer por 2s e enviar a mensagem de confirmação
    }

    if (serialInput == "m") // Caso essa entrada seja o caractere n
    {
      controlBuzzerCommand(messages[7], LOW); // Vai desativar o buzzer e enviar a mensagem de confirmação
    }

    if (serialInput == "z") // Caso essa entrada seja o caractere z
    {
      Serial.println("2"); // Ele vai mandar o ID 2 para o computador, onde será executada a lista de eventos
    }

    if (serialInput == "c") // Caso essa entrada seja o caractere c
    {
      Serial.println("3"); // Ele vai mandar o ID 3 para o computador, onde será exibido os controles de comando
    }

    serialInput.toCharArray(printout, 21); // Ainda não sei para que isso serve
    serialInput = "";                      // Define o caractere como nulo
  }
}
