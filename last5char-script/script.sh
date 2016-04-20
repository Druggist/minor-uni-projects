#!/bin/bash

if [ -z "$1" ]; then
	echo "No file was given. Exiting."
	exit 1
fi

if [ -z "$2" ]; then
	CHAR=5
else
	CHAR=$2
fi

if [ ! -f $1 ]; then
   echo "File $1 does not exist."
   exit 1
fi

TEXT="$(tail -2 $1 | head -1)"

echo ${TEXT:0:$CHAR}