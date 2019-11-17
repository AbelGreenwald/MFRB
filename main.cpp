#include "cmsis_os.h"
#include "Inductor.h"
#include "main.h"
#include "mbed.h"
#include "PID.h"
#include "ak8963.h"
#include "TextLCD_ST7032I2C.h"

volatile bool cycle_complete;
Serial pc(USBTX, USBRX, 1000000);

TextLCD_ST7032I2C LCD(PB_9, PB_8, 0x3F, 16, 2);
//PCF8574 lcd(PB_9, PB_8, 0x3F);
int main() {
  timer1.attach(&_isr_active_blink, .25);
  timer1.attach(&_isr_pwm_cycle, inductor_freq);
  osThreadCreate(osThread(magnetometer), NULL); //med, locates position
  osThreadCreate(osThread(inductors), NULL); //high, fights gravity
  osThreadCreate(osThread(readCurrent), NULL); //low
  osThreadCreate(osThread(display), NULL); //low

  // state output and debug info
  osDelay(osWaitForever);
}

//Blink ISR
void _isr_active_blink() {
  led1 = !led1;
}

void _isr_pwm_cycle() {
  cycle_complete = true;
}

void magnetometer(void const *argument) {
  SPI magnometeter_spi(PB_5, PB_4, PB_3);
  magnometeter_spi.frequency(MAGNETOMETER_FREQUENCY);
  magnometeter_spi.format(8,3);
  osDelay(1);
  DigitalOut magnometeter_spi_cs(PG_10);
  AK8963 ak8963(&magnometeter_spi, &magnometeter_spi_cs);
  ak8963.setPrecision(AK8963_MODE_BIT_16);
  ak8963.setOperationMode(AK8963_MODE_CONT2);
  osDelay(10);
  if(!ak8963.checkConnection()) {
   pc.printf("Failed to communicate with AK8963\r\n");
  }
  while (true) {
    osDelay(10);
    if (!ak8963.checkDataReady()) {
      pc.printf("X=%7.3f Y=%7.3f Z=%7.3f\n\r",ak8963.getX(),ak8963.getY(),ak8963.getZ());
    }
    if(ak8963.checkOverflow()) {
         pc.printf("Magnetic Overflow\r\n");
    }
  }
}

void inductors(void const *argument) {
  PwmOut     d1(PE_14);
  DigitalOut polarity(PE_0);
  polarity = 1;
  d1.period(inductor_freq);
  d1.write(.5);
  osDelay(osWaitForever);
}

void readCurrent(void const *argument) {
  float current, current_rdg;
  int count = 0;
  while (true) {
    current_rdg += inductor_Z_Reading.read() - .5;
    count++;
    if (cycle_complete == true) {
      current = 3.3 * current_rdg/count/20/.09*1000;
      //pc.printf("%f mA #\%i#\r\n",current,count);
      count = 0;
      current_rdg = 0;
      cycle_complete = false;
    }
  }
}

void display(void const *argument) {

  while (true) {
    for (int i=0;i<8;i++) {
      LCD.cls();
      LCD.locate(0,0);
      for (int j=0;j<32;j++) {
        LCD.printf("%c", i*32+j);
      }
    }
  }
  // wait for signal
}
