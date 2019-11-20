#include "cmsis_os.h"
#include "Inductor.h"
#include "main.h"
#include "mbed.h"
#include "PID.h"
#include "ak8963.h"
#include "gfx.h"

volatile bool cycle_complete;
Serial pc(USBTX, USBRX, 1000000);

//PCF8574 lcd(PB_9, PB_8, 0x3F);
int main() {
  timer1.attach(&_isr_active_blink, .25);
  timer1.attach(&_isr_pwm_cycle, 1.0/INDUCTOR_FREQUENCY);
  osThreadCreate(osThread(magnetometer), NULL); //med, locates position
  osThreadCreate(osThread(inductor_x), NULL); //high, fights gravity
  osThreadCreate(osThread(readCurrent), NULL); //low
  osThreadCreate(osThread(display), NULL); //low
  pc.printf("Starting Up...\r\n");
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
  magnometeter_spi.frequency(MAGNETOMETER_SPI_FREQUENCY);
  magnometeter_spi.format(8,3);
  DigitalOut magnometeter_spi_cs(PG_10);
  AK8963 ak8963(&magnometeter_spi, &magnometeter_spi_cs);
  ak8963.setPrecision(AK8963_MODE_BIT_16);
  ak8963.setOperationMode(AK8963_MODE_CONT2);
  float x_val, y_val, z_val;
  osDelay(10);
  if(!ak8963.checkConnection()) {
   pc.printf("Failed to communicate with AK8963\r\n");
  }
  while (true) {
    osDelay(10);
    if (ak8963.checkDataReady()) {
      x_val = ak8963.getX();
      if(ak8963.checkOverflow()) {
           pc.printf("Magnetic Overflow\r");
      }
      y_val = ak8963.getY();
      if(ak8963.checkOverflow()) {
           pc.printf("Magnetic Overflow\r");
      }
      z_val = ak8963.getZ();
      if(ak8963.checkOverflow()) {
           pc.printf("Magnetic Overflow\r");
      }
      //pc.printf("X=%7.3f Y=%7.3f Z=%7.3f\n", x_val, y_val, z_val);
    }
  }
}

// trigger when data is ready on magnetometer

void inductor_x(void const *argument) {
  PwmOut     inductor_driver(INDUCTOR_X_L_PWM);
  DigitalOut polarity(INDUCTOR_X_L_POLARITY);
  inductor_driver.period(1.0/INDUCTOR_FREQUENCY);
  inductor_driver.write(0.25f);
  polarity.write(1);
  pc.printf("Setting power to %f", inductor_driver.read());
  osDelay(osWaitForever);
}

void readCurrent(void const *argument) {
  float current, current_rdg;
  int count = 0;
  float prev_current=0;
  while (true) {
    current_rdg += inductor_z_current.read() - .5;
    count++;
    if (cycle_complete == true) {
      current = 3.3 * current_rdg/count/20/.09*1000;
      if (abs(1-(prev_current/current)) > 0.15) {
        pc.printf("%f mA #\%i# %f diff\r\n",current,count, abs(1-(prev_current/current)));
      }
      count = 0;
      current_rdg = 0;
      cycle_complete = false;
      prev_current = current;
    }
  }
}

void display(void const *argument) {
  //PinName CS, PinName RESET, PinName RS, PinName WR, BusOut* DATA_PORT, PinName BL, PinName RD, backlight_t blType, float defaultBackLightLevel )
  osDelay(osWaitForever);
  // wait for signal
}
