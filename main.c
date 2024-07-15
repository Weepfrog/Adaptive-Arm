#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62

#define E_STEP_PIN         26
#define E_DIR_PIN          28
#define E_ENABLE_PIN       24

#define SDPOWER            -1
#define SDSS               53
#define LED_PIN            13

#define FAN_PIN            9

#define PS_ON_PIN          12
#define KILL_PIN           -1

#define HEATER_0_PIN       10
#define HEATER_1_PIN       8
#define TEMP_0_PIN          13   // ANALOG NUMBERING
#define TEMP_1_PIN          14   // ANALOG NUMBERING

#define GPIO_A             3
#define GPIO_B             2
#define GPIO_C             14
#define GPIO_D             15
#define GPIO_E             18
#define GPIO_F             19

void setup() {
    pinMode(HEATER_0_PIN, OUTPUT);

}

void loop() {
  digitalWrite(HEATER_0_PIN, HIGH);

}
