#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "door_sensor.h"
#include "keypad.h"

void testDoorSensor();
void testKeypad();

int main()
{
  //testDoorSensor();
  testKeypad();
}

void testKeypad()
{
  Keypad_init();
  
  char new_code[6] = "123456";
  code_t code;
  Keypad_setCode(6, new_code);
  code = Keypad_getCode();
  printf("NEW CODE = %s\n", code.code);

  sleep(6);
  
  Keypad_unInit();
}

void testDoorSensor()
{
  Door_init();
  sleep(8);
  Door_unInit();
}
