#!/bin/bash

if ! [ -d /Users/$(whoami)/Library/Frameworks ]
then
	echo "Make folder Frameworks";
	mkdir /Users/$(whoami)/Library/Frameworks;
fi;
if ! [ -e /Users/$(whoami)/Library/Frameworks/SDL2.framework ]
then
	echo "Putting SDL2.framework in ~/Library/Frameworks";
	cp -R $(pwd)/../Visualisator/SDL2.framework /Users/$(whoami)/Library/Frameworks/;
fi;
if ! [ -e /Users/$(whoami)/Library/Frameworks/SDL2_ttf.framework ]
then
	echo "Putting SDL2_ttf.framework in ~/Library/Frameworks";
	cp -R $(pwd)/../Visualisator/SDL2_ttf.framework /Users/$(whoami)/Library/Frameworks/;
fi;
