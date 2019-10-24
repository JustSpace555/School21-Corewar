#!/bin/bash

if ! [ -d /Users/$(whoami)/Library/Frameworks ]
then
	echo "Make folder Frameworks";
	mkdir /Users/$(whoami)/Library/Frameworks;
fi;
if ! [ -e /Users/$(whoami)/Library/Frameworks/SDL2.framework ]
then
	echo "Putting SDL2.framework in Frameworks";
	cp -R $(pwd)/../Vizualizator/SDL2.framework /Users/$(whoami)/Library/Frameworks/;
fi;
if ! [ -e /Users/$(whoami)/Library/Frameworks/SDL2_ttf.framework ]
then
	echo "Putting SDL2_ttf.framework in Frameworks";
	cp -R $(pwd)/../Vizualizator/SDL2_ttf.framework /Users/$(whoami)/Library/Frameworks/;
fi;
