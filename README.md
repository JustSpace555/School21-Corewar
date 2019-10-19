# Corewar
## About
> Core War is a 1984 programming game created by D. G. Jones and A. K. Dewdney in which
> two or more battle programs (called "warriors") compete for control of a virtual computer.
> These battle programs are written in an abstract assembly language called Redcode.

Project Structure
This project consists of five parts:

+ Champion
+ Assembler
+ Virtual Machine
+ Visualizer (Bonus)
Project has one developed champion: squash.s It is located at the [Champion directory][Champ_dir].
Also you can find in the folder [vm_champs][vm_champs_dir] both standard warriors and those who participated
in official competitions in 2016, [2017][2017_champ] and [2018][2018_champ] years

[Champ_dir]:https://github.com/JustSpace555/School21-Corewar/tree/master/Champion
[vm_champs_dir]:https://github.com/JustSpace555/School21-Corewar/tree/master/vm_champs
[2017_champ]:https://www.youtube.com/watch?v=A8DPfQL3uO0
[2018_champ]:https://www.youtube.com/watch?v=R-OkYyzp-DI

## How to clone
This repository includes submodule. So if you want to clone it, you can use the following command:

	`git clone --recurse-submodules <repository url>`

## Installation
Clone repository and then go into the created directory and run the following command:

	`make`

## Usage
### `asm`
	Usage: ./asm [-m] <file.s> [<files.s> ...]
		<file.s>	: warrior's file
		[-m]		: flag for multiple files input

### `corewar`
	Usage: ./corewar [-a] [-dump N] [-vi] [-v N] [-n N] <champion.cor> <...>
	-a		: Print output from "aff"
	-dump N		: Dumps memory after N cycles then exits
	-dumpc N	: Dumps memory in color mode after N cycles then exits
	-n N		: set the champion number
	-vi		: visual mode
	-v N		: verbose
			- 1  :	Show opearions information
			- 2  :	Show cycles information
			- 3  :	Show lives information
			- 4  :	Show deaths information
			- 5  :	Show PC movement information
			- 30 :	Show all information

## How it looks like
If you want to look how output information looks like, you can find screenshots in [Readme_files][RD_folder] folder

[RD_folder]:https://github.com/JustSpace555/School21-Corewar/tree/master/Readme_files

## Vizualizer
SDL2 Realisation:
![Corewar_demo_SDL2](https://github.com/JustSpace555/School21-Corewar/blob/master/Readme_files/Corewar_demo.gif)

If you want to change resolution of a vizualize window, find file `vizualizator.h` in `Vizualizator` folder
and change the parameters `SCREEN_WIDTH` and `SCREEN_HEIGHT` to the ones you need. After that you will need to recompile project.
Run command `make new` in project's root folder or just `make` if you haven't done it yet.

![resolution](https://github.com/JustSpace555/School21-Corewar/blob/master/Readme_files/resolution.png)

## Team:
+ [Temofy](https://github.com/temofy)
+ [Acrooks](https://github.com/Cybersky21)
+ [Me](https://github.com/JustSpace555) :)
+ And another person who doesn't use github :(
	
