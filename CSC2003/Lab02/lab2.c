/*
 * This code is created by
 * Jonathan Au Wai Chong (2101277) & Lim Kei Yiang (2100593)
 */

/* DriverLib Includes */
#include "driverlib.h"

/* Standard Includes */
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#define RED GPIO_PIN0
#define GREEN GPIO_PIN1
#define BLUE GPIO_PIN2

void toggleLedOne(){
    MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P1, RED);
    delay();
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, RED);
}

void toggleLedTwo( bool flagGreen, bool flagBlue ){
    if ( !flagGreen && !flagBlue ){
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, RED);
    }
    if ( flagGreen ){
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, RED);
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, GREEN);
    }
    if ( flagBlue ){
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, RED);
        MAP_GPIO_setOutputHighOnPin(GPIO_PORT_P2, BLUE);
    }
    delay();
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, RED);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, GREEN);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P2, BLUE);
}

void delay(){
    int i;
    for(i=0; i<50000; i++){}
}

void setup(){
    GPIO_setAsOutputPin(GPIO_PORT_P1, RED);
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, RED);

    GPIO_setAsOutputPin(GPIO_PORT_P2, RED);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GREEN);
    GPIO_setAsOutputPin(GPIO_PORT_P2, BLUE);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, RED);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GREEN);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, BLUE);

    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
}

void main(void){
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD; // Stopping the Watchdog Timer
    setup();

    bool flagGreen = false;
    bool flagBlue = false;

    while(1)
    {
        toggleLedOne();
        toggleLedTwo(flagGreen, flagBlue);

        if(GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == ((uint8_t)0x00)){
            flagGreen = true;
        }
        if(GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN1) == ((uint8_t)0x01)){
            flagGreen = false;
        }
        if(GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == ((uint8_t)0x00)){
            flagBlue = true;
        }
        if(GPIO_getInputPinValue(GPIO_PORT_P1, GPIO_PIN4) == ((uint8_t)0x01)){
            flagBlue = false;
        }

    }
}
