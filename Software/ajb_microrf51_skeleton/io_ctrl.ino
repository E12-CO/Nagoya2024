void initGPIO() {
  pinMode(L_MOTOR_DIR, OUTPUT);
  pinMode(R_MOTOR_DIR, OUTPUT);

  // Setup PWM channel
  nrf_pwm_config_t pwm_config = PWM_DEFAULT_CONFIG;

  pwm_config.mode         = PWM_MODE_MTR_255;
  pwm_config.num_channels = 2;
  pwm_config.gpio_num[L_MOTOR_PWM_CHAN]  = L_MOTOR_PWM;
  pwm_config.gpio_num[R_MOTOR_PWM_CHAN]  = R_MOTOR_PWM;

  nrf_pwm_init(&pwm_config);
}

void motor_setSpeedLR(int16_t Lspeed, int16_t Rspeed) {
  if((Lspeed > 255) || (Lspeed < -255))
    return;
  if((Rspeed > 255) || (Rspeed < -255))
    return;
  // Left motor
  if (Lspeed > 0) { // Positive speed, going forward
    digitalWrite(L_MOTOR_DIR, L_FORWARD);// Change direction before speed
    nrf_pwm_set_value(L_MOTOR_PWM_CHAN, Lspeed);
  } else if (Lspeed < 0) { // Negative speed, going backward
    digitalWrite(L_MOTOR_DIR, L_BACKWARD);// Change direction before speed
    nrf_pwm_set_value(L_MOTOR_PWM_CHAN, -Lspeed);
  } else { // Zero speed, stay still
    nrf_pwm_set_value(L_MOTOR_PWM_CHAN, 0);
  }

  // Right motor
  if (Rspeed > 0) { // Positive speed, going forward
    digitalWrite(R_MOTOR_DIR, R_FORWARD);// Change direction before speed
    nrf_pwm_set_value(R_MOTOR_PWM_CHAN, Rspeed);
  } else if (Rspeed < 0) { // Negative speed, going backward
    digitalWrite(R_MOTOR_DIR, R_BACKWARD);// Change direction before speed
    nrf_pwm_set_value(R_MOTOR_PWM_CHAN, -Rspeed);
  } else { // Zero speed, stay still
    nrf_pwm_set_value(R_MOTOR_PWM_CHAN, 0);
  }
}
