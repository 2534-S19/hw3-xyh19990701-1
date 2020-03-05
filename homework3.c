#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "homework3.h"
#include "myGPIO.h"
#include "myTimer.h"
void button_S1();
void Bled1_lit();
unsigned int LED2_CHANGE = 0;
unsigned char led_flag=0, Button_real = 7;
unsigned char Button_flag=0;
unsigned char last_state = 0;
#define key_push GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN1)
int main(void)
 {
    // Count variables to control the LEDs.
    unsigned int count0 = 0;
    unsigned int count1 = 0;

    // TODO: Declare the variables that main uses to interact with your state machine.

    // Stops the Watchdog timer.
    initBoard();
    // Initialize the GPIO.
    // YOU MUST WRITE THIS FUNCTION IN myGPIO.c
    initGPIO();
    // Initialize Timer0 to provide a one second count interval for updating LED2.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_0_BASE, TIMER0_PRESCALER, TIMER0_COUNT);
    // Initialize Timer1 to provide a one millisecond count interval for updating the button history.
    // YOU MUST WRITE THIS FUNCTION IN myTimer.c
    initTimer(TIMER32_1_BASE, TIMER1_PRESCALER, TIMER1_COUNT);

    while(1)
    {
        // Update the color of LED2 using count0 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeLaunchpadLED2(count0);
        // Update the color of the Boosterpack LED using count1 as the index.
        // YOU MUST WRITE THIS FUNCTION BELOW.
        changeBoosterpackLED(count1);
        button_S1();
        // TODO: If Timer0 has expired, increment count0.
        // YOU MUST WRITE timer0expired IN myTimer.c
         if(timer0Expired())
            {
            LED2_CHANGE++;
            if(LED2_CHANGE==20000)LED2_CHANGE=0;
            if(LED2_CHANGE==0)led_flag=0;
            else if(LED2_CHANGE==2500)led_flag=1;
            else if(LED2_CHANGE==5000)led_flag=2;
            else if(LED2_CHANGE==7500)led_flag=3;
            else if(LED2_CHANGE==10000)led_flag=4;
            else if(LED2_CHANGE==12500)led_flag=5;
            else if(LED2_CHANGE==15000)led_flag=6;
            else if(LED2_CHANGE==17500)led_flag=7;
            else ;
            }

        // TODO: If Timer1 has expired, update the button history from the pushbutton value.
        // YOU MUST WRITE timer1expired IN myTimer.c
        if(timer1Expired())
        {
           ;// if(s1==1);
        }

        // TODO: Call the button state machine function to check for a completed, debounced button press.
        // YOU MUST WRITE THIS FUNCTION BELOW.

        // TODO: If a completed, debounced button press has occurred, increment count1.
        button_S1();
        Bled1_lit();
    }
}
///////////////////////////////////////////////////////////////////////////////////
void initBoard()
{
    WDT_A_hold(WDT_A_BASE);
}

void button_S1()
{ if( timer1Expired())
    {
        if(GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN1)==GPIO_INPUT_PIN_LOW)
        {
            if(GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN1)==GPIO_INPUT_PIN_LOW)
                 {
                     if(GPIO_getInputPinValue(GPIO_PORT_P5,GPIO_PIN1)==GPIO_INPUT_PIN_LOW)Button_flag ++;
                     if(Button_flag >88) Button_flag=0;
                 }
           else {if(Button_flag >= 1)Button_flag--;else ;}

        if(Button_flag>86){Button_real ++;Button_flag=0;if(Button_real >7) Button_real = 0;}

        }
    }
}

