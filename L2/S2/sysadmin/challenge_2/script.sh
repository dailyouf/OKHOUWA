#!/bin/bash

i=0

while [ $i -lt 1048576 ] 
do 	
	echo -n 0 >>./sandbox/zeros.bin
	i=$((i + 1))
	
done
