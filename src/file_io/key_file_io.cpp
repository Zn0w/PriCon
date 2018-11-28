#include "key_file_io.h"

std::vector<Symbol> readKey(const char* key_path)
{
	std::vector<Symbol> symbols;
	symbols.reserve(CHAR_AMOUNT); // For now it's 26 (the amount of letters in the alpabet), but it will be bigger because of numbers, special symbols, etc
	
	std::string line;
  	std::ifstream file_reader(key_path);
  	if (file_reader.is_open())
  	{
    	/*for (int i = 0; i < 26; i++)
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
    	}*/

		int i = 0;
		
		// Get Uppercase letters, lowercase letters, numbers
		for (int i = 0; i < CHAR_AMOUNT; i++)
		{
			if (getline(file_reader,line))
			{
				Symbol symbol;

				// Get numbers in char type
				if (i < 10)
					symbol.character = (char) (i + 48);
				// Get uppercase letters
				else if (i < 36)
					symbol.character = (char) ((i - 10) + 65);
				// Get lowercase letters
				else if (i < 62)
					symbol.character = (char) ((i - 36) + 97);
				// Get SPACE
				else
					symbol.character = (char) ((i - 62) + 32);

				symbol.code = line;

				
				symbols.push_back(symbol);
			}
			else
			{
				std::cout << "Invalid key file." << std::endl;
				break;
			}
		}

    	file_reader.close();
  	}
  	else 
	  std::cout << "Unable to open file" << std::endl;
	
	return symbols;
}

void createKey(const char* key_path, std::string key)
{
	std::ofstream key_file;
	key_file.open (key_path);
	
	if (!key_file.is_open())
	{
		std::cout << "Failed to open a key file at " << key_path << std::endl;
		return;
	}

	key_file << key;
	key_file.close();

	std::cout << "Successfully created a key file at " << key_path << std::endl;
}