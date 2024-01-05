
// IR input pin on ESP32
// Active LOW
#define LF_IR       19
#define LB_IR       22
#define RF_IR       14
#define RB_IR       27

// Motor control stuffs

// Motor drives pin
#define L_MOTOR_DIR 33
#define L_MOTOR_PWM 32
#define R_MOTOR_DIR 26
#define R_MOTOR_PWM 25

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
