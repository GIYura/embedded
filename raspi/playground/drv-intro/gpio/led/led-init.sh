#!/bin/bash

FILE=$(pwd)/.led-config

if [ ! -f $FILE ]; then
	echo ".config file not found"
	exit
fi

source $FILE

if [ ! -e $LED_PATH/gpio$LED_PIN ]; then
	echo $LED_PIN > $LED_PATH/export
	echo "out" > $LED_PATH/gpio$LED_PIN/direction
	echo "LED init"
	exit
fi
	echo "LED init failed"
	exit

