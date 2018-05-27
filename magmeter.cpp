#include "ak8963.h"
#include "mbed.h"

//I2C Objects for Magnetometers
I2C i2c_1(PB_9, PB_8);

//Buffers for rolling averages
volatile float avg_X[12];
volatile float avg_Y[12];
volatile float avg_Z[12];

volatile float X = 0;
volatile float Y = 0;
volatile float Z = 0;

// state output and debug info
Serial pc(USBTX, USBRX, 921600);

unsigned int j=0;
float Z_pv1, Y_pv1, X_pv1;
float Z_pv2, Y_pv2, X_pv2;

void magmeter(void const *argument) {

    i2c_1.frequency(100000); // Can't do 400 on this breadboard
//    i2c_1.frequency(100); // Can't do 400 on this breadboard

    //Magnetometer declarations
    AK8963 mag1(&i2c_1, AK8963::SLAVE_ADDR_2);
    AK8963 mag2(&i2c_1, AK8963::SLAVE_ADDR_1);
    //currently broken
//    AK8963 mag2(&i2c_2, AK8963::SLAVE_ADDR_2);
    AK8963::MagneticVector mag_rdng1;
    AK8963::MagneticVector mag_rdng2;
    //this should be a fault light
    pc.printf("Configuring Magnetometer...\r\n");
    if(mag1.checkConnection() != AK8963::SUCCESS) {
       pc.printf("Failed to communicate with AK8963 Number 1\r\n");
    }
    if(mag1.setOperationMode(AK8963::MODE_CONTINUOUS_2) != AK8963::SUCCESS) {
        pc.printf("Failed to enter magometer mode on 1\r\n");
    }

    if(mag2.checkConnection() != AK8963::SUCCESS) {
       pc.printf("Failed to communicate with AK8963 Number 2\r\n");
    }
    if(mag2.setOperationMode(AK8963::MODE_CONTINUOUS_2) != AK8963::SUCCESS) {
        pc.printf("Failed to enter magometer mode on 2\r\n");
    }

    while(true) {
        if (true) {
            mag2.getMagneticVector(&mag_rdng2);
            osDelay(2);
            mag1.getMagneticVector(&mag_rdng1);
            osDelay(2);

            Z_pv1 = floor(mag_rdng1.mz / 10) - 60;
            Y_pv1 = floor(mag_rdng1.my / 10);
            X_pv1 = floor(mag_rdng1.mx / 10);

            Z_pv2 = floor(mag_rdng2.mz / 10) - 60;
            Y_pv2 = floor(mag_rdng2.my / 10);
            X_pv2 = floor(mag_rdng2.mx / 10);
/*
            for (j=0;j<12;j++) {
                if (j != 11)
                {
                    avg_X[j] = avg_X[j+1];
                    avg_Y[j] = avg_Y[j+1];
                    avg_Z[j] = avg_Z[j+1];
                } else {
                    avg_X[j] = X_pv1;
                    avg_Y[j] = Y_pv1;
                    avg_Z[j] = Z_pv1;
                }
//                pc.printf("%f,%i\r\n",avg_Z[j],j);
                X = (X + avg_X[j])/12;
                Y = (Y + avg_Y[j])/12;
                Z = (Z + avg_Z[j])/12;
            }
*/
            pc.printf("%.f,%.f,%.f,%.f,%.f,%.f\r\n", X_pv1,Y_pv1,Z_pv1,X_pv2,Y_pv2,Z_pv2);
//            osDelay(25);
            if (mag_rdng1.isOverflow == true) {
            }
        }
    }
}