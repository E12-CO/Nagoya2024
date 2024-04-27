#ifndef __IO_PINS_H__
#define __IO_PINS_H__
// IR input pin on ESP32
// Active LOW
#define LF_IR       6
#define LB_IR       7
#define RF_IR       24
#define RB_IR       23

// Motor control stuffs

// Motor drives pin
#define L_MOTOR_DIR 17
#define L_MOTOR_PWM 18
#define R_MOTOR_DIR 19
#define R_MOTOR_PWM 20

// Motor PWM channels
#define L_MOTOR_PWM_CHAN  0
#define R_MOTOR_PWM_CHAN  1

// Motor direction constant
// Might change, depends on motor placement 
// and pole connection.
#define L_FORWARD   1
#define L_BACKWARD  !L_FORWARD
#define R_FORWARD   1
#define R_BACKWARD  !R_FORWARD
#endif
