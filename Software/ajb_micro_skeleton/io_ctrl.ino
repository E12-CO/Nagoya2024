#include "io_pins.h" // Contains all GPIO definition plus PWM channel

#define PWM_RES   12    // 12-bit PWM resolution
#define PWM_FREQ  15000 // 15kHz PWM modulation frequency, might change depends on driver IC Bandwidth.

void initGPIO() {
  pinMode(L_MOTOR_DIR, OUTPUT);
  pinMode(L_MOTOR_PWM, OUTPUT);
  pinMode(R_MOTOR_DIR, OUTPUT);
  pinMode(R_MOTOR_PWM, OUTPUT);

  // Setup PWM channel
  ledcSetup(L_MOTOR_PWM_CHAN, PWM_FREQ, PWM_RES);
  ledcSetup(R_MOTOR_PWM_CHAN, PWM_FREQ, PWM_RES);
  ledAttachPin(L_MOTOR_PWM, L_MOTOR_PWM_CHAN);
  ledAttachPin(R_MOTOR_PWM, R_MOTOR_PWM_CHAN);
}

void motor_setSpeedLR(int16_t Lspeed, int16_t Rspeed) {
  // Left motor
  if (Lspeed > 0) { // Positive speed, going forward
    digitalWrite(L_MOTOR_DIR, L_FORWARD);// Change direction before speed
    ledcWrite(L_MOTOR_PWM_CHAN, Lspeed);
  } else if (Lspeed < 0) { // Negative speed, going backward
    digitalWrite(L_MOTOR_DIR, L_BACKWARD);// Change direction before speed
    ledcWrite(L_MOTOR_PWM_CHAN, -Lspeed);
  } else { // Zero speed, stay still
    ledcWrite(L_MOTOR_PWM_CHAN, 0);
  }

  // Right motor
  if (Rspeed > 0) { // Positive speed, going forward
    digitalWrite(R_MOTOR_DIR, R_FORWARD);// Change direction before speed
    ledcWrite(R_MOTOR_PWM_CHAN, Rspeed);
  } else if (Rspeed < 0) { // Negative speed, going backward
    digitalWrite(R_MOTOR_DIR, R_BACKWARD);// Change direction before speed
    ledcWrite(R_MOTOR_PWM_CHAN, -Rspeed);
  } else { // Zero speed, stay still
    ledcWrite(R_MOTOR_PWM_CHAN, 0);
  }
}
