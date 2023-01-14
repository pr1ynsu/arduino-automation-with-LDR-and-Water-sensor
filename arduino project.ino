
// Include Libraries
#include "Arduino.h"
#include "LDR.h"
#include "Servo.h"


// Pin Definitions
#define LDR_PIN_SIG	A3
#define SERVO360MICRO_PIN_SIG	2
#define WATERLEVELSENSOR_5V_PIN_SIG	A1



// Global variables and defines
#define THRESHOLD_ldr   100
int ldrAverageLight;
// object initialization
LDR ldr(LDR_PIN_SIG);
Servo servo360Micro;


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    ldrAverageLight = ldr.readAverage();
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // LDR (Mini Photocell) - Test Code
    // Get current light reading, substract the ambient value to detect light changes
    int ldrSample = ldr.read();
    int ldrDiff = abs(ldrAverageLight - ldrSample);
    Serial.print(F("Light Diff: ")); Serial.println(ldrDiff);

    }
    else if(menuOption == '2') {
    // Continuous Rotation Micro Servo - FS90R - Test Code
    // The servo will rotate CW in full speed, CCW in full speed, and will stop  with an interval of 2000 milliseconds (2 seconds) 
    servo360Micro.attach(SERVO360MICRO_PIN_SIG);         // 1. attach the servo to correct pin to control it.
    servo360Micro.write(180);  // 2. turns servo CW in full speed. change the value in the brackets (180) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 3. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro.write(0);    // 4. turns servo CCW in full speed. change the value in the brackets (0) to change the speed. As these numbers move closer to 90, the servo will move slower in that direction.
    delay(2000);                              // 5. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro.write(90);    // 6. sending 90 stops the servo 
    delay(2000);                              // 7. waits 2000 milliseconds (2 sec). change the value in the brackets (2000) for a longer or shorter delay in milliseconds.
    servo360Micro.detach();                    // 8. release the servo to conserve power. When detached the servo will NOT hold it's position under stress.
    }
    else if(menuOption == '3')
    {
    // Disclaimer: The Water Level Sensor Module is in testing and/or doesn't have code, therefore it may be buggy. Please be kind and report any bugs you may find.
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) LDR (Mini Photocell)"));
    Serial.println(F("(2) Continuous Rotation Micro Servo - FS90R"));
    Serial.println(F("(3) Water Level Sensor Module"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing LDR (Mini Photocell)"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Continuous Rotation Micro Servo - FS90R"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Water Level Sensor Module - note that this component doesn't have a test code"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
