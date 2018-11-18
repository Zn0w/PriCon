#include <iostream>
#include <string>
#include <string.h>

#include "operation.h"

#include "file_io/key_file_io.h"

int main(int argc, char** argv)
{
	// Startup:
	//			pricon e key.txt "Hello :)"			- encrypt using key.txt a message "Hello :)"
	//			pricon d key.txt ar45,Gtt7,co09.	- decrypt using key.txt an encrypted message ar45,Gtt7,co09.
	//			pricon c							- randomly generate a key file in the current folder named "key.txt"
	//			pricon c keys/mykey.txt				- randomly generate a key file in the "keys" folder named "mykey.txt"
	//			pricon h							- show the list of all the available commands
	
	std::cout << argc << std::endl;//fg
	
	Operation operation;
	//char* key;
	//char* text;
	std::string key;
	std::string text;
	
	if (argc > 1)
	{
		std::cout << argv[1] << std::endl;
		
		if ((!strcmp(argv[1], "e") || !strcmp(argv[1], "d")) && argc == 4)
		{
			if (!strcmp(argv[1], "e"))
				operation = ENCRYPT;
			else
				operation = DECRYPT;
			key = argv[2];
			text = argv[3];
		}

		else if (!strcmp(argv[1], "c") && argc == 2)
		{
			operation = CREATE_KEY;
			key = "key.txt";
		}

		else if (!strcmp(argv[1], "c") && argc == 3)
		{
			operation = CREATE_KEY;
			key = argv[2];
		}

		else if (!strcmp(argv[1], "h"))
		{
			operation = HELP;
		}

		else
		{
			std::cout << "No such kind of command." << std::endl;
			return 1;
		}
	}

	else
		std::cout << "Please, provide at least one argument. ($ pricon h - to show the list of commands)" << std::endl;


	//char* operation_str;
	std::string operation_str;
	if (operation == ENCRYPT)
		operation_str = "encrypt";
	else if (operation == DECRYPT)
		operation_str = "encrypt";
	else if (operation == CREATE_KEY)
		operation_str = "encrypt";
	else if (operation == HELP)
		operation_str = "help";
	else
		operation_str = "null";

	std::cout << "Operation: " << operation_str << std::endl;
	std::cout << "Key:       " << key << std::endl;
	std::cout << "Text:      " << text << std::endl;

	// Handle operations

	if (operation == ENCRYPT)
	{
		Symbol* symbols = readKey(key.c_str());

		for (int i = 0; i < 26; i++)
			std::cout << *(symbols + i)->code << std::endl;
	}
	
	return 0;
}