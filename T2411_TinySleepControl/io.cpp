#include "Arduino.h"
#include "main.h"
#include "io.h"



  void io_initialize(void)
  {
    pinMode(PIN_EDOG_CLR, INPUT);
    pinMode(PIN_EDOG_WAKE, INPUT_PULLUP);
    pinMode(PIN_PWR_OFF_0, OUTPUT);
    digitalWrite(PIN_PWR_OFF_0, LOW);
  }

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

void io_goto_sleep(void)
{
    // cntrl.sleep_state = SLEEP_STATE_CLOSING;
}

void io_power_off(void)
{
    pinMode(PIN_PWR_OFF_0, OUTPUT);
    digitalWrite(PIN_PWR_OFF_0, LOW);
}

void io_power_on(void)
{
    pinMode(PIN_PWR_OFF_0, INPUT);
    // digitalWrite(PIN_PWR_OFF_0, HIGH);
}

uint8_t io_get_clr_input(void)
{
    return digitalRead(PIN_EDOG_CLR);
}

bool io_is_wake_up(void)
{
   return (digitalRead(PIN_EDOG_WAKE) == 0); 
}

