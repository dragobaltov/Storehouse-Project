#pragma once
#include "Engine.h"
#include "Storehouse.h"
#include "Change.h"
#include <string>
#include <regex>

const std::regex DATE_FORMAT("^([1-9][0-9]*)-((0?[1-9])|(1[0-2]))-((0?[1-9])|([1-2][0-9])|3[0-1])$");
const size_t COUNT_COMMANDS = 12;
const std::string VALID_COMMANDS[COUNT_COMMANDS] = { "open", "save", "saveas", "close", "exit", "help",
									  "print", "add", "remove", "clean", "log", "loss" };

class StorehouseEngine : public Engine
{
public:
	StorehouseEngine();
private:
	Storehouse m_house{};

	void load(std::istream&) override;
	void save_data(std::ostream&) const override;
	void help() const override;
	void execute_command(const std::string&, const std::string&) override;
	bool is_valid_command(const std::string&) const override;

	void print() const;
	void add();
	void remove();
	void log(const Date&, const Date&) const;
	void clean();
	void loss() const;

	void read_place(Place&) const;
};