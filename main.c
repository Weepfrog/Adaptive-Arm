// 1/4 resolution
// 800 seteps per revolution
// 0.45 degrees per step
// Mode 0 - Pour
// Mode 1 - Stir

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define liftStepPin         22
#define liftDirPin          24
#define liftEnablePin       26

#define sweepStepPin        23
#define sweepDirPin         25
#define sweepEnablePin      27

#define wristStepPin        28
#define wristDirPin         30
#define wirstEnablePin      32

#define userButton          29
#define modeChangeButton    31
#define modeSelectButton    33

int globalSelectedMode = 0;
int globalViewMode = 0;

LiquidCrystal_I2C lcd(0x27,  16, 2);


void setup() {
    //add coments
    // i dont want to rn
    lcd.init();
    lcd.backlight();

}

void loop() {
    int pressedButton = checkButtonPress;
    switch(pressedButton){
        case 1: // userButton
            if(globalSelectedMode = 0){
                pickAndPour();
            }
            else if (globalSelectedMode = 1){
                pickAndPour();
            }
        break;

        case 2: // modeChangeButton
            viewModeChange();
            modeOutput();
        break;

        case 3: // modeSelectButton
            globalSelectedMode = globalViewMode;
            modeOutput();
        break;

        default: break;
    }

}

void pickAndPour(){
    motorTurn(heightToDegrees(15), 1440, "LIFT");
    motorTurn(20, 2, "SWEEP");
    motorTurn(100, 20, "WRIST");
    
    motorTurn(-100, 20, "WRIST");
    motorTurn(-20, 2, "SWEEP");
    motorTurn(heightToDegrees(-15), 1440, "LIFT");
}

int heightToDegrees(int height){
    return height*4*360;
}

//make into smaller functions
void motorTurn(int degrees, int degPerSec, String motor){
    int absDegrees = abs(degrees);

    int steps = degreesToSteps(absDegrees);
    int delay = speedToDelay(degPerSec);
    if (motor == "LIFT"){
        if(degrees>1){
            digitalWrite(liftDirPin, HIGH);
        }
        else if(degrees<1){
            digitalWrite(liftDirPin, LOW);
        }

        for(int i = 0; i<steps; i++){
            digitalWrite(liftStepPin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(liftStepPin, LOW);
            delayMicroseconds(delay);
        }
      }
      if (motor == "SWEEP"){
        if(degrees>1){
            digitalWrite(sweepDirPin, HIGH);
        }
        else if(degrees<1){
            digitalWrite(sweepDirPin, LOW);
        }

        for(int i = 0; i<steps; i++){
            digitalWrite(sweepStepPin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(sweepStepPin, LOW);
            delayMicroseconds(delay);
        }
      }
      if (motor == "WRIST"){
        if(degrees>1){
            digitalWrite(wristDirPin, HIGH);
        }
        else if(degrees<1){
            digitalWrite(wristDirPin, LOW);
        }

        for(int i = 0; i<steps; i++){
            digitalWrite(wristStepPin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(wristStepPin, LOW);
            delayMicroseconds(delay);
        }
      }   
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

void modeOutput(){
    if(globalViewMode = 0 && globalSelectedMode == globalViewMode){
        lcd.setCursor(0,0);
        lcd.print("Pouring");
        lcd.setCursor(0,1);
        lcd.print("Selected");
    }
    else if(globalViewMode = 1 && globalSelectedMode == globalViewMode){
        lcd.setCursor(0,0);
        lcd.print("Stiring");
        lcd.setCursor(0,1);
        lcd.print("Selected");
    }
    else if(globalViewMode = 0 && globalSelectedMode != globalViewMode){
        lcd.setCursor(0,0);
        lcd.print("Pouring");
    }
    else if(globalViewMode = 1 && globalSelectedMode != globalSelectedMode){
        lcd.setCursor(0,0);
        lcd.print("Stiring");
    }
}