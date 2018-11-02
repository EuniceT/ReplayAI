#!/bin/bash
make -f Makefile || exit
make -f ../Wumpus_World_World_Generator/Makefile tournamentSet || exit
mv ../Wumpus_World_World_Generator/Worlds ./Worlds
