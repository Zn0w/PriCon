#pragma once

#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <vector>

#include "../symbol.h"

std::vector<Symbol> readKey(const char* key_path);

void createKey(const char* key_path);