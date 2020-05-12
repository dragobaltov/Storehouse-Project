#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <fstream>
#include <utility>

const std::string INVALID_ACTION_MSG = "Invalid action! There is no opened file.\n";

std::string to_lower(const std::string&);
std::pair<std::string, std::string> split_in_two(const std::string&, char);

enum class Status
{
	open,
	closed,
	exit
};

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
	virtual void save_data(std::ostream&) const = 0;
	virtual void execute_command(const std::string&, const std::string&) = 0;
	virtual bool is_valid_command(const std::string&) const = 0;
};


