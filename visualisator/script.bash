#!/bin/bash

if ! [ -d /Library/Frameworks ]
then
	echo "Make folder Frameworks";
	mkdir /Library/ Frameworks;
fi;
if ! [ -e /Library/Frameworks/SDL2.framework ]
then
	echo "Putting SDL2.framework in /Library/Frameworks";
	cp -R SDL2.framework /Library/Frameworks/;
fi;
if ! [ -e /Library/Frameworks/SDL2_ttf.framework ]
then
	echo "Putting SDL2_ttf.framework in /Library/Frameworks";
	cp -R SDL2_ttf.framework /Library/Frameworks/;
fi;
