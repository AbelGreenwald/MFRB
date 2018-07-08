#include "cmsis_os.h"
#include "Inductor.h"
#include "main.h"
#include "mbed.h"
#include "PID.h"

void Inductors(void const *argument) {

    //Set Inductor Z values
    Inductor inductor_Z(inductor_Z_enA, inductor_Z_in);
    inductor_Z.setInputLimits(inductor_Z_input_min, inductor_Z_input_max);
    inductor_Z.setOutputLimits(inductor_Z_output_min, inductor_Z_output_max);
    inductor_Z.setTunings(inductor_Z_Kc,inductor_Z_Ki,inductor_Z_Kd);
    inductor_Z.setMode(AUTO_MODE);
    inductor_Z.setInterval(inductor_Z_timestep);
    inductor_Z.setSetPoint(inductor_Z_set_point);

    // Process PID loop
    while (true) {
        // Semiphore from completed calculation here
        // Wait for data to be available,  Probably signal 
        Process_PID(inductor_Z, 123);
        // Process_PID(inductor_X_h);
        // Process_PID(inductor_X_l);
        // Process_PID(inductor_Y_h);
        // Process_PID(inductor_Y_l);
        // Process_PID(inductor_MZ_h;
        // Process_PID(inductor_MZ_l);
    }
}

void Process_PID(Inductor& inductor, float a_value) {  //get this from calculated forces probably a memory pool
    inductor.setProcessValue(a_value);
    power = inductor.compute();

    if (power >= 0.0) {
        inductor.setPolarity(0);
        inductor.setPower(power);
    } else {
        power = -(power);
        inductor.setPolarity(1);
        inductor.setPower(power);
    }

}

int main() {
    osKernelStart();
    timer1.attach(&active_blink1, .25);
    timer2.attach(&active_blink2, .5);
    timer3.attach(&active_blink3, 1);
    osThreadCreate(osThread(magmeter), NULL);
    //osThreadCreate(osThread(Inductors), NULL);
    //osThreadCreate(osThread(Calculate), NULL);

    // state output and debug info
//    Serial pc(USBTX, USBRX, 921600);
    osDelay(osWaitForever);
}

//Blink ISR
void active_blink1() {
    led1 = !led1;
}

//Blink ISR
void active_blink2() {
    led2 = !led2;
}

//Blink ISR
void active_blink3() {
    led3 = !led3;
}
void Calculate(void const *argument) {}