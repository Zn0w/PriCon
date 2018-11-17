#include "key_file_io.h"

std::vector<Symbol> readKey(const char* key_path)
{
	std::string line;
  	std::ifstream file_reader(key_path);
  	if (file_reader.is_open())
  	{
    	while (getline(file_reader,line))
    	{
      		std::cout << line << std::endl;
    	}

    	file_reader.close();
  	}
  	else 
	  std::cout << "Unable to open file" << std::endl;
}

void createKey(const char* key_path)
{

}