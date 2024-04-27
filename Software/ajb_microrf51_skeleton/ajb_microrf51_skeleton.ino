// =================================================================================================================================================================
// =================================================================================================================================================================
// =================================================================================================================================================================
// THIS IS A SKELETAL CODE | PLEASE SAVE THE MODIFIED CODE AS NEW PROJECT
// KEEP THE SKELETAL CODE ! | KEEP THE SKELETAL CODE ! | KEEP THE SKELETAL CODE ! | KEEP THE SKELETAL CODE ! | KEEP THE SKELETAL CODE ! | KEEP THE SKELETAL CODE ! |
// =================================================================================================================================================================
// =================================================================================================================================================================
// =================================================================================================================================================================
// AJB Micro's skeletal code for basic I/O of IR sensors and motors
// Coded By TinLethax for Robot Club Engineering KMITL in the Nagoya Microrobot contest 2024.

// Board : AJB MicroRF51 (nRF51822-QFAA) Using Arduino-nRF5 board and Enhanced ShockBurse protocol with nRF24L remote.
#include <nrf.h>
#include <nrf51_bitfields.h>


uint8_t receive_buffer[32];

unsigned long poll_millis = 0;

#include "io_pins.h"

// GPIO for IR sensors
// IMPORTANT :
// Sensors are ACTIVE LOW,
// meaning that when meet the wall will read logic 0.
// And open air will read logic 1.
// For the current board revision (rev 1.0)
// doesn't capable of AnalogRead on these pins.
// digitalRead(LF_IR); -> Left Front sensor
// digitalRead(LB_IR); -> Left Back sensor
// digitalRead(RF_IR); -> Right Front sensor
// digitalRead(RB_IR); -> Right Back sensor

// Motor control
// use this function :
//
// motor_setSpeedLR(left_motor, right_motor);
//
// Since the PWM resolution is 8 bit,
// the value range is -255 to 0 to 255.
// This function take in two int16_t variable as speed.
// Also there are MACROs in io_pins.h that you can customize
// the default direction of each left and right motor separately.
// Name L/R_FORWARD/BACKWARD

void setup() {
  // put your setup code here, to run once:
  initGPIO();// Initialize GPIO and PWM

  // 2.4GHz nRF Enhanced ShockBurst for communicating with nRF24L01+ Joy controller
  //nrf51_esb_init(0xF0F0F0F0D2, 0xF0F0F0F0E1, 76);
  //nrf51_esb_setPTR(receive_buffer);
  
  //Serial.setPins(16, 15);
  //Serial.begin(115200);
  //delay(100);
  //Serial.println("AJB2024");
}

void loop() {
  // put your main code here, to run repeatedly:
  while (true) {
    pwm_runner();// Must be run in order to use PWM 
    
  }
}
