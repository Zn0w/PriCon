#include "key_file_io.h"

Symbol* readKey(const char* key_path)
{
	Symbol symbols[26];	// For now it's 26 (the amount of letters in the alpabet), but it will be bigger because of numbers, special symbols, etc
	
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
				
				if (CODE_SIZE - line.length())
					for (int j = 0; j < line.length(); j++)
						symbol.code[j] = line.at(j);
				else
					std::cout << "The code specified in key file is bigger then maximum allowed length." << std::endl;
				
				symbols[i] = symbol;
			}
			else
				std::cout << "Invalid key file." << std::endl;
    	}

    	file_reader.close();
  	}
  	else 
	  std::cout << "Unable to open file" << std::endl;
}

void createKey(const char* key_path)
{

}