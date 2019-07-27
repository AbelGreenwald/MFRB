#include "cmsis_os.h"
#include "mbed.h"
#include "math.h"
#include "ak8963.h"

#define PERIOD .1
#define READRATE PERIOD / 500

Ticker timer1;
Ticker timer2;
Ticker timer3;
Serial pc(USBTX, USBRX, 2000000);
DigitalOut led3(PB_14);
DigitalOut  out(PC_8);

AnalogIn   aIn(A0);
float PrintVal;
float avgCur = 0;
bool printFlag;

//INA219 ina219(PB_9, PB_8, 0x40, 1000000, RES_9BITS);
//mbed-os/targets/TARGET_STM/i2c_api.c
void read(void);
void ISR_reset(void);

SPI mag_read_1(PA_7, PA_6, PA_5); //PinName mosi, PinName miso, PinName sclk

DigitalOut SS(PB_6);

float mA = 0;
float avg_rd = 0;
//PwmOut inductor_power(PC_6);

int average =  16;
int print = 0;
float M_1_avg = 0.0;
int main() {            
    led3 = true;
 //   timer1.attach(&read, READRATE);
 //   timer2.attach(&ISR_reset, PERIOD);
    
//    inductor_power.period(PERIOD);
//    inductor_power = .375;
    
    mag_read_1.format(8,3);
    wait_us(100);
    mag_read_1.frequency(20000000);
    wait_us(100);
    AK8963 readings_1(&mag_read_1, &SS);

    readings_1.setPrecision(AK8963_MODE_BIT_16);
    readings_1.setOperationMode(AK8963_MODE_CONT2);

    pc.printf("\r\nChecking Connection...\r\n");

        if (readings_1.checkConnection()) {
            pc.printf("\r\nConnection Valid\r\n");
    }

    while (true) {
//      if (printFlag == true) {
        if (readings_1.checkDataReady()) {
   
            led3 = !led3;
            printFlag = false;
            M_1_avg += readings_1.getX();
            print++;
            readings_1.checkOverflow();
        }
        if (print == 3) {
            pc.printf("X=%7.3f\r\n",M_1_avg / 3.0);
            M_1_avg = 0.0;
            print = 0;
        }
    }
}

float rd = 0;
float cur;
float sum_squares;
#define resistor 0.012
#define ref_voltage 3.0
//V = I R
void read() {

    for (int i=0;i<4;i++)
    {
        //rd += 2 * (aIn.read()-.5);
        ;
    }
    rd = rd / 4;
    //rd = 2 * (aIn.read()-.5);
    cur += rd * ref_voltage / resistor / 50;
    rd=0;
}

void ISR_reset() {
    PrintVal = cur * READRATE * 10;
    cur = 0;
    printFlag = true;
}