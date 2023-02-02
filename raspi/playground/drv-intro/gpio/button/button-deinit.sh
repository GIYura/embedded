#!/bin/bash

FILE=$(pwd)/.config

if [ ! -f $FILE ]; then
	echo ".config file not found"
	exit
fi

source $FILE

if [ -e $PATH/gpio$PIN ]; then
	echo $PIN > $PATH/unexport
	echo "Button deinit"
	exit
fi
	echo "Button deinit failed"
	exit
