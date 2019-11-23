#ifndef MAIN_H
#define MAIN_H

/* Define Pins */
#define INDUCTOR_X_L_POLARITY PE_15
#define INDUCTOR_X_L_PWM      PE_14
#define INDUCTOR_X_L_CURRENT  PF_7

#define INDUCTOR_Z_POLARITY PB_11
#define INDUCTOR_Z_PWM      PB_10
#define INDUCTOR_Z_CURRENT  PF_9

//#define INDUCTOR_X_H_POLARITY NaN
//#define INDUCTOR_X_H_PWM      NaN

//#define INDUCTOR_Y_L_POLARITY NaN
//#define INDUCTOR_Y_L_PWM      NaN

//#define INDUCTOR_Y_H_POLARITY NaN
//#define INDUCTOR_Y_H_PWM      NaN

#define MAG_DATA_READY_PIN PG_4
//#define MAG_DATA_TRGR_PIN  PH_1

// 16 BIT TFT LCD PARALLEL
#define DB0  PF_1
#define DB1  PE_5
#define DB2  PF_2
#define DB3  PF_0
#define DB4  PD_1
#define DB5  PD_0
#define DB6  PG_1
#define DB7  PG_0
#define DB8  PD_2
#define DB9  PH_1
#define DB10 PD_4
#define DB11 PD_3
#define DB12 PD_5
#define DB13 PG_2
#define DB14 PD_6
#define DB15 PG_3
#define RS   PC_10
#define WR   PC_11
#define CS   PE_3
#define RD   PC_12
#define RST  PE_4

/* Define Calibration Settings */

/* Z Settings */
#define INDUCTOR_Z_INPUT_MIN -100.0
#define INDUCTOR_Z_INPUT_MAX  800.0
#define INDUCTOR_Z_SET_POINT  200.0
#define INDUCTOR_Z_OUTPUT_MIN  -1.0
#define INDUCTOR_Z_OUTPUT_MAX   1.0
#define INDUCTOR_Z_TIMESTEP     0.015

/* Y_h Settings */
#define INDUCTOR_Y_H_INPUT_MIN  0
#define INDUCTOR_Y_H_INPUT_MAX  0
#define INDUCTOR_Y_H_SET_POINT  0
#define INDUCTOR_Y_H_OUTPUT_MIN 0
#define INDUCTOR_Y_H_OUTPUT_MAX 0
#define INDUCTOR_Y_H_TIMESTEP   0

/* Y_l Settings */
//#define INDUCTOR_Y_L_INPUT_MIN  0
//#define INDUCTOR_Y_L_INPUT_MAX  0
//#define INDUCTOR_Y_L_SET_POINT  0
//#define INDUCTOR_Y_L_OUTPUT_MIN 0
//#define INDUCTOR_Y_L_OUTPUT_MAX 0
//#define INDUCTOR_Y_L_TIMESTEP   0

/* X_h Settings */
//#define INDUCTOR_X_H_INPUT_MIN   0.0
//#define INDUCTOR_X_H_INPUT_MAX   0.0
//#define INDUCTOR_X_H_SET_POINT   0.0
//#define INDUCTOR_X_H_OUTPUT_MIN  0.0
//#define INDUCTOR_X_H_OUTPUT_MAX  0.0
//#define INDUCTOR_X_H_TIMESTEP    0.0

/* X_l Settings */
//#define INDUCTOR_X_L_INPUT_MIN -100.0
//#define INDUCTOR_X_L_INPUT_MAX  800.0
//#define INDUCTOR_X_L_SET_POINT  200.0
//#define INDUCTOR_X_L_OUTPUT_MIN  -1.0
//#define INDUCTOR_X_L_OUTPUT_MAX   1.0
//#define INDUCTOR_X_L_TIMESTEP     0.015

/* Magnetometer 1 Settings */
#define MAGNETOMETER_SPI_FREQUENCY 500000 //HZ
#define INDUCTOR_FREQUENCY 100 //Hz

//Should come from rlocus after mass is measured
#define inductor_Z_Kc 0.5
#define inductor_Z_Kd 5
#define inductor_Z_Ki 1


#define inductor_X_l_Kc 0.5
#define inductor_X_l_Kd 5
#define inductor_X_l_Ki 1

// blinking LED
DigitalOut led1(PB_0);
DigitalOut led2(PB_7);
DigitalOut led3(PB_14);

AnalogIn inductor_z_current(INDUCTOR_Z_CURRENT);

// Timer inturrupt for power LED
Ticker timer1;

DigitalIn mag_pin(MAG_DATA_READY_PIN);
InterruptIn mag_ready(MAG_DATA_READY_PIN);


//mail_box
typedef struct {
  float    xval; /* AD result of measured voltage */
  float    yval; /* AD result of measured current */
  float    zval; /* AD result of measured current */
  bool overflow; /* A counter value               */
} mag_reading;

osMailQDef(mag_mail, 1, mag_reading);
osMailQId  mag_mail;

/* Function Prototypes  */
void _isr_active_blink(void);
void _isr_pwm_cycle(void);
void _isr_mag_data_ready(void);
void count_ms(void);
void readCurrent(void const*);
void inductor_x(void const*);
void magnetometer(void const*);
void display(void const*);
void processPID(Inductor& S, float a_value);

//LCD Pins
//BusOut buspins(DB0, DB1, DB2, DB3, DB4, DB5, DB6, DB7, DB8, DB9, DB10, DB11, DB12, DB13, DB14, DB15);

/* Threads  */
osThreadDef(magnetometer, osPriorityHigh, 4096);
osThreadDef(inductor_x, osPriorityNormal, 4096);
osThreadDef(readCurrent, osPriorityNormal, 8192);
osThreadDef(display, osPriorityLow, 8192);
#endif
