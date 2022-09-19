// Lab 3
// This lab is done by the following two students as noted below
// Author: Jonathan Au Wai Chong (2101277) & LIM KEI YIANG (2100593)

/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdio.h>

#include <stdbool.h>
#define RED GPIO_PIN0
#define GREEN GPIO_PIN1
#define BLUE GPIO_PIN2

uint32_t g_notches_detected;

int main(void)
{
    g_notches_detected = 0;

    // Disable Watchdog timer
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Stopping the Watchdog Timer


    // P2.5 as input with pull up resistor
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN5);


    /* Configuring P2.0, P2.1, P2.2 as output low on pin */
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, RED);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, GREEN);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P2, BLUE);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, RED);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GREEN);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, BLUE);

    // Clear interrupt flag for pin P2.5
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN5);

    // Enable interrupt for pin P2.5
    MAP_GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN5);

    // Enable interrupt for Port 2
    MAP_Interrupt_enableInterrupt(INT_PORT2);


    /* Enabling MASTER interrupts */
    MAP_Interrupt_enableMaster();   

    /* Going to LPM3 */
    while (1)
    {

        MAP_PCM_gotoLPM3();
    }

}

// To get the number of rotation bbased on the number of notches
// Based on 1 rotation == 20 notches
uint16_t getRotation(uint32_t notches){
    if(notches >= 20 && notches< 40){
        return 1;
    }else if(notches >= 40 && notches < 60){
        return 2;
    }else if(notches >= 60 && notches < 80){
        return 3;
    }else if(notches >= 80 && notches < 100){
        return 4;
    }else if(notches >= 100 && notches < 120){
        return 5;
    }else if(notches >= 120 && notches < 140){
        return 6;
    }else if(notches == 140){
        return 7;
    }else{
        return 0;
    }
}

void PORT2_IRQHandler(void)
{

    uint32_t status;
    // Get interrupt status for PORT 2 and store it in local var
    status = MAP_GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    if(status){
        if(g_notches_detected > 140){
            g_notches_detected = 0;
        }else{
            g_notches_detected++;
        }
        uint16_t counter = getRotation(g_notches_detected);

        switch(counter){
            case 1:
                // BLUE ON, RED AND GREEN OFF
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, RED);
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GREEN);
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, BLUE);

                break;
            case 2:
                // GREEN ON, RED AND BLUE OFF
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, RED);
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GREEN);
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, BLUE);
                break;
            case 3:
                // GREEN AND BLUE ON, RED OFF
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, RED);
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GREEN);
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, BLUE);
                break;
            case 4:
                // RED ON, GREEN AND BLUE OFF
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, RED);
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GREEN);
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, BLUE);
                break;
            case 5:
                // RED and BLUE LED ON. GREEN OFF
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, RED);
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GREEN);
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, BLUE);
                break;
            case 6:
                // RED and GREEN LED ON. BLUE OFF
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, RED);
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GREEN);
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, BLUE);
                break;
            case 7:
                // RGB on
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, RED);
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GREEN);
                MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, BLUE);
                break;
            default:
                // RGB OFF
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, RED);
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GREEN);
                MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, BLUE);
                break;
        }

        // Clear Interrupt flag for port 2
        MAP_GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
    }
}


