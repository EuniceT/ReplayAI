#!bin/bash
make -f Makefile || exit
temp="Worlds$1"
./bin/Wumpus_World -f $temp
