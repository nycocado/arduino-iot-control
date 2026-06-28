#define RED_LED 10
#define GREEN_LED 11
#define RED_BUTTON 9
#define GREEN_BUTTON 8
#define BUZZER A0

char* messages[] = {
    "Valid Identity0",
    "Invalid Identity1",
    "RED LED ON",
    "RED LED OFF",
    "GREEN LED ON",
    "GREEN LED OFF",
    "ALARM ON",
    "ALARM OFF"
};                       // Messages displayed on the PC terminal
String serialInput = ""; // Character read by the Arduino
char printout[20];       // Purpose not yet understood

const int buzzerFrequency = 1000; // 1000 Hz frequency

void setup()
{
    // Sets up the used ports
    pinMode(RED_LED, OUTPUT);
    pinMode(GREEN_LED, OUTPUT);
    pinMode(RED_BUTTON, INPUT);
    pinMode(GREEN_BUTTON, INPUT);
    pinMode(BUZZER, OUTPUT); // Configures buzzer pin as output

    // Starts serial port at 9600 baud
    Serial.begin(9600);

    // Shows connection established message
    delay(250);
    Serial.println("Connection Established");
}

void activateButton(int pin, char* message, bool activateBuzzer)
{
    digitalWrite(pin, HIGH); // Turns on the LED
    if (activateBuzzer)
    {
        tone(
            BUZZER, buzzerFrequency
        ); // Activates buzzer at specified frequency
    }
    Serial.println(
        message
    ); // Sends confirmation message with event ID to save in event table
    delay(2000);            // 2s delay
    digitalWrite(pin, LOW); // Turns off the LED
    if (activateBuzzer)
    {
        noTone(BUZZER); // Deactivates buzzer
    }
}

void controlLed(int pin, char* message, int state)
{
    digitalWrite(pin, state); // Turns on the LED
    Serial.println(message);  // Sends confirmation message
}

void controlBuzzer(char* message, int state)
{
    if (state == HIGH)
    {
        tone(
            BUZZER, buzzerFrequency
        );              // Activates buzzer at specified frequency
        delay(2000);    // Keeps buzzer active for 2s
        noTone(BUZZER); // Deactivates buzzer after delay
    }
    else
    {
        noTone(BUZZER); // Deactivates buzzer
    }
    Serial.println(message); // Sends confirmation message
}

void controlBuzzerCommand(char* message, int state)
{
    if (state == HIGH)
    {
        tone(
            BUZZER, buzzerFrequency
        ); // Activates buzzer at specified frequency
    }
    else
    {
        noTone(BUZZER); // Deactivates buzzer
    }
    Serial.println(message); // Sends confirmation message
}

void loop()
{
    while (Serial.available()) // Reads commands sent to the PC
    {
        char charRead = Serial.read();
        serialInput.concat(charRead);
    }

    // Below are the Arduino interaction commands (see README for Arduino
    // command details)

    if (digitalRead(GREEN_BUTTON)) // If green LED button is pressed
    {
        activateButton(
            GREEN_LED, messages[0], false
        ); // Turns on green LED for 2s and sends confirmation message with
           // event ID
    }

    if (digitalRead(RED_BUTTON)) // If red LED button is pressed
    {
        activateButton(
            RED_LED, messages[1], true
        ); // Turns on red LED for 2s, activates buzzer and sends confirmation
           // message with event ID
    }

    // Below are the PC-controlled commands (see README for PC command details)

    if (serialInput != "") // If there is input data from the PC
    {
        if (serialInput == "i") // If input is character i
        {
            controlLed(
                RED_LED, messages[2], HIGH
            ); // Turns on red LED and sends confirmation message
        }

        if (serialInput == "o") // If input is character o
        {
            controlLed(
                RED_LED, messages[3], LOW
            ); // Turns off red LED and sends confirmation message
        }

        if (serialInput == "k") // If input is character k
        {
            controlLed(
                GREEN_LED, messages[4], HIGH
            ); // Turns on green LED and sends confirmation message
        }

        if (serialInput == "l") // If input is character l
        {
            controlLed(
                GREEN_LED, messages[5], LOW
            ); // Turns off green LED and sends confirmation message
        }

        if (serialInput == "n") // If input is character b
        {
            controlBuzzerCommand(
                messages[6], HIGH
            ); // Activates buzzer and sends confirmation message
        }

        if (serialInput == "m") // If input is character n
        {
            controlBuzzerCommand(
                messages[7], LOW
            ); // Deactivates buzzer and sends confirmation message
        }

        if (serialInput == "z") // If input is character z
        {
            Serial.println("2"); // Sends ID 2 to the computer, where the event
                                 // list will be displayed
        }

        if (serialInput == "c") // If input is character c
        {
            Serial.println("3"); // Sends ID 3 to the computer, where command
                                 // controls will be displayed
        }

        serialInput.toCharArray(printout, 21); // Purpose not yet understood
        serialInput = "";                      // Resets input to empty string
    }
}
