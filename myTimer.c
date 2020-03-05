/*
 * myTimer.c
 *
 *  Created on:
 *      Author:
 */

#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "myTimer.h"
extern unsigned int count0;
// TODO: Write a function that can intialize a Timer with particular values for pre-scale and count.
// Aliases for the Timers and the preScaler arguments are defined in myTimer.h
void initTimer(unsigned int timer, unsigned int preScaler, unsigned int count)
{
    Timer32_initModule (timer, preScaler, TIMER32_32BIT,TIMER32_PERIODIC_MODE ); // For the specified timer and pre-scale value, put the timer in 32-bit periodic mode.

    Timer32_setCount(timer,count);// For the specified timer, pass the count value.

   // extern void Timer32_startTimer(uint32_t timer, bool oneShot);// For the specified timer, configure the timer to repeat once it elapses.
    Timer32_startTimer( timer, REPEAT);
}

// TODO: Write a function that indicates whether Timer0 has expired.
// You have been given a such a function in the lecture slides.
bool timer0Expired(void)
{

    static unsigned int previousSnap = 0;
    unsigned int currentSnap;
    bool returnValue;

    currentSnap = Timer32_getValue(TIMER32_0_BASE);
    returnValue = (currentSnap >=previousSnap);
    previousSnap = currentSnap;
    return returnValue;


}

// TODO: Write a function that indicates whether Timer1 has expired.
// This is essentially a copy of the previous function, using a different timer.
// Since we only have two timers, later in the course we will create software timers that use a common time base.
bool timer1Expired(void)
{
    static unsigned int previousSnap1 = 0;
    unsigned int currentSnap1;
    bool returnValue1;

    currentSnap1 = Timer32_getValue(TIMER32_1_BASE);
    returnValue1 = (currentSnap1 > previousSnap1);
    previousSnap1 = currentSnap1;
    return returnValue1;


}
