#include "Change.h"
#include <string>
#include <vector>

Change::Change() = default;

Change::Change(ChangeType type, const ProductInfo& product_info, const Date& date) :
	m_type{ type }, m_product_info{ product_info }, m_date{ date } {}

Change::Change(const Change& other) : 
	m_type{ other.m_type }, m_product_info{ other.m_product_info }, m_date{ other.m_date } {}

Change::~Change() = default;
 
Change& Change::operator=(const Change& other)
{
	if (this != &other)
	{
		m_type = other.m_type;
		m_product_info = other.m_product_info;
		m_date = other.m_date;
	}

	return *this;
}

/*! Prints the change in the format: "type product_info date"*/
void Change::print(std::ostream& out) const
{
	std::string result = "";

	switch (m_type)
	{
	case ChangeType::added:
		out << "added ";
		break;
	case ChangeType::removed:
		out << "removed ";
		break;
	case ChangeType::cleaned:
		 out << "cleaned ";
		break;
	default:
		out << "undefined ";
		break;
	}

	out << m_product_info << ' ' << m_date << '\n';
}

const Date& Change::get_date() const
{
	return m_date;
}

const ChangeType Change::get_type() const
{
	return m_type;
}

const ProductInfo& Change::get_info() const
{
	return m_product_info;
}

std::ostream& operator<<(std::ostream& out, const Change& change)
{
	change.print(out);
	return out;
}

std::istream& operator>>(std::istream& in, Change& change)
{
	std::string line{};
	std::getline(in, line);

	if (line == "")
	{
		return in;
	}

	size_t first_space_pos = line.find(' ');
	size_t last_space_pos = line.find_last_of(' ');

	std::string type_str = line.substr(0, first_space_pos);
	std::string info_str = line.substr(first_space_pos + 1, last_space_pos - first_space_pos - 1);
	std::string date_str = line.substr(last_space_pos + 1);

	ChangeType type;

	if (type_str == "added")
	{
		type = ChangeType::added;
	}
	else if (type_str == "removed")
	{
		type = ChangeType::removed;
	}
	else if (type_str == "cleaned")
	{
		type = ChangeType::cleaned;
	}
	else
	{
		type = ChangeType::undefined;
	}

	change = Change(type, { info_str }, { date_str });

	return in;
}