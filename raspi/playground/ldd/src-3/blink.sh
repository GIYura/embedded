#!/bin/bash

# path for gpio
GPIO=/dev/my-gpio-driver

# names of states
ON="1"
OFF="0"

ledState()
{
	echo $2 > $1
}

if [ ! -f "$GPIO" ]; 
then	
{	
	echo "Device file does not exit"
	exit 
}
fi
 
echo "LED is Blinking ... Press 'CNTL+C' to terminate"
while [ 1 ]
do
	ledState $GPIO $ON
	sleep 1

	ledState $GPIO $OFF
	sleep 1
done

