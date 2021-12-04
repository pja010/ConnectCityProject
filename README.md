# CSCI 311 Project 2 - Connecting a City

Jeffrey Cai, Emily Pecoraro, Per Astrom

## Project files
connect_city.c <br />
optimized_connect_city.c <br />
Makefile cal.txt <br />
NA.txt <br />
OL.txt <br />
TG.txt <br />
SF.txt <br />

## Description
Two different implementations of algorithm that finds the smallest graph connecting all roads in a city. Their performance can be tested on five different files, each describing a city's network of roads. Roads are represented by edges, their length by a weight, and their points of intersection by nodes.  

## How to run
Compile project in bash (or other terminal):
```bash
$make
``` 
Run the programs: 
```bash
./connect_city 'Inputfile' 'Outputfile' 

./optimized_connect_city 'Inputfile' 'Outputfile'
```
The result of the program will be stored in the specified outputfile (ex. output.txt).

