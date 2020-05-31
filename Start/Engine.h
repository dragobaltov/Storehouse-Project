#pragma once
#include <string>

const std::string INVALID_ACTION_MSG = "Invalid action! There is no opened file.\n";
const std::string INVALID_FILE_NAME_MSG = "File name cannot be empty string!\n";

std::string to_lower(const std::string&);
std::pair<std::string, std::string> split_in_two(const std::string&, char);

/*! Enum class that represents if there is an open file or if the user has given command to exit the program.*/
enum class Status
{
	open,
	closed,
	exit
};

/*! \brief Handles user input and executes basic commands(open, close, save, save as, help, exit)
 *
 * Contains a string, in which is stored the name of the currently opened file(or the last one that was open) and
 * an object of type enum Status, which can accept 3 different values - open, closed and exit.\n
 * open status: means there is a currently opened file and all commands can be executed\n
 * closed status: means there is no opened file; the only functions that can be executed are open, help and exit\n
 * exit status: means the user has given command exit and wants to stop the program*/
class Engine
{
public:
	Engine();
	void run();
protected:
	std::string m_current_file{ "" };
	Status m_status{ Status::closed };

	void open(const std::string&);
	void close();
	virtual void save_as(const std::string&) const;
	virtual void help() const;
	void exit();

	void parse_command(std::string&);
	virtual void load(std::istream&) = 0;
	virtual void unload() = 0;
	virtual void save_data(std::ostream&) const = 0;
	virtual void execute_command(const std::string&, const std::string&) = 0;
	virtual bool is_valid_command(const std::string&) const = 0;
};


