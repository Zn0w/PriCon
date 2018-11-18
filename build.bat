@echo off
g++ -c src/file_io/key_file_io.cpp -o obj/key_file_io.o
g++ -c src/main.cpp -o obj/main.o
g++ obj/main.o obj/key_file_io.o -o bin/pricon -std=c++11 -static-libgcc -static-libstdc++
@pause