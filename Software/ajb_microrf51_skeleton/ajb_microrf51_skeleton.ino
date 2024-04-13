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

// Board : AJB MicroRF51 (nRF51822-QFAA) Using Arduino-nRF5 board and BLEPeripheral library with Softdevice S130.
#include <nrf.h>

#include <SPI.h>
#include <BLEPeripheral.h>
#include "BLESerial.h"


#include "io_pins.h"
#include "nrf_pwm_noglitch.h"

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

// Bluetooth Serial instant
BLESerial BLESerial(0, 1, 2);// Choosing pin 0, 1 and 2 for bluetooth status display that we don't really have 5555.

void setup() {
  // put your setup code here, to run once:
  BLESerial.setLocalName("AJB2024");// Set Bluetooth Name
  BLESerial.begin();// Start nRF softdevice and Bluetooth stuffs
  initGPIO();// Initialize GPIO and PWM
}

void loop() {
  // put your main code here, to run repeatedly:
  BLESerial.poll();
}
