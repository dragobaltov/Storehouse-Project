#include <iostream>
#include <iostream>
#include <cassert>
#include "Place.h"
#include "Date.h"
#include "Product.h"
#include <string>

Product::Product() : m_name{ "" }, m_expiration_date{}, m_arrival_date{}, m_manifacturer_name{ "" },
m_unit{ "" }, m_quantity{ 0 }, m_place{}, m_comment{ "" } {}

Product::Product(const std::string& name, const Date& expiration_date, const Date& arrival_date, 
	const std::string& manifacturer_name,const std::string& unit, size_t quantity, 
	const Place& place,const std::string& comment)
{
	set_data(name, expiration_date, arrival_date, manifacturer_name, unit, quantity, place, comment);
}

Product::Product(const Product& other)
{
	set_data(other.m_name, other.m_expiration_date, other.m_arrival_date, other.m_manifacturer_name, 
		other.m_unit, other.m_quantity, other.m_place, other.m_comment);
}

Product& Product::operator=(const Product& other)
{
	if (this != &other)
	{
		set_data(other.m_name, other.m_expiration_date, other.m_arrival_date, other.m_manifacturer_name, 
			other.m_unit, other.m_quantity, other.m_place, other.m_comment);
	}

	return *this;
}

Product::~Product() {}

bool Product::operator==(const Product& other) const
{
	return m_name == other.m_name && m_expiration_date == other.m_expiration_date;
}

void Product::set_name(const std::string& name)
{
	m_name = name;
}

void Product::set_expiration_date(const Date& expiration_date)
{
	m_expiration_date = expiration_date;
}

void Product::set_arrival_date(const Date& arrival_date)
{
	m_arrival_date = arrival_date;
}

void Product::set_manifacturer_name(const std::string& manifacturer_name)
{
	assert(manifacturer_name.length());
	m_manifacturer_name = manifacturer_name;
}

void Product::set_unit(const std::string& unit)
{
	assert(is_in_units(unit));
	m_unit = unit;
}

void Product::set_quantity(size_t quantity)
{
	assert(quantity);
	m_quantity = quantity;
}

void Product::set_place(const Place& place)
{
	m_place = place;
}

void Product::set_comment(const std::string& comment)
{
	m_comment = comment;
}

const std::string& Product::get_name() const
{
	return m_name;
}

const Date& Product::get_expiration_date() const
{
	return m_expiration_date;
}

const Date& Product::get_arrival_date() const
{
	return m_arrival_date;
}

const std::string& Product::get_manifacturer_name() const
{
	return m_manifacturer_name;
}

const std::string& Product::get_unit() const
{
	return m_unit;
}

size_t Product::get_quantity() const
{
	return m_quantity;
}

const Place& Product::get_place() const
{
	return m_place;
}

const std::string& Product::get_comment() const
{
	return m_comment;
}

void Product::set_data(const std::string& name, const Date& exp_date, const Date& arrival_date, 
	const std::string& manifacturer_name, const std::string& unit, size_t quantity, 
	const Place& place, const std::string& comment)
{
	set_name(name);
	set_expiration_date(exp_date);
	set_arrival_date(arrival_date);
	set_manifacturer_name(manifacturer_name);
	set_unit(unit);
	set_quantity(quantity);
	set_place(place);
	set_comment(comment);
}

std::ostream& operator<<(std::ostream& out, const Product& pr)
{
	out << "Name: " << pr.m_name << '\n' << "Expiration Date: " << pr.m_expiration_date << '\n'
		<< "Arrival Date: " << pr.m_arrival_date << '\n' << "Manifacturer: " << pr.m_manifacturer_name << '\n'
		<< "Quantity: " << pr.m_quantity << ' ' << pr.m_unit << '\n' 
		<< "Place in the storehouse: " << pr.m_place << '\n'
		<< "Comment: " << pr.m_comment << '\n';

	return out;
}

std::istream& operator>>(std::istream& in, Product& pr)
{
	std::string name;
	Date expiration_date;
	Date arrival_date;
	std::string manif_name;
	std::string unit;
	size_t quantity;
	Place place;
	std::string comment;

	name = get_data(in);
	expiration_date = { get_data(in) };
	arrival_date = { get_data(in) };
	manif_name = get_data(in);

	std::string unit_quantity_line = get_data(in);
	int space_index = get_first_index(unit_quantity_line, ' ');

	unit = unit_quantity_line.substr(space_index + 1);
	quantity = num_parse(unit_quantity_line.substr(0, space_index));

	std::string place_line = get_data(in);
	place = { place_line };
	
	comment = get_data(in);

	pr = Product(name, expiration_date, arrival_date, manif_name, unit, quantity, place, comment);

	return in;
}

ProductInfo Product::get_short_info() const
{
	return {m_name, m_unit, m_quantity, m_place};
}

void Product::increase_quantity(size_t quantity_to_add)
{
	m_quantity += quantity_to_add;
}

void Product::decrease_quantity(size_t quantity_to_remove)
{
	m_quantity -= quantity_to_remove;
}

//--------------------------------------------------------------------------------------
std::string get_data(std::istream& in)
{
	std::string line;
	int index;

	std::getline(in, line);
	index = get_first_index(line, ':');

	if (index == -1)
		return "";

	return line.substr(index + 2);
}

bool is_in_units(const std::string& unit)
{
	std::string unit_to_lower = to_lower(unit);

	for (size_t i = 0; i < COUNT_UNITS; i++)
	{
		if (UNITS[i] == unit_to_lower)
		{
			return true;
		}
	}

	return false;
}

/*std::string to_lower(const std::string& text)
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
}*/

int get_first_index(const std::string& text, char delimeter)
{
	for (size_t i = 0; i < text.length(); i++)
	{
		if (text[i] == delimeter)
		{
			return i;
		}
	}

	return -1;
}
//--------------------------------------------------------------------------------------
