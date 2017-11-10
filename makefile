all:
	arm-linux-gnueabihf-gcc -Wall -g -std=c99 -D _POSIX_C_SOURCE=200809L -pthread -Werror door_sensor.c -o project
	mv project $(HOME)/cmpt433/public/myApps/

