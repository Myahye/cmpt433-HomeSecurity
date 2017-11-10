#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "door_sensor.h"

void testDoorSensor();

int main()
{
  testDoorSensor();
}

void testDoorSensor()
{
  Door_init();
  sleep(8);
  Door_unInit();
}
