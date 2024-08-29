// 1/4 resolution
// 800 seteps per revolution
// 0.45 degrees per step
// Mode 0 - Pour
// Mode 1 - Stir

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//define all i/o pins
#define liftStepPin         5
#define liftDirPin          4
#define liftLimitPin        A7

#define wristStepPin        3
#define wristDirPin         2

#define sweepStepPin        7
#define sweepDirPin         6
#define sweepLimitPin       A6

#define userButton          10
#define modeChangeButton    12
#define modeSelectButton    11

//set up mode variables
int globalSelectedMode = 0;
int globalViewMode = 0;

//initate lcd library
LiquidCrystal_I2C lcd(0x27,  16, 2);

void setup() {
    //start lcd
    lcd.init();
    lcd.backlight();
    Serial.begin(9600);

    pinMode(liftLimitPin, INPUT);

    //set default mode
    globalSelectedMode = globalViewMode;
    modeOutput();
    // for(int i = 0; i != 1; i = 0){
    //   lcd.setCursor(0,0);
    //   lcd.print(digitalRead(liftLimitPin));
    // };
    //reset arm to limits
    //reset sweep
    //for(int i = 0; i != 1; i = digitalRead(sweepLimitPin)){
    //    motorTurn(-200, 20, "SWEEP");
    //}
    //reset height
    Serial.println("printing");
    pour();
    Serial.println("purned");
}

void loop() {        
    // motorTurn(200, 20, "WRIST");

    switch(checkButtonPress()){
        case 1: // run userButton case
            if(globalSelectedMode = 0){
                pour();
            }
            else if (globalSelectedMode = 1){
                stir();
            }
        break;

        case 2: // run modeChangeButton case
            viewModeChange();
            modeOutput();
        break;

        case 3: // run modeSelectButton case
            globalSelectedMode = globalViewMode;
            modeOutput();
        break;

        default: //default is nothing 8
        break;
    }

}

//run through all buttons and output one which is pressed
int checkButtonPress(){
    if (digitalRead(userButton)){
        return 1;
    }
    else if (digitalRead(modeChangeButton)){
        return 2;
    }
    else if (digitalRead(modeSelectButton)){
        return 3;
    }
    else{
        return 0;
    }
}

//move arm to pour cup contents
void pour(){
    // move and pour cup
    motorTurn(20, 1440, "LIFT");
    Serial.print("Doing height");
    delay(100000);

    motorTurn(5, 2, "SWEEP");
   Serial.print("Doing Sweep");
    motorTurn(100, 20, "WRIST");
   Serial.print("Doing Wrist");

    
    // reset cup position
    motorTurn(-100, 20, "WRIST");
    motorTurn(-20, 2, "SWEEP");
    motorTurn(heightToDegrees(-5), 1440, "LIFT");
}

//move arm to bowl location and stir
void stir(){
    motorTurn(heightToDegrees(15), 1440, "LIFT");
    motorTurn(20, 2, "SWEEP");

    motorTurn(60, 40, "WRIST");
    motorTurn(-60, 40, "WRIST");
    motorTurn(60, 40, "WRIST");
    motorTurn(-60, 40, "WRIST");
    motorTurn(60, 40, "WRIST");
    motorTurn(-60, 40, "WRIST");
    motorTurn(60, 40, "WRIST");
    motorTurn(-60, 40, "WRIST");
    motorTurn(60, 40, "WRIST");
    motorTurn(-60, 40, "WRIST");

    motorTurn(-20, 2, "SWEEP");
    motorTurn(heightToDegrees(-15), 1440, "LIFT");
}

//turn a specivied motor a specified amount
void motorTurn(int degrees, int degPerSec, String motor){
    // convert input variables to be usable by motor controler
    int absDegrees = abs(degrees);
    int steps = degreesToSteps(absDegrees);
    int delay = speedToDelay(degPerSec);

    // move LIFT motor
    if (motor == "LIFT"){
        if(degrees>1){
            digitalWrite(liftDirPin, HIGH);
        }
        else if(degrees<1){
            digitalWrite(liftDirPin, LOW);
        }

        for(int i = 0; i<=steps; i++){
            digitalWrite(liftStepPin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(liftStepPin, LOW);
            delayMicroseconds(delay);
        }
      }

      // move SWEEP motor
      if (motor == "SWEEP"){
        if(degrees>1){
            digitalWrite(sweepDirPin, HIGH);
        }
        else if(degrees<1){
            digitalWrite(sweepDirPin, LOW);
        }

        for(int i = 0; i<=steps; i++){
            digitalWrite(sweepStepPin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(sweepStepPin, LOW);
            delayMicroseconds(delay);
        }
      }

      // move WRIST motor
      if (motor == "WRIST"){
        if(degrees>1){
            digitalWrite(wristDirPin, HIGH);
        }
        else if(degrees<1){
            digitalWrite(wristDirPin, LOW);
        }

        for(int i = 0; i<=steps; i++){
            digitalWrite(wristStepPin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(wristStepPin, LOW);
            delayMicroseconds(delay);
        }
      }   
}

// mode change and display functions

//changed the view mode
void viewModeChange(){
    int mode = globalSelectedMode;

    if(mode<2){
        mode = mode++;
    }
    else if(mode>= 2){
        mode = 0;
    }

    globalViewMode = mode;
}

//output to display
void modeOutput(){
    //outup pouring/selected
    if(globalViewMode = 0 && globalSelectedMode == globalViewMode){
        lcd.setCursor(0,0);
        lcd.print("Pouring");
        lcd.setCursor(0,1);
        lcd.print("Selected");
    }
    
    else if(globalViewMode = 1 && globalSelectedMode == globalViewMode){
        lcd.setCursor(0,0);
        lcd.print("Stirring");
        lcd.setCursor(0,1);
        lcd.print("Selected");
    }
    else if(globalViewMode = 0 && globalSelectedMode != globalViewMode){
        lcd.setCursor(0,0);
        lcd.print("Pouring");
    }
    else if(globalViewMode = 1 && globalSelectedMode != globalSelectedMode){
        lcd.setCursor(0,0);
        lcd.print("Stirring");
    }
}

// unit conversions

int heightToDegrees(int height){
    return height*4*360;
}

int degreesToSteps(int degrees){
    int steps = degrees/0.45;
    return(steps);
}

int speedToDelay(int degPerSec){
    int stepsPerSec = degreesToSteps(degPerSec);
    int mSecPerStep = (1/stepsPerSec)*1000000/2;
    
    return(mSecPerStep);
}
