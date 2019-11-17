#ifndef MAIN_H
#define MAIN_H

#define EIGEN_NO_MALLOC

/* Define Pins */
//#define inductor_X_l_in1  NaN
//#define inductor_X_l_in2  NaN
//#define inductor_X_l_enA  NaN
//#define inductor_Y_l_in1  NaN
//#define inductor_Y_l_in2  NaN
//#define inductor_Y_l_enA  NaN
//#define inductor_X_h_in1  NaN
//#define inductor_X_h_in2  NaN
//#define inductor_X_h_enA  NaN
#define inductor_Y_h_in1  NaN
#define inductor_Y_h_in2  NaN
#define inductor_Y_h_enA  NaN
#define inductor_Z_in     PA_9
#define inductor_Z_enA    PC_9
#define inductor_Z_Read   PC_0

/* Define Calibration Settings */

/* Z Settings */
#define inductor_Z_input_min -100.0
#define inductor_Z_input_max  800.0
#define inductor_Z_set_point  200.0
#define inductor_Z_output_min  -1.0
#define inductor_Z_output_max   1.0
#define inductor_Z_timestep     0.015

/* Y_h Settings */
#define inductor_Y_h_input_min  0
#define inductor_Y_h_input_max  0
#define inductor_Y_h_set_point  0
#define inductor_Y_h_output_min 0
#define inductor_Y_h_output_max 0
#define inductor_Y_h_timestep   0

/* Y_l Settings */
//#define inductor_Y_l_input_min  0
//#define inductor_Y_l_input_max  0
//#define inductor_Y_l_set_point  0
//#define inductor_Y_l_output_min 0
//#define inductor_Y_l_output_max 0
//#define inductor_Y_l_timestep   0

/* X_h Settings */
//#define inductor_X_h_input_min   0.0
//#define inductor_X_h_input_max   0.0
//#define inductor_X_h_set_point   0.0
//#define inductor_X_h_output_min  0.0
//#define inductor_X_h_output_max  0.0
//#define inductor_X_h_timestep    0.0

/* X_l Settings */
//#define inductor_X_l_input_min -100.0
//#define inductor_X_l_input_max  800.0
//#define inductor_X_l_set_point  200.0
//#define inductor_X_l_output_min  -1.0
//#define inductor_X_l_output_max   1.0
//#define inductor_X_l_timestep     0.015

/* Magnetometer 1 Settings */
#define MAGNETOMETER_FREQUENCY 500000


//Should come from rlocus
#define inductor_Z_Kc 0.5
#define inductor_Z_Kd 5
#define inductor_Z_Ki 1

#define inductor_Y_l_Kc 0.5
#define inductor_Y_l_Kd 5
#define inductor_Y_l_Ki 1

//#define inductor_MZ_l_in1 NaN
//#define inductor_MZ_l_in2 NaN
//#define inductor_MZ_l_enA NaN

//#define inductor_MZ_h_in1 NaN
//#define inductor_MZ_h_in2 NaN
//#define inductor_MZ_h_enA NaN

//#define test_pin_mag_thread PA_3
//#define test_pin_ind_thread PA_2
//#define test_pin_mtr_thread PA_10

#define mag_data_ready_pin PC_2
#define mag_data_trgr_pin  PH_1
#define inductor_freq 0.004546
/* Set Pins */


// blinking LED
DigitalOut led1(PB_0);
DigitalOut led2(PB_7);
DigitalOut led3(PB_14);

AnalogIn inductor_Z_Reading(inductor_Z_Read);

// Timer inturrupt for power LED
Ticker timer1;

/* Function Prototypes  */
void _isr_active_blink(void);
void _isr_pwm_cycle(void);
void count_ms(void);
void readCurrent(void const*);
void inductors(void const*);
void magnetometer(void const*);
void display(void const*);
void processPID(Inductor& S, float a_value);

/* Threads  */
osThreadDef(magnetometer, osPriorityHigh, 1024);
osThreadDef(inductors, osPriorityLow, 4096); //2K stack
osThreadDef(readCurrent, osPriorityLow, 4096);//4K stack
osThreadDef(display, osPriorityHigh, 1024);
#endif
