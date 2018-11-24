#include "key_file_io.h"

std::vector<Symbol> readKey(const char* key_path)
{
	std::vector<Symbol> symbols;
	symbols.reserve(26); // For now it's 26 (the amount of letters in the alpabet), but it will be bigger because of numbers, special symbols, etc
	
	std::string line;
  	std::ifstream file_reader(key_path);
  	if (file_reader.is_open())
  	{
    	for (int i = 0; i < 26; i++)
    	{
			if (getline(file_reader,line))
			{
				Symbol symbol;
				symbol.character = (Character) i;
				symbol.code = line;
				
				symbols.push_back(symbol);
			}
			else
				std::cout << "Invalid key file." << std::endl;
    	}

    	file_reader.close();
  	}
  	else 
	  std::cout << "Unable to open file" << std::endl;
	
	return symbols;
}

void createKey(const char* key_path)
{

}