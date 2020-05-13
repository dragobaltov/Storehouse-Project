#include "StorehouseEngine.h"
#include <fstream>

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
	if (m_status != Status::open)
	{
		std::cout << INVALID_ACTION_MSG;
		return;
	}

	m_house.print_products(std::cout);
}

void StorehouseEngine::add()
{
	if (m_status != Status::open)
	{
		std::cout << INVALID_ACTION_MSG;
		return;
	}

	std::string name;
	std::string exp_date;
	std::string manif_name;
	std::string unit;
	size_t quantity;
	std::string comment;

	std::cout << "Enter product information:\n";
	std::cout << "> Name: ";
	std::getline(std::cin, name);
	std::cout << "> Expiration date(yyyy-mm-dd): ";
	std::getline(std::cin, exp_date);
	std::cout << "> Manifacturer: ";
	std::getline(std::cin, manif_name);
	std::cout << "> Unit: ";
	std::getline(std::cin, unit);
	std::cout << "> Quantity: ";
	std::cin >> quantity;
	std::cin.ignore(); // ----------------------- //
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
	if (m_status != Status::open)
	{
		std::cout << INVALID_ACTION_MSG;
		return;
	}

	m_house.clean();
}

void StorehouseEngine::log(const Date & date1, const Date & date2) const
{
	if (m_status != Status::open)
	{
		std::cout << INVALID_ACTION_MSG;
		return;
	}

	m_house.log(date1, date2);
}

void StorehouseEngine::remove()
{
	if (m_status != Status::open)
	{
		std::cout << INVALID_ACTION_MSG;
		return;
	}

	std::string name = "";
	size_t quantity = 0;
	std::cout << "> Product name you would like to remove: ";
	std::getline(std::cin, name);
	std::cout << "> Quantity: ";
	std::cin >> quantity;
	std::cin.ignore();

	m_house.remove_product(name, quantity);
}

void StorehouseEngine::loss() const
{
	if (m_status != Status::open)
	{
		std::cout << INVALID_ACTION_MSG;
		return;
	}

	std::string name = "";
	double price = 0;
	std::string from = "";
	std::string to = "";

	std::cout << "Product name: ";
	std::getline(std::cin, name);
	std::cout << "Price per unit: ";
	std::cin >> price;
	std::cin.ignore();
	std::cout << "Enter the wanted period.\n" << "From: ";
	std::getline(std::cin, from);
	std::cout << "To: ";
	std::getline(std::cin, to);

	Date date1 = { from };
	Date date2 = { to };

	m_house.loss(name, price, date1, date2);
}

void StorehouseEngine::load(std::istream & in)
{
	in >> m_house;
}

void StorehouseEngine::save_data(std::ostream & out) const
{
	out << m_house;
}

void StorehouseEngine::execute_command(const std::string & command, const std::string & additional)
{
	if (command == "open")
	{
		open(additional);
	}
	else if (command == "save")
	{
		save_as(m_current_file);
	}
	else if (command == "saveas")
	{
		save_as(additional);
	}
	else if (command == "help")
	{
		help();
	}
	else if (command == "close")
	{
		close();
	}
	else if (command == "exit")
	{
		exit();
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
	size_t section;
	size_t shelf;
	size_t num;

	std::cout << "Choose where to place the product:\n";
	std::cout << "> Section: ";
	std::cin >> section;
	std::cout << "> Shelf: ";
	std::cin >> shelf;
	std::cout << "> Number: ";
	std::cin >> num;

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
	}
	std::cin.ignore(); // ----------------------------- //

	place = { section, shelf, num };
}