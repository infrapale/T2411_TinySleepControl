#include "Arduino.h"
#include <avr/sleep.h>
#include <avr/power.h>
#include "main.h"
#include "io.h"

/*

  void io_initialize(void)
  {
    pinMode(PIN_EDOG_CLR, INPUT);
    pinMode(PIN_EDOG_WAKE, INPUT_PULLUP);
    pinMode(PIN_PWR_OFF_0, OUTPUT);
    digitalWrite(PIN_PWR_OFF_0, LOW);
  }
*/

void io_blink_color_times(uint8_t pin, uint8_t n, uint16_t us)
{
  for (uint8_t i=0; i < n; i++)
  {
    digitalWrite(pin, HIGH);
    delayMicroseconds(us);
    digitalWrite(pin, LOW);
    delayMicroseconds(us);
  }
}


void io_power_off(void)
{
    PORTA.DIRCLR = PIN_PWR_OFF_BM;
    // PORTA.OUTSET = PIN_PWR_OFF_BM;
    //pinMode(PIN_PWR_OFF_0, OUTPUT);
    //digitalWrite(PIN_PWR_OFF_0, LOW);
}

void io_power_on(void)
{
    PORTA.DIRSET = PIN_PWR_OFF_BM;
    PORTA.OUTCLR = PIN_PWR_OFF_BM;
    // pinMode(PIN_PWR_OFF_0, INPUT);
    // digitalWrite(PIN_PWR_OFF_0, HIGH);
}

bool io_goto_sleep_inp(void)
{
    PORTA.DIRCLR = PIN_SLEEP_BM;
    bool zzz  = ((PORTA.IN & PIN_SLEEP_BM)  == 0);
    PORTA.PIN3CTRL = PORT_PULLUPEN_bm | PORT_ISC_INPUT_DISABLE_gc;
    return zzz;
}

uint8_t io_get_clr_input(void)
{
    return digitalRead(PIN_EDOG_CLR);
}

bool io_is_wake_up(void)
{
   return (digitalRead(PIN_EDOG_WAKE) == 0); 
}


void io_gpio_enable(void)
{
  PORTA.DIRSET = PIN_PWR_OFF_BM;
  PORTA.OUTSET = PIN_PWR_OFF_BM;
  //PORTA.DIRSET = PIN_TEST_BM;     
  //PORTA.OUTCLR = PIN_TEST_BM;
  PORTA.DIRCLR = PIN_SLEEP_BM;
  PORTA.PIN3CTRL |= PORT_ISC_INTDISABLE_gc;
}


//////////////////////////////////////////////////////////////////
//  disableAllPeripherals()
//
//  To achieve minimum current consumption during sleep, it's best to
//  disable everything that might draw current during sleep.
//  This function disables everything except the RTC-PIT and 32K
//  internal low power oscillator.  This function does not disable
//  the counter used by the Arduino framework to implement millis(),
//  although the clock that drives that counter is suspended during sleep.
//
void io_gpio_disable(void) {
  PORTA.DIRCLR = PIN0_bm; //  set port A0 to input
  PORTA.DIRCLR = PIN1_bm; //  set port A1 to input
  PORTA.DIRCLR = PIN2_bm; //  set port A2 to input
  PORTA.DIRCLR = PIN3_bm; //  set port A3 to input
  PORTA.DIRCLR = PIN6_bm; //  set port A4 to input
  PORTA.DIRCLR = PIN7_bm; //  set port A5 to input        
    
  PORTA.PIN0CTRL = PORT_ISC_INPUT_DISABLE_gc; // disable input buffers
  PORTA.PIN1CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTA.PIN2CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTA.PIN3CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTA.PIN6CTRL = PORT_ISC_INPUT_DISABLE_gc;
  PORTA.PIN7CTRL = PORT_ISC_INPUT_DISABLE_gc;
  
  power_all_disable();
  //USART0.CTRLB &= ~USART_RXEN_bm & ~USART_TXEN_bm; // disable USART
}

#define PA3_INTERRUPT PORTA.INTFLAGS & PIN3_bm
#define PA3_CLEAR_INTERRUPT_FLAG PORTA.INTFLAGS &= PIN3_bm

ISR(PORTA_PORT_vect)
{
  if(PA3_INTERRUPT)
  {
    //pb2Ioc = 1;
    PA3_CLEAR_INTERRUPT_FLAG;
  }
}


//////////////////////////////////////////////////////////////////
//  LED set/clear/toggle functions
//
void ledOn(void) {PORTA.OUTSET = PIN_PWR_OFF_BM;} // turn on active high LED on PA1
void ledOff(void) {PORTA.OUTCLR = PIN_PWR_OFF_BM;} // turn off active high LED on PA1
void ledToggle(void) {PORTA.OUTTGL = PIN_PWR_OFF_BM;} // toggle active high LED on PA1

//////////////////////////////////////////////////////////////////
//  Power on/off
//
void pwr_off(void) {PORTA.OUTSET = PIN_PWR_OFF_BM;} 
void pwr_on(void)  {PORTA.OUTCLR = PIN_PWR_OFF_BM;} 


//////////////////////////////////////////////////////////////////
//  Diagnostic pin set/clear/toggle functions
//
void diagnosticPinHigh(void) {PORTA.OUTSET = PIN2_bm;} // port output high
void diagnosticPinLow(void) {PORTA.OUTCLR = PIN2_bm;} // port output low
void diagnosticPinToggle(void) {PORTA.OUTTGL = PIN2_bm;} // port output toggle


