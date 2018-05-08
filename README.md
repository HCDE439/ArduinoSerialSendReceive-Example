# Arduino XBee Send/Receive Example
A quick implementation of sending/receiving data via an XBee controller

## Usage
Simply download a ZIP of this repository from [this link](https://github.com/HCDE439/ArduinoXBeeSendReceive-Example/archive/master.zip) and run the code on your Arduino.

## What's going on?
### Sending a message
```c++
xBee.println("buzzer");
```
Prints the string to the XBee controller (as opposed to `Serial`). Using `println` adds a newline, or `'\n'` after each message which helps segment messages on the receiving side.

### Receiving a message
``` c++
if (xBee.available() > 0) {
    char c = xBee.read();

    if (isAlphaNumeric(c) || c == ' ') {
        buff += c;
    } else {
        ...
        buff = "";
    }
}
```
This reads message data from the XBee controller until we find a character that is not a letter, number, or space (such as a newline, or `'\n'`). Then we act on it and reset `buff` to read the next message.

### Making a Decision
```c++
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
```
We can compare strings using `equals`. This returns a `boolean` for whether or not the strings are the same. There are other functions for comparing characters, splitting strings, etc. that can be found in the [`String()` documentation](https://www.arduino.cc/reference/en/language/variables/data-types/stringobject/).

## License
TBA
