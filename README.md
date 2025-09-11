# Carrascone
Replica of board game Carcassonne

Carcassone program for local multiplayer, to run in UNIX systems.

## Libraries used

+ C++11
+ [SFML](https://www.sfml-dev.org/) graphic library
+ [catch](https://github.com/catchorg/Catch2) testing framework
+ [boost](https://www.boost.org/library/latest/program_options/) program options

## Future expansions

### Game mechanics

+ Priest
+ River
+ Extra tiles

### Misc

+ Compatibility and install instructions for Windows and MacOX
+ **Network multiplayer with Internet socket communications or a dedicated Server**
+ AI player

## Compilation

### Linux

+ Clone this repository
+ Install the dependencies, `sfml`, `boost`, `cmake` and `gcc`, this depends on your system.

```sh
$ cmake -S . -B build -G 'Unix Makefiles'
$ cmake --build build
```

Launch with

```sh
$ ./build/bin/carrascone
```
and use `--help` to view available options.

## Code formatting

```sh
$ clang-format --version
clang-format version 20.1.8

clang-format -i --verbose --style=file:.clang-format ./**/*[^catch].hpp ./**/*.cpp
```

## Licence

GNU General Public License 3

This was made as a learning exercise, no commercial use intended. Buy the [Carcassonne app](https://play.google.com/store/apps/details?id=com.asmodeedigital.carcassonne&hl=pt) (link visited on 23/08/2018).
