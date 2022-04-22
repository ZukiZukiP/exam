#!/bin/bash

echo 'Working directory name : ' 
read dirname

if [ -n "$dirname" ]  
then
	if [ -d "$dirname" ]
	then
		if [ -x "$dirname" ]
		then
			cd $dirname
				for i in *
				do
				changename=`echo $i | tr '[a-z][A-Z]' '[A-Z][a-z]'`
                       		mv $i $changename
				done	
				
		fi
	else
		echo "IS NOT DIRECTORY"
	fi

else
	dirname=pwd
		for i in *
		do
			changename=`echo $i | tr '[a-z][A-Z]' '[A-Z][a-z]'`
			mv $i $changename
		done
fi
