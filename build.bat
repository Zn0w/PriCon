@echo off
g++ -c src/main.cpp -o obj/main.o
g++ obj/main.o -o bin/pricon -std=c++11 -static-libgcc -static-libstdc++
@pause