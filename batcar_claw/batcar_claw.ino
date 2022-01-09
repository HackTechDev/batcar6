/*
 * Grove Bluetooth serial v1.1
 
 */
 #include <Servo.h>
// Bluetooth

#include <SoftwareSerial.h>

#define RxD 6  // Plug the Bluetooth on the D6 pin
#define TxD 7

SoftwareSerial blueToothSerial(RxD,TxD);

Servo claw;
Servo head;  


int clawPos = 0;   
int headPos = 0;


void setup() {
    claw.attach(2);  
    head.attach(3);

 
              
    // Bluetooth
    pinMode(RxD, INPUT);
    pinMode(TxD, OUTPUT);  
    setupBlueToothConnection(); 
}

void loop() {

    char recvChar;

    while(1) {

        // Bluetooth
        if (blueToothSerial.available()) {
            recvChar = blueToothSerial.read();
            Serial.print(recvChar);

            if(recvChar == 'a') {
               Serial.println("Claw Open");
              for (clawPos = 0; clawPos <= 180; clawPos += 1) {
                claw.write(clawPos);
                delay(15);
              }
            }

            if(recvChar == 'q') {
                Serial.println("Claw Close");
                for (clawPos = 180; clawPos >= 0; clawPos -= 1) {
                  claw.write(clawPos);
                  delay(15);
                }
            }

            if(recvChar == 'z') {
                Serial.println("Arm Up");
                for (headPos = 0; headPos <= 180; headPos += 1) {
                  head.write(headPos);
                  delay(15);
                }
            }

            if(recvChar == 's') {
                Serial.println("Arm Down");
                for (headPos = 180; headPos >= 0; headPos -= 1) { 
                  head.write(headPos);              
                  delay(15);                    
                }
            }

        }
    }
    delay(500);
}


void setupBlueToothConnection() {
    Serial.println("setupBlueToothConnection");
    blueToothSerial.begin(38400);
    blueToothSerial.print("\r\n+STWMOD=0\r\n");
    blueToothSerial.print("\r\n+STNA=Batclaw\r\n");
    blueToothSerial.print("\r\n+STPIN=6666\r\n");
    blueToothSerial.print("\r\n+STOAUT=1\r\n");
    blueToothSerial.print("\r\n+STAUTO=0\r\n");
    delay(2000);
    blueToothSerial.print("\r\n+INQ=1\r\n");
    Serial.println("The slave bluetooth is inquirable!");
    delay(2000);
    blueToothSerial.flush();
} 
