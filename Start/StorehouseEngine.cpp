#include "StorehouseEngine.h"
#include <fstream>
#include <regex>

StorehouseEngine::StorehouseEngine() = default;

void StorehouseEngine::help() const
{
	Engine::help();

	std::cout << "print - prints information about products\n";
	std::cout << "add - adds new product\n";
	std::cout << "remove - removes a product by given name and quantity\n";
	std::cout << "clean - clears all expired products\n";
	std::cout << "log <from> <to> - gives information about all changes in the period <from> <to>\n";
	std::cout << "loss - estimates the loss by a given product, price and period\n";
}

void StorehouseEngine::print() const
{
	m_house.print_products(std::cout);
}

void StorehouseEngine::add()
{
	std::string name = "";
	std::string exp_date = "";
	std::string manif_name = "";
	std::string unit = "";
	size_t quantity = 0;
	std::string comment = "";

	std::cout << "Enter product information:\n";
	std::cout << "> Name: ";
	std::getline(std::cin, name);
	read_date(exp_date, "> Expiration date(yyyy-mm-dd): ");
	std::cout << "> Manifacturer: ";
	std::getline(std::cin, manif_name);
	read_unit(unit, "> Unit: ");
	quantity = read_quantity("> Quantity: ");
	std::cout << "> Comment: ";
	std::getline(std::cin, comment);

	Product pr{ name, exp_date, Date::current_date(), manif_name, unit, quantity, {}, comment };
	Place place = m_house.product_place(pr);

	if (place.get_section() == 0)
	{
		read_place(place);

		while (!m_house.place_is_free(place))
		{
			std::cout << "This place is not free! Please, choose another one!\n";
			read_place(place);
		}

		pr.set_place(place);
		m_house.add_product(pr);
	}
	else
	{
		pr.set_place(place);
		m_house.increase_quantity_of(pr);
	}
}

void StorehouseEngine::clean()
{
	m_house.clean();
}

void StorehouseEngine::log(const Date & date1, const Date & date2) const
{
	m_house.log(date1, date2);
}

void StorehouseEngine::remove()
{
	std::string name = "";
	std::cout << "> Product name you would like to remove: ";
	std::getline(std::cin, name);
	size_t quantity = read_quantity("> Quantity: ");

	m_house.remove_product(name, quantity);
}

void StorehouseEngine::loss() const
{
	std::string name = "";
	double price = 0;
	std::string from = "";
	std::string to = "";

	std::cout << "Product name: ";
	std::getline(std::cin, name);
	std::cout << "Price per unit: ";
	std::cin >> price;
	std::cin.ignore();
	std::cout << "Enter the wanted period.\n";
	read_date(from, "From: ");
	read_date(to, "To: ");

	Date date1 = { from };
	Date date2 = { to };

	m_house.loss(name, price, date1, date2);
}

void StorehouseEngine::load(std::istream & in)
{
	in >> m_house;
}

void StorehouseEngine::unload()
{
	m_house.unload();
}

void StorehouseEngine::save_data(std::ostream & out) const
{
	out << m_house;
}

void StorehouseEngine::execute_command(const std::string & command, const std::string & additional)
{
	if (command == "open")
	{
		if (additional == "")
		{
			std::cout << INVALID_FILE_NAME_MSG;
			return;
		}
		open(additional);
	}
	else if (command == "help")
	{
		help();
	}
	else if (command == "exit")
	{
		exit();
	}
	else
	{
		if (m_status != Status::open)
		{
			std::cout << INVALID_ACTION_MSG;
			return;
		}

		if (command == "save")
		{
			save_as(m_current_file);
		}
		else if (command == "saveas")
		{
			if (additional == "")
			{
				std::cout << INVALID_FILE_NAME_MSG;
				return;
			}

			save_as(additional);
		}
		else if (command == "close")
		{
			close();
		}
		else if (command == "add")
		{
			add();
		}
		else if (command == "remove")
		{
			remove();
		}
		else if (command == "print")
		{
			print();
		}
		else if (command == "clean")
		{
			clean();
		}
		else if (command == "log")
		{
			std::pair<std::string, std::string> dates = split_in_two(additional, ' ');

			if (std::regex_match(dates.first, DATE_FORMAT) && std::regex_match(dates.second, DATE_FORMAT))
			{
				log({ dates.first }, { dates.second });
			}
			else
			{
				std::cout << "Invalid date format! Please, use 'YYYY-MM-DD' format.\n";
			}
		}
		else if (command == "loss")
		{
			loss();
		}
	}
	
}

bool StorehouseEngine::is_valid_command(const std::string & command) const
{
	for (size_t i = 0; i < COUNT_COMMANDS; ++i)
	{
		if (command == VALID_COMMANDS[i])
		{
			return true;
		}
	}

	return false;
}

void StorehouseEngine::read_place(Place & place) const
{
	size_t section = 0;
	size_t shelf = 0;
	size_t num = 0;

	std::cout << "Choose where to place the product:\n";
	std::cout << "> Section: ";
	std::cin >> section;
	std::cout << "> Shelf: ";
	std::cin >> shelf;
	std::cout << "> Number: ";
	std::cin >> num;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (section < 1 || section > COUNT_SECTIONS || shelf < 1 || shelf > COUNT_SHELVES ||
		num < 1 || num > SHELF_CAPACITY)
	{
		std::cout << "Invalid place!\nChoose where to place the product:\n";
		std::cout << "> Section: ";
		std::cin >> section;
		std::cout << "> Shelf: ";
		std::cin >> shelf;
		std::cout << "> Number: ";
		std::cin >> num;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	place = { section, shelf, num };
}

void StorehouseEngine::read_date(std::string& str_date, const std::string& prefix_msg) const
{
	std::cout << prefix_msg;
	std::getline(std::cin, str_date);

	while (!std::regex_match(str_date, DATE_FORMAT))
	{
		std::cout << "Invalid date! Please try again:\n" << prefix_msg;
		std::getline(std::cin, str_date);
	}
}

void StorehouseEngine::read_unit(std::string& unit, const std::string& prefix_msg) const
{
	std::cout << prefix_msg;
	std::getline(std::cin, unit);

	while (!is_in_units(unit))
	{
		std::cout << "Inavlid unit! Supported units are kg and l\n" << prefix_msg;
		std::getline(std::cin, unit);
	}
}

size_t StorehouseEngine::read_quantity(const std::string& prefix_msg) const
{
	size_t quantity = 0;

	std::cout << prefix_msg;
	std::cin >> quantity;
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (!quantity)
	{
		std::cout << "Quantity cannot be 0!\n" << prefix_msg;
		std::cin >> quantity;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return quantity;
}