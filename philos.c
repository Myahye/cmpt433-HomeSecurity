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
  sleep(10);
  Keypad_unInit();
}

void testDoorSensor()
{
  Door_init();
  sleep(8);
  Door_unInit();
}
