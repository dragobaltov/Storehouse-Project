#include "Engine.h"
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <utility>

Engine::Engine() = default;

/*! Start the program and accept user input, which is parsed to a command.*/
void Engine::run()
{
	std::string input;

	while (m_status != Status::exit)
	{
		std::cout << "> ";
		std::getline(std::cin, input);
		parse_command(input);
	}
}

/*! Checks if there isn't already opened file. If not, opens the given file and invokes
 * the virtual function load.
 * If the file doesn't exists, it is created.*/
void Engine::open(const std::string & file_name)
{
	if (m_status == Status::open)
	{
		std::cout << "File " << m_current_file << " is already opened!\n";
		return;
	}

	std::fstream file;
	file.open(file_name, std::ios::in);

	if (!file)
	{
		std::cout << file_name << " does not exist! Creating " << file_name << " ...\n";
		file.open(file_name, std::ios::out);
	}
	else
	{
		load(file);
	}

	m_status = Status::open;
	m_current_file = file_name;

	std::cout << "Successfully opened " << m_current_file << '\n';
}

/*! Checks if the given file can be opened. If yes, invokes the virtual function save_data.*/
void Engine::save_as(const std::string & file_name) const
{
	std::ofstream out;
	out.open(file_name, std::ios::out);

	if (!out)
	{
		std::cout << "Couldn't open file " << file_name << '\n';
		return;
	}

	save_data(out);

	std::cout << "Successfully saved changes in " << file_name << '\n';
}

/*! Sets the status to closed and invokes the virtual function unload.*/
void Engine::close()
{
	m_status = Status::closed;
	unload();
	std::cout << "Successfully closed " << m_current_file << '\n';
}

/*! Exits the program after 1 second.*/
void Engine::exit()
{
	std::cout << "Exiting the program...";
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));

	m_status = Status::exit;
}

/*! Prints info about the basic commands.*/
void Engine::help() const
{
	std::cout << "The following commands are supported:\n";
	std::cout << "open <file> - opens and loads a file\n";
	std::cout << "close - closes currently opened file\n";
	std::cout << "save - saves the currently opened file\n";
	std::cout << "saveas <file> - saves the currently opened file in <file>\n";
	std::cout << "exit - exits the program\n";
}

/*! Parses user input to a command.*/
void Engine::parse_command(std::string & input)
{
	std::pair<std::string, std::string> tokens = split_in_two(input, ' ');
	std::string command = to_lower(tokens.first);

	while (!is_valid_command(command))
	{
		std::cout << "Invalid command! If you need help enter the 'help' command.\n" << "> ";
		std::getline(std::cin, input);
		tokens = split_in_two(input, ' ');
		command = to_lower(tokens.first);
	}

	execute_command(command, tokens.second);
}

//--------------------------------------------------------------

std::string to_lower(const std::string & text)
{
	std::string lower = "";

	for (char l : text)
	{
		if (l >= 'A' && l <= 'Z')
		{
			lower += (l + ('a' - 'A'));
		}
		else
		{
			lower += l;
		}
	}

	return lower;
}

std::pair<std::string, std::string> split_in_two(const std::string & input, char delimeter)
{
	size_t start = 0;

	while (input[start] == delimeter)
	{
		start++;
	}

	size_t delim_pos = input.find(delimeter, start);

	if (delim_pos == std::string::npos)
	{
		return { input, "" };
	}

	std::string first = input.substr(start, delim_pos - start);

	while (input[delim_pos] == delimeter)
	{
		delim_pos++;
	}

	return { first, input.substr(delim_pos) };
}

//--------------------------------------------------------------