# Carrascone
Replica of board game Carcassonne

Carcassone program for local multiplayer, to run in UNIX systems.

## Technologies used

+ C++11
+ [SFML](https://www.sfml-dev.org/) graphic library
+ [catch](https://github.com/catchorg/Catch2) testing framework

## Future expansions

### Game mechanics

+ Priest
+ River
+ Extra tiles

### Misc

+ Compatibility and install instructions for Windows and MacOX
+ **Network multiplayer with Internet socket communications or a dedicated Server**
+ AI player

## Install

### Linux

+ Clone this repository
```
sudo apt-get install libsfml-dev
sudo apt-get install libboost-all-dev
cd carrascone/src
make
```

+ Launch with
```
./main
```
and use `--help` to view available options.


## Licence

GNU General Public License 3

This was made as a learning exercise, no commercial use intended. Buy the [Carcassonne app](https://play.google.com/store/apps/details?id=com.asmodeedigital.carcassonne&hl=pt) (link visited on 23/08/2018).
