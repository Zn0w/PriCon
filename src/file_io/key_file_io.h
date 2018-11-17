#pragma once

#include <fstream>
#include <vector>
#include <string>
#include <iostream>

#include <../symbol.h>

std::vector<Symbol> readKey(const char* key_path);

void createKey(const char* key_path);