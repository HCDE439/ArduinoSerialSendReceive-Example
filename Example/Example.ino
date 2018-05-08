/*
 * Arduino Serial Send/Receive Example
 * 
 * A quick implementation of sending/receiving data via a serial device, such as an XBee controller
 */

#include <SoftwareSerial.h>
#include <Button.h>

const int ledPin = 13;
const int buttonPin = 7;
const int buzzerPin = 12;

SoftwareSerial xBee(2, 3);
Button button(buttonPin, INPUT_PULLUP);

String buff;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  
  Serial.begin(9600);
  xBee.begin(9600);

  buff = "";
}

void loop() {
  
  // Reads data from the port until we find a character that is not a letter, number, or space
  if (xBee.available() > 0) {
    char c = xBee.read();
    
    if (isAlphaNumeric(c) || c == ' ') {
      buff += c;
    } else {

      // Check the message for keywords
      if (buff.equals("buzzer")) {
        tone(buzzerPin, 1000);
        delay(1000);
        noTone(buzzerPin);
      }
      else if (buff.equals("led")) {
        digitalWrite(ledPin, HIGH);
        delay(1000);
        digitalWrite(ledPin, LOW);
      }
      buff = "";
    }
  }

  int buttonState = button.checkButtonAction();

  if (buttonState == Button::CLICKED) {

    // This example uses println, which automatically adds a newline, or '\n' after each message.
    // Conveniently, our "receive" code looks for any character that is not a letter, number, or space.
    xBee.println("buzzer");
  }
}
