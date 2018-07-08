#ifndef MAIN_H
#define MAIN_H

#define EIGEN_NO_MALLOC

/* Define Pins */
#define inductor_X_l_in1  NaN
#define inductor_X_l_in2  NaN
#define inductor_X_l_enA  NaN
#define inductor_Y_l_in1  NaN
#define inductor_Y_l_in2  NaN
#define inductor_Y_l_enA  NaN
#define inductor_X_h_in1  NaN
#define inductor_X_h_in2  NaN
#define inductor_X_h_enA  NaN
#define inductor_Y_h_in1  NaN
#define inductor_Y_h_in2  NaN
#define inductor_Y_h_enA  NaN
#define inductor_Z_in     PA_9
#define inductor_Z_enA    PC_9
#define inductor_Z_Read   PC_3

/* Define Calibration Settings */

/* Z Settings */
#define inductor_Z_input_min -100.0
#define inductor_Z_input_max  800.0
#define inductor_Z_set_point  200.0
#define inductor_Z_output_min  -1.0
#define inductor_Z_output_max   1.0
#define inductor_Z_timestep     0.015

/* X_h Settings */
#define inductor_X_h_input_min   0.0
#define inductor_X_h_input_max   0.0
#define inductor_X_h_set_point   0.0
#define inductor_X_h_output_min  0.0
#define inductor_X_h_output_max  0.0
#define inductor_X_h_timestep    0.0

/* X_l Settings */
#define inductor_X_l_input_min -100.0
#define inductor_X_l_input_max  800.0
#define inductor_X_l_set_point  200.0
#define inductor_X_l_output_min  -1.0
#define inductor_X_l_output_max   1.0
#define inductor_X_l_timestep     0.015

//should come from rlocus
#define inductor_Z_Kc 0.5
#define inductor_Z_Kd 5
#define inductor_Z_Ki 1

#define inductor_MZ_l_in1 NaN
#define inductor_MZ_l_in2 NaN
#define inductor_MZ_l_enA NaN

#define inductor_MZ_h_in1 NaN
#define inductor_MZ_h_in2 NaN
#define inductor_MZ_h_enA NaN

#define test_pin_mag_thread PA_3
#define test_pin_ind_thread PA_2
#define test_pin_mtr_thread PA_10

#define mag_data_ready_pin PC_2
#define mag_data_trgr_pin  PH_1

/* Set Pins */


// blinking LED
DigitalOut led1(PB_0);
DigitalOut led2(PB_7);
DigitalOut led3(PB_14);

DigitalOut Freq(D1);

DigitalOut mag_thread(test_pin_mag_thread);
DigitalOut ind_thread(test_pin_ind_thread);
DigitalOut mtr_thread(test_pin_mtr_thread);
DigitalOut ak8963_trg(mag_data_trgr_pin);
//Temp Sensor for inductor_X1
AnalogIn inductor_Z_Reading(inductor_Z_Read);

AnalogIn Calibrate_Z_Kc(A5);
AnalogIn Calibrate_Z_Kd(A4);
AnalogIn Calibrate_Z_Ki(A3);
// Tunnel Motor ESC Driver
//Servo tunnel_motor(D3);
// Timer inturrupt for power LED
Ticker timer1;
Ticker timer2;
Ticker timer3;
Ticker ms;
Ticker ak8963_tmr;


float power;

/* Function Prototypes  */
void active_blink1(void);
void active_blink2(void);
void active_blink3(void);
void count_ms(void);
void Calculate(void const*);
void Inductors(void const*);
void magmeter(void const*);
void Process_PID(Inductor& S, float a_value);

/* Threads  */
osThreadDef(magmeter, osPriorityNormal, 12000);
osThreadDef(Inductors, osPriorityNormal, 1024); //4K stack
osThreadDef(Calculate, osPriorityNormal, 12000);

#endif