#!/bin/bash

FILE=$(pwd)/.config

if [ ! -f $FILE ]; then
	echo ".config file not found"
	exit
fi

source $FILE

if [ ! -e $PATH/gpio$PIN ]; then
	echo $PIN > $PATH/export
	echo "in" > $PATH/gpio$PIN/direction
	echo $EDGE > $PATH/gpio$PIN/edge
	echo "Button init"
	exit
fi
	echo "Button init failed"
	exit
