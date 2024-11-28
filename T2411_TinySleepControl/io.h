#ifndef __IO_H__
#define __IO_H__

/**********************************************************************
    IO Definitions and Functions
***********************************************************************
                ---------------------
                |                   |
    3.3-5V    --| (1) VDD   GND (8) |-- GND
                |                   |
    PWR_OFF   --| (2) PA6   PA3 (7) |-- EDOG_WAKE
                |                   |
    EDOG_CLR  --| (3) PA7   PA0 (6) |-- UPDI
                |                   |
    I2C SDA   --| (4) PA1   PA2 (5) |-- I2C SCL
                |                   |
                 ---------------------
                                               
***********************************************************************
PWR_OFF is connected to the Pico 3V3_EN. This pin has a 100k pullup
resistor. The Pico internal supply will shut down when pulling down 
then PWR_OFF pin.

EDOG_CLR is an input with internal pullup. The main MCU (Pico) must toggle
this input with a interval less than the watchdog timeout defined.

EDOG_WAKE is an input with internal pullup. When pulled down we power on
the main MCU by disconnecting the PWR_OFF pin.

I2C_SCL and I2C_SDA are acting as a slave when communicating with the 
main MCU

UPDI is used for programming the ATTiny412
**********************************************************************/


#define PA1 (2u)
#define PA2 (3u)
#define PA3 (4u)
#define PA6 (0u)
#define PA7 (1u)

#define PIN_I2C_SDA         PA1
#define PIN_I2C_SCL         PA2

#define PIN_EDOG_WAKE       PA3
#define PIN_PWR_OFF_0       PA6
#define PIN_EDOG_CLR        PA7


void io_initialize(void);

void io_blink_color_times(uint8_t pin, uint8_t n, uint16_t us);

void io_goto_sleep(void);

void io_power_off(void);

void io_power_on(void);


uint8_t io_get_clr_input(void);

bool io_is_wake_up(void);


#endif