# COMP8551-GameEngine
Major Project for COMP8551

## Setup
### Make
In order to run make you will need make for windows found here:</br>
http://gnuwin32.sourceforge.net/packages/make.htm </br>
Note: Just dl and install complete package and I'm unsure at moment if you need this with cygwin

## How To Run (Cygwin/MinGW)
### Running
Navigate to file that contains Makefile then:</br></br>
To build the game
```
make
```
To run the game
```
./engine.exe
```
### Debugging
If you notice it says something about glfw3 when compiling, change the -lglfw3 in the makefile to -lglfw3dll. I'm not sure why this is a thing.
</br></br>
If when trying to run it says it can't find glfw3.dll, just move the dll file in libs to the same folder as the Makefile. Again not sure why this is a thing.
