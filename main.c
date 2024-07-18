// 1/4 resolution
// 800 seteps per revolution
// 0.45 degrees per step

#define liftStepPin         22
#define liftDirPin          24
#define liftEnablePin       26

#define sweepStepPin        23
#define sweepDirPin         25
#define sweepEnablePin      27

#define wristStepPin        28
#define wristDirPin         30
#define wirstEnablePin      32

void setup() {

}

void loop() {

}

void motorTurn(int degrees, int degPerSec, String motor){
    int absDegrees = abs(degrees);

    int steps = degreesToSteps(absDegrees);
    int delay = speedToDelay(degPerSec);
    
    switch (motor) {
      case lift:
        if(degrees>1){
            digitalWrite(liftDirPin, HIGH)
        }
        else if(degrees<1){
            digitalWrite(liftDirPin, LOW)
        }

        for(int i = 0; i<steps; i++){
            digitalWrite(liftStepPin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(liftStepPin, LOW);
            delayMicroseconds(delay);
        }
      break;
      case sweep:
        if(degrees>1){
            digitalWrite(sweepDirPin, HIGH)
        }
        else if(degrees<1){
            digitalWrite(sweepDirPin, LOW)
        }

        for(int i = 0; i<steps; i++){
            digitalWrite(sweepStepPin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(sweepStepPin, LOW);
            delayMicroseconds(delay);
        }
      break;
      case wrist:
        if(degrees>1){
            digitalWrite(wristDirPin, HIGH)
        }
        else if(degrees<1){
            digitalWrite(wristDirPin, LOW)
        }

        for(int i = 0; i<steps; i++){
            digitalWrite(wristStepPin, HIGH);
            delayMicroseconds(delay);
            digitalWrite(wristStepPin, LOW);
            delayMicroseconds(delay);
        }
      break;
      default: break;
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