#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <ctime>


#ifdef _WIN32

#include <windows.h>
#define ON_WINDOWS

#endif


#include "operation.h"

#include "file_io/key_file_io.h"

void copyToClipboard(char* text, int text_length);

int main(int argc, char** argv)
{
	// Startup:
	//			pricon e key.txt "Hello :)"			- encrypt using key.txt a message "Hello :)"
	//			pricon d key.txt ar45,Gtt7,co09.	- decrypt using key.txt an encrypted message ar45,Gtt7,co09.
	//			pricon c							- randomly generate a key file in the current folder named "key.txt"
	//			pricon c keys/mykey.txt				- randomly generate a key file in the "keys" folder named "mykey.txt"
	//			pricon h							- show the list of all the available commands
	
	Operation operation;
	std::string key;
	std::string text;
	
	if (argc > 1)
	{
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
			std::cout << "No such kind of command. ($ pricon h - to show the list of commands)" << std::endl;
			return 1;
		}
	}

	else
		std::cout << "Please, provide at least one argument. ($ pricon h - to show the list of commands)" << std::endl;


	// Handle operations

	if (operation == ENCRYPT)
	{
		std::vector<Symbol> symbols;
		symbols = readKey(key.c_str());
		if (symbols.size() < 62)
			return 1;

		std::string encrypted_text = "";

		for (int i = 0; i < text.length(); i++)
		{
			for (int j = 0; j < symbols.size(); j++)
			{
				if (symbols.at(j).character == text.at(i))
				{
					encrypted_text += symbols.at(j).code + " ";
					break;
				}
			}
		}

		encrypted_text += " "; // Needed for future decryption

		// TODO: call this function only if on windows (at least for now)
		copyToClipboard((char*) encrypted_text.c_str(), encrypted_text.length());

		std::cout << "Encrypted text: " << encrypted_text << std::endl;
	}

	else if (operation == DECRYPT)
	{
		std::vector<Symbol> symbols;
		symbols = readKey(key.c_str());
		if (symbols.size() < CHAR_AMOUNT)
			return 1;

		std::string decrypted_text = "";
		std::string encrypted_char = "";

		for (int i = 0; i < text.length(); i++)
		{
			if (text.at(i) == ' ')
			{
				for (int j = 0; j < symbols.size(); j++)
				{
					if (symbols.at(j).code == encrypted_char)
					{
						decrypted_text += symbols.at(j).character;
						break;
					}
				}

				encrypted_char = "";
			}
			else
				encrypted_char += text.at(i);
		}

		std::cout << "Decrypted text: " << decrypted_text << std::endl;
	}

	else if (operation == CREATE_KEY)
	{
		std::string key_content;
		
		srand(time(0));
		int length_of_code = rand() % (10 - 4 + 1) + 4;
		for (int i = 0; i < CHAR_AMOUNT; i++)
		{
			for (int j = 0; j < length_of_code; j++)
				key_content += (char) (rand() % (126 - 35 + 1) + 35);
			
			if (i != (CHAR_AMOUNT - 1))
				key_content += "\n";
		}

		createKey(key.c_str(), key_content);
	}

	else if (operation == HELP)
	{
		std::cout << "pricon e key.txt 'Hello :)'           - encrypt using key.txt a message 'Hello :)'" << std::endl;
		std::cout << "pricon d key.txt 'ar45 Gtt7 co09 '    - decrypt using key.txt an encrypted message ar45,Gtt7,co09." << std::endl;
		std::cout << "pricon c                              - randomly generate a key file in the current folder named 'key.txt'" << std::endl;
		std::cout << "pricon c keys/mykey.txt               - randomly generate a key file in the 'keys' folder named 'mykey.txt'" << std::endl;
		std::cout << "pricon h                              - show the list of all the available commands" << std::endl;
	}
	
	return 0;
}

void copyToClipboard(char* text, int text_length)
{
   	// Auto copy feature is fro now implemented for windows only
	#ifdef ON_WINDOWS
	{
	
		if (!OpenClipboard(NULL))
   		{
		   	std::cout << "Failed to copy text to the clipboard. (OpenClipboard - returned false)" << std::endl;
		   	return;
   		}

   		if (!EmptyClipboard())
   		{
		   	std::cout << "Failed to copy text to the clipboard. (EmptyClipboard - returned false)" << std::endl;
		   	return;
   		}

   		HGLOBAL clipboard_data = GlobalAlloc(GMEM_DDESHARE, text_length + 1);
   		strcpy((char*) clipboard_data, text);
		if (SetClipboardData(CF_TEXT, clipboard_data))
			CloseClipboard();
		else
		{
			CloseClipboard();
			GlobalFree(clipboard_data);
			std::cout << "Failed to copy text to the clipboard. (SetClipboardData - failed)" << std::endl;
		}
	}
	
	#else
		std::cout << "Now on windows." << std::endl;

	#endif

}