// Soft PWM effort on nRF51 Arduino
// Tried by TinLethax (2024).

#include <nrf.h>
#include "nrf_pwm_noglitch.h"

#include <BLEPeripheral.h>
#include <iBeacon.h>

iBeacon beacon;

#define MOTOR_L_PWM   4
#define MOTOR_R_PWM   9

void pwm_init() {
  //pinMode(MOTOR_L_PWM, OUTPUT);
  nrf_pwm_config_t pwm_config = PWM_DEFAULT_CONFIG;

  pwm_config.mode         = PWM_MODE_MTR_255;
  pwm_config.num_channels = 2;
  pwm_config.gpio_num[0]  = MOTOR_L_PWM;
  pwm_config.gpio_num[1]  = MOTOR_R_PWM;

  nrf_pwm_init(&pwm_config);
}


void setup() {
  // put your setup code here, to run once:
  char* uuid                   = "a196c876-de8c-4c47-ab5a-d7afd5ae7127";
  unsigned short major         = 0;
  unsigned short minor         = 0;
  unsigned short measuredPower = -55;

  beacon.begin(uuid, major, minor, measuredPower);

  pwm_init();
  nrf_pwm_set_value(0, 50);
  nrf_pwm_set_value(1, 127);
}

void loop() {
  // put your main code here, to run repeatedly:
  beacon.loop();
}
