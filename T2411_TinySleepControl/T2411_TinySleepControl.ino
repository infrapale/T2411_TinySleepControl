/*******************************************************************************

T2411 ATtiny412 Sleep Control
- I2C slave interface
- Cut main MCU and peripheral power on timeout or direct command
- EEPROM functions
- Low power to be implemented
-------------------------------------------------------------------------------
https://github.com/infrapale/T2411_TinySleepControl.git
Sleep function based on the : 
  https://github.com/microPaul/ATtiny412-Sleeping-Lighthouse

https://wiki-content.arduino.cc/en/Tutorial/LibraryExamples/MasterWriter
https://inductive-kickback.com/2019/04/creating-an-i2c-slave-interface-for-a-sensor-or-peripheral/

See python scripts for usage

*******************************************************************************/

#include "main.h"
#include <Wire.h>
#include <avr/sleep.h>
#include "cmd.h"
#include "io.h"
#include "buff.h"
#include "eep.h"
#include "edog.h"
#include <EEPROM.h>
#include "sleep.h"

uint8_t RxByte;
uint8_t tbuff[] = {0x56,0x45,0x34,0x23,0x12,0x01};

main_data_st main_data;
volatile i2c_buff_st i2c_buff; 
restarts_st restarts;

//extern cmd_data_st cmd_data[];

uint32_t next_task_run_ms = 0;




void setup() {
  sleep_setup();
 
}


///////////////////////////////////////////////////////////
// loop
//
// This is the Super Loop.  In the Arduino world this is really a function (not a loop)
// that is called repeatedly by the Arduino executive.  As such, any local variables
// will be lost each time when the function concludes.  If you want to retain local
// variables then wrap the loop code in a while(1) statement.
//
void loop() {
  while(1) {
    // this loop blinks the LED three times then a 3 second gap
    // the MCU will be in POWER DOWN sleep mode when the LED is off
    pwr_on(); 
    delay(5000);
    pwr_off();
    sleepNCycles(8); // cycles are about 500ms each
    
    pwr_on(); 
    delay(10000);
    pwr_off(); 
    sleepNCycles(8); // cycles are about 500ms each
    
    
  }
}


/*
void i2c_receive_event(int rx_bytes)
{
  uint8_t msg_len = 0;
  i2c_buff.rx_indx = 0;

  for (int i = 0; i < rx_bytes; i++)
  {
    i2c_buff.rx[i2c_buff.rx_indx] = Wire.read();
    i2c_buff.rx_indx++; 

    if (i2c_buff.rx_indx >= I2C_RX_BUFF_SIZE) break;
  }
  msg_len = rx_bytes;
  for (uint8_t i=0; i < msg_len; i++) 
  {
    i2c_buff.cmd[i] = i2c_buff.rx[i];
  }
  i2c_buff.cmd_len = msg_len;       
  i2c_buff.rx_indx = 0;
}


void i2c_request_event()
{
   uint8_t cmd = i2c_buff.cmd[0];
   cmd_get_data(cmd);
   
   
}

 
void setup() {
  epp_initialize_data();
  main_data.wd_interval_ms = 5000;
  main_data.wd_is_active = 0;
  edog_initialize();
  next_task_run_ms = millis() + TICK_TIME;
  restarts.internal = EEPROM.read(1);
  restarts.internal++;
  EEPROM.write(1, restarts.internal);
  io_initialize();
  //io_blink_color_times(PIN_LED, restarts.internal, 2);
  Wire.begin(I2C_ADDR); // Initialize I2C (Slave Mode)
  Wire.onRequest(i2c_request_event);
  Wire.onReceive( i2c_receive_event );
}


void loop() {
  if (i2c_buff.cmd_len > 0) 
  {
    // io_blink_color_times(PIN_PWR_OFF , i2c_buff.cmd_len, 4);
    cmd_execute_cmd(i2c_buff.cmd[0]);
    i2c_buff.cmd_len = 0;
  }
  
  if(millis() > next_task_run_ms){
    next_task_run_ms = millis() + TICK_TIME;
    eep_time_machine();
    edog_state_machine();
  }

}
*/