void Bled1_lit()
{
    if( Button_real == 0) {turnOn_BoosterpackLEDRed();turnOff_BoosterpackLEDBlue();turnOff_BoosterpackLEDGreen();}
    else if( Button_real == 1) {turnOff_BoosterpackLEDRed();turnOff_BoosterpackLEDBlue();turnOn_BoosterpackLEDGreen();}
    else if( Button_real == 2) {turnOn_BoosterpackLEDRed();turnOff_BoosterpackLEDBlue();turnOn_BoosterpackLEDGreen();}
    else if( Button_real == 3) {turnOff_BoosterpackLEDRed();turnOn_BoosterpackLEDBlue();turnOff_BoosterpackLEDGreen();}
    else if( Button_real == 4) {turnOn_BoosterpackLEDRed();turnOn_BoosterpackLEDBlue();turnOff_BoosterpackLEDGreen();}
    else if( Button_real == 5) {turnOff_BoosterpackLEDRed();turnOn_BoosterpackLEDBlue();turnOn_BoosterpackLEDGreen();}
    else if( Button_real == 6) {turnOn_BoosterpackLEDRed();turnOn_BoosterpackLEDBlue();turnOn_BoosterpackLEDGreen();}
    else if( Button_real == 7) {turnOff_BoosterpackLEDRed();turnOff_BoosterpackLEDBlue();turnOff_BoosterpackLEDGreen();}
    else;
}
// TODO: Map the value of a count variable to a color for LED2.
// Since count is an unsigned integer, you can mask the value in some way.
void changeLaunchpadLED2(unsigned int count)
{
    if( led_flag == 0) {turnOn_LaunchpadLED2Red();turnOff_LaunchpadLED2Blue();turnOff_LaunchpadLED2Green();}
    else if( led_flag == 1) {turnOff_LaunchpadLED2Red();turnOff_LaunchpadLED2Blue();turnOn_LaunchpadLED2Green();}
    else if( led_flag == 2) {turnOn_LaunchpadLED2Red();turnOff_LaunchpadLED2Blue();turnOn_LaunchpadLED2Green();}
    else if( led_flag == 3) {turnOff_LaunchpadLED2Red();turnOn_LaunchpadLED2Blue();turnOff_LaunchpadLED2Green();}
    else if( led_flag == 4) {turnOn_LaunchpadLED2Red();turnOn_LaunchpadLED2Blue();turnOff_LaunchpadLED2Green();}
    else if( led_flag == 5) {turnOff_LaunchpadLED2Red();turnOn_LaunchpadLED2Blue();turnOn_LaunchpadLED2Green();}
    else if( led_flag == 6) {turnOn_LaunchpadLED2Red();turnOn_LaunchpadLED2Blue();turnOn_LaunchpadLED2Green();}
    else if( led_flag == 7) {turnOff_LaunchpadLED2Red();turnOff_LaunchpadLED2Blue();turnOff_LaunchpadLED2Green();}
    else;

}

// TODO: Maybe the value of a count variable to a color for the Boosterpack LED
// This is essentially a copy of the previous function, using a different LED
void changeBoosterpackLED(unsigned int count)
{
//    if( Button_real == 0) {turnOn_BoosterpackLEDRed();turnOff_BoosterpackLEDBlue();turnOff_BoosterpackLEDGreen();}
//    else if( Button_real == 1) {turnOff_BoosterpackLEDRed();turnOff_BoosterpackLEDBlue();turnOn_BoosterpackLEDGreen();}
//    else if( Button_real == 2) {turnOn_BoosterpackLEDRed();turnOn_BoosterpackLEDBlue();turnOff_BoosterpackLEDGreen();}
//    else if( Button_real == 3) {turnOff_BoosterpackLEDRed();turnOn_BoosterpackLEDBlue();turnOff_BoosterpackLEDGreen();}
//    else if( Button_real == 4) {turnOn_BoosterpackLEDRed();turnOff_BoosterpackLEDBlue();turnOn_BoosterpackLEDGreen();}
//    else if( Button_real == 5) {turnOff_BoosterpackLEDRed();turnOff_BoosterpackLEDBlue();turnOn_BoosterpackLEDGreen();}
//    else if( Button_real == 6) {turnOn_BoosterpackLEDRed();turnOn_BoosterpackLEDBlue();turnOff_BoosterpackLEDGreen();}
//    else if( Button_real == 7) {turnOff_BoosterpackLEDRed();turnOff_BoosterpackLEDBlue();turnOff_BoosterpackLEDGreen();}
//    else;
}

// TODO: Create a button state machine.
// The button state machine should return true or false to indicate a completed, debounced button press.
bool fsmBoosterpackButtonS1(unsigned int  buttonhistory)
{
    bool pressed = false;
    static unsigned char timer0_state = 0xff;
    static enum {up,down} initial_state = 0;
    switch(initial_state)
    {
        case up:
            if((key_push==1))
            {
                buttonhistory = key_push;
                pressed = false;
            }
            break;
        case down:
            if((key_push==0)&(last_state))
            {
                buttonhistory  =~ key_push;
                pressed = true;
            }
            break;
        default:
            ;
    }
    buttonhistory = initial_state;
//  //  pressed = Timer32_getValue(TIMER32_1_BASE);
//
   return pressed;
}
