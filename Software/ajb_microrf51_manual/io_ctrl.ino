void initGPIO() {
  pinMode(L_MOTOR_DIR, OUTPUT);
  pinMode(R_MOTOR_DIR, OUTPUT);
  pinMode(L_MOTOR_PWM, OUTPUT);
  pinMode(R_MOTOR_PWM, OUTPUT);
}

volatile uint8_t pwm_counter;
uint8_t pwm_comp0;
uint8_t pwm_comp1;

// Soft PWM (temporary)
void pwm_runner() {
  pwm_counter++;

  if (pwm_comp0 > pwm_counter)
    NRF_GPIO->OUTSET  = (1 << L_MOTOR_PWM);
  else
    NRF_GPIO->OUTCLR  = (1 << L_MOTOR_PWM);

  if (pwm_comp1 > pwm_counter)
    NRF_GPIO->OUTSET  = (1 << R_MOTOR_PWM);
  else
    NRF_GPIO->OUTCLR  = (1 << R_MOTOR_PWM);
}

void motor_setSpeedLR(int16_t Lspeed, int16_t Rspeed) {
  if ((Lspeed > 255) || (Lspeed < -255))
    return;
  if ((Rspeed > 255) || (Rspeed < -255))
    return;
    
  // Left motor
  digitalWrite(L_MOTOR_DIR, Lspeed >= 0 ? L_FORWARD : L_BACKWARD);
  pwm_comp0 = (Lspeed >= 0 ? Lspeed : -Lspeed);
  
  // Right motor
  digitalWrite(R_MOTOR_DIR, Rspeed >= 0 ? R_FORWARD : R_BACKWARD);
  pwm_comp1 = (Rspeed >= 0 ? Rspeed : -Rspeed);
}
