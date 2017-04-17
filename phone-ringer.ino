//
// Pins to use for the A/C control voltage
//
const int AC_PIN_1 = D0;
const int AC_PIN_2 = D1;
const int ACTIVATE_PIN = A0;

//
// PWM sine wave lookup functions
//
const short PWM_LOOKUP[] = {
      0,   3,   6,  10,  13,  16,  19,  22,  26,  29,  32,  35,  38,  41,  45,  48,  51,  54,  57,  60,  63,  67,  70,  73,  76,
     79,  82,  85,  88,  91,  94,  97, 100, 103, 106, 109, 111, 114, 117, 120, 123, 126, 128, 131, 134, 137, 139, 142, 145, 147,
    150, 152, 155, 158, 160, 163, 165, 167, 170, 172, 175, 177, 179, 181, 184, 186, 188, 190, 192, 194, 196, 199, 201, 202, 204,
    206, 208, 210, 212, 214, 215, 217, 219, 220, 222, 223, 225, 226, 228, 229, 231, 232, 233, 235, 236, 237, 238, 239, 240, 242,
    243, 243, 244, 245, 246, 247, 248, 249, 249, 250, 250, 251, 252, 252, 253, 253, 253, 254, 254, 254, 254, 255, 255, 255, 255,
    255, 255, 255, 255, 255, 254, 254, 254, 254, 253, 253, 253, 252, 252, 251, 250, 250, 249, 249, 248, 247, 246, 245, 244, 243,
    243, 242, 240, 239, 238, 237, 236, 235, 233, 232, 231, 229, 228, 226, 225, 223, 222, 220, 219, 217, 215, 214, 212, 210, 208,
    206, 204, 202, 201, 199, 196, 194, 192, 190, 188, 186, 184, 181, 179, 177, 175, 172, 170, 167, 165, 163, 160, 158, 155, 152,
    150, 147, 145, 142, 139, 137, 134, 131, 128, 126, 123, 120, 117, 114, 111, 109, 106, 103, 100,  97,  94,  91,  88,  85,  82,
     79,  76,  73,  70,  67,  63,  60,  57,  54,  51,  48,  45,  41,  38,  35,  32,  29,  26,  22,  19,  16,  13,  10,   6,   3
};
const int PWM_LOOKUP_LENGTH = 250;
const int PWM_STEP_MICROSECONDS = 100;

const int AC_PERIOD_MILLISECONDS = PWM_LOOKUP_LENGTH * PWM_STEP_MICROSECONDS * 2 / 1000;

bool isActivated = false;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup() {
    pinMode(AC_PIN_1, OUTPUT);
    pinMode(AC_PIN_2, OUTPUT);
    pinMode(ACTIVATE_PIN, INPUT_PULLDOWN);
    
    attachInterrupt(ACTIVATE_PIN, setActivatedFromPin, CHANGE);
    
    Particle.function("setActivated", setActivatedFromCloud);
}

void loop() {
    ringPattern();
}

void ringPattern() {
    ring(true, 2000);
    ring(false, 3000);
}

void ring(bool ringing, int milliseconds) {
    int periods = milliseconds / AC_PERIOD_MILLISECONDS;
    for(int i = 0; i < periods; i++) {
        if(!isActivated) return;
        
        if(ringing) {
          doFullWave(); 
        } else {
          delay(AC_PERIOD_MILLISECONDS);
        }
        
        Particle.process();
    }
}

void setActivatedFromPin() {
    isActivated = digitalRead(ACTIVATE_PIN) == HIGH;
}

int setActivatedFromCloud(String state) {
    if(state == "true") {
        isActivated = true;
    } else if(state == "false") {
        isActivated = false;
    } else {
        return 0;
    }
    
    return 1;
}

void doFullWave() {
    digitalWrite(AC_PIN_1, LOW);
    doHalfWave(AC_PIN_2);
    digitalWrite(AC_PIN_2, LOW);
    doHalfWave(AC_PIN_1);
}

void doHalfWave(int pin) {
    for(int i = 0; i < PWM_LOOKUP_LENGTH; i++) {
        analogWrite(pin, PWM_LOOKUP[i]);
        delayMicroseconds(PWM_STEP_MICROSECONDS);
    }
}