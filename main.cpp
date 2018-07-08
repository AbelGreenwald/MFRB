#include "cmsis_os.h"
#include "mbed.h"
#include "INA219.hpp"

Ticker timer1;
Ticker timer2;
Ticker timer3;
Serial pc(USBTX, USBRX, 230400);

DigitalOut led1(PB_0);
DigitalOut led2(PB_7);
DigitalOut led3(PB_14);
DigitalOut  out(PC_8);

AnalogIn   aIn(A0);

INA219 ina219(PB_9, PB_8, 0x40, 1000000, RES_9BITS);
//mbed-os/targets/TARGET_STM/i2c_api.c
void active_blink1(void);
void active_blink2(void);
void active_blink3(void);

float mA = 0;

PwmOut inductor_power(PC_6);

bool print = true;
int main() {
    timer1.attach(&active_blink1, 5);
    timer2.attach(&active_blink2, .01);
    //timer3.attach(&active_blink3, 1);
//    osKernelStart();
    inductor_power.period(.01);
    inductor_power = .25;
    while (true) {
    	pc.printf("%f\r\n", aIn.read()*100.0f);
    	print = false;
    }
}

//Blink ISR
void active_blink1() {
    led1 = !led1;
    mA = 0;
}

//Blink ISR
void active_blink2() {
    led2 = !led2;
    print = true;
}

//Blink ISR
//void active_blink3() {
//    led3 = !led3;
//}