#include <Arduino.h>
#include "main.h"
#include "io.h"
#include "eep.h"

#define  WD_DEFAULT_INTERVAL    10000
#define  WD_POWER_OFF_DURATION  2000

typedef struct
{
  uint32_t timeout_at_ms;
  uint32_t power_on_at_ms;
  uint16_t forced_reset_ms;
  uint8_t  state;
  uint8_t  last_clr_value;
} ed_st;

extern main_data_st main_data;
extern restarts_st restarts;

ed_st ed;

void edog_clear()
{
  ed.timeout_at_ms = millis() + main_data.wd_interval_ms;
}

void edog_force_reset(uint16_t reset_duration)
{
  ed.forced_reset_ms = reset_duration;
}

void edog_initialize(void)
{
    ed.state = 0;
    ed.timeout_at_ms = millis() + WD_DEFAULT_INTERVAL;
    ed.forced_reset_ms = 0;
    ed.power_on_at_ms = 0;
    ed.last_clr_value = 0;
}

void edog_state_machine(void)
{
    uint8_t clr_input = io_get_clr_input();
    if (ed.last_clr_value != clr_input )
    {
        ed.timeout_at_ms = millis() + main_data.wd_interval_ms;
        ed.last_clr_value = clr_input;
    }

    switch(ed.state)
    {
      case 0:
          ed.state = 10;
          break;
      case 10:
          if (main_data.wd_is_active > 0) ed.state = 100;
          break;  
      case 100:  // WD is active
        if (millis() > ed.timeout_at_ms)
        {
            if (!io_is_wake_up())
            {
                ed.state = 110;
                ed.power_on_at_ms = millis() + WD_POWER_OFF_DURATION;
                restarts.watchdog++;
                eep_req_save(EEPROM_RESTARTS);
                io_power_off();

            }
        }
        break;
      case 110:
          if ((millis() > ed.power_on_at_ms) || io_is_wake_up())
          {
            io_power_on();
            edog_clear();
            ed.state = 100;
          }
          break;
    }
    if (!main_data.wd_is_active) 
    {
      ed.state = 10;
      io_power_on();
    }   
}