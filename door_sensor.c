#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#include "door_sensor.h"

#define _250MS_IN_NS 250000000L
#define BUFFER_SIZE 256
#define GPIO_EXPORT "/sys/class/gpio/export"
#define GPIO_UNEXPORT "/sys/class/gpio/unexport"
#define GPIO_OUT "/sys/class/gpio/gpio67/value"
#define GPIO_OUT_DIR "/sys/class/gpio/gpio67/direction"
#define GPIO_IN "/sys/class/gpio/gpio68/value"
#define GPIO_IN_DIR "/sys/class/gpio/gpio68/direction"

static int run = 0;
static pthread_t door_id;

void *doorReader();
void getVal(int* value);

void Door_init()
{
  FILE *file = fopen(GPIO_EXPORT, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO export file!");
    return;
  }
  fprintf(file, "%s", "67");
  fclose(file);

  file = fopen(GPIO_EXPORT, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO export file!");
    return;
  }
  fprintf(file, "%s", "68");
  fclose(file);

  file = fopen(GPIO_OUT_DIR, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO 67 dir file!");
    return;
  }
  fprintf(file, "%s", "out");
  fclose(file);

  file = fopen(GPIO_IN_DIR, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO 68 dir file!");
    return;
  }
  fprintf(file, "%s", "in");
  fclose(file);

  run = 1;
  pthread_create(&door_id, NULL, doorReader, NULL);
}

void Door_unInit()
{
  run = 0;
  pthread_join(door_id, NULL);

  FILE *file = fopen(GPIO_UNEXPORT, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO unexport file!");
    return;
  }
  fprintf(file, "%s", "67");
  fclose(file);

  file = fopen(GPIO_UNEXPORT, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO unexport file!");
    return;
  }
  fprintf(file, "%s", "68");
  fclose(file);
}

void *doorReader()
{
  struct timespec delay;
  delay.tv_sec = 0;
  delay.tv_nsec = _250MS_IN_NS;
  int value = 0;

  while (run) {
    nanosleep(&delay, NULL);
    getVal(&value);
    
    if (value == 0)
      printf("DOOR: OPEN!\n");
    else
      printf("DOOR: CLOSED!\n");
    
  }

  return NULL;
}

void getVal(int *value)
{
  FILE *file = fopen(GPIO_OUT, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO value file!");
    return;
  }
  fprintf(file, "%s", "1");
  fclose(file);

  file = fopen(GPIO_IN, "r");
  if (file == NULL) {
    perror("Couldn't open GPIO value file!");
    return;
  }

  char buffer[BUFFER_SIZE];
  fgets(buffer, BUFFER_SIZE, file);
  fclose(file);

  if (buffer[0] == '0')
    *value = 1;
  else
    *value = 0;

  file = fopen(GPIO_OUT, "w");
  if (file == NULL) {
    perror("Couldn't open GPIO value file!");
    return;
  }
  fprintf(file, "%s", "0");
  fclose(file);
  
}
