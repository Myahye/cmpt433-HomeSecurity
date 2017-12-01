#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include "keypad.h"

#define _10MS_IN_NS 10000000L
#define BUFFER_SIZE 512
#define NUM_GPIO 12
#define GPIO_BASE_DIR "/sys/class/gpio/"

static int run = 0;
static pthread_t keypad_id;
static const char *GPIO[] = {
  "36", "32", "86", "87", "10", "9", "8", "78", "76", "74", "72", "70"
};

static void *keypad_reader();

void Keypad_init()
{
  FILE *file;
  char buffer[BUFFER_SIZE] = "";

  // export GPIO pins
  for (int i = 0; i < NUM_GPIO; ++i) {
    file = fopen((GPIO_BASE_DIR "export"), "w");
    if (file == NULL)
      perror("Couldn't open GPIO export file!");
    fprintf(file, "%s", GPIO[i]);
    fclose(file);
  }

  // set directions as in
  for (int i = 0; i < NUM_GPIO; ++i) {
    strcpy(buffer, GPIO_BASE_DIR "gpio");
    strcat(buffer, GPIO[i]);
    strcat(buffer, "/direction");
    
    file = fopen(buffer, "w");
    if (file == NULL)
      perror("Couldn't export a GPIO pin!");
    fprintf(file, "%s", "in");
    fclose(file);
  }

  run = 1;
  pthread_create(&keypad_id, NULL, keypad_reader, NULL);
}

void Keypad_unInit()
{
  run = 0;
  pthread_join(keypad_id, NULL);

  FILE *file;

  // unexport GPIO pins
  for (int i = 0; i < NUM_GPIO; ++i) {
    file = fopen((GPIO_BASE_DIR "unexport"), "w");
    if (file == NULL)
      perror("Couldn't open GPIO unexport file!");
    fprintf(file, "%s", GPIO[i]);
    fclose(file);
  }  
}

static void *keypad_reader()
{
  struct timespec delay;
  delay.tv_sec = 0;
  delay.tv_nsec = _10MS_IN_NS;

  while (run) {
    nanosleep(&delay, NULL);
    printf("some reading here...\n");
  }

  return NULL;
}