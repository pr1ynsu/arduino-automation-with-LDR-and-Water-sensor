#include "Arduino.h"
#include "LDR.h"
#include "Servo.h"

#define LDR_PIN_SIG	A3
#define SERVO360MICRO_PIN_SIG	2
#define WATERLEVELSENSOR_5V_PIN_SIG	A1

#define THRESHOLD_ldr   100
int ldrAverageLight;
LDR ldr(LDR_PIN_SIG);
Servo servo360Micro;

const int timeout = 10000;     
char menuOption = 0;
long time0;


void setup() 
{
    Serial.begin(9600);
    while (!Serial) ;
    Serial.println("start");
    
    ldrAverageLight = ldr.readAverage();
    menuOption = menu();
    
}
void loop() 
{
    
    
    if(menuOption == '1') {
    int ldrSample = ldr.read();
    int ldrDiff = abs(ldrAverageLight - ldrSample);
    Serial.print(F("Light Diff: ")); Serial.println(ldrDiff);

    }
    else if(menuOption == '2') {
    servo360Micro.attach(SERVO360MICRO_PIN_SIG);        
    servo360Micro.write(180);  
    delay(2000);                              
    servo360Micro.write(0);    
    delay(2000);                              
    servo360Micro.write(90);     
    delay(2000);                             
    servo360Micro.detach();                    
    }
    else if(menuOption == '3')
    {
    
    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}

char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) LDR (Mini Photocell)"));
    Serial.println(F("(2) Continuous Rotation Micro Servo - FS90R"));
    Serial.println(F("(3) Water Level Sensor Module"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());
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
