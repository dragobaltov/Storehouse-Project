#include "ProductInfo.h"
#include <iostream>
#include <regex>

ProductInfo::ProductInfo() = default;

ProductInfo::ProductInfo(const std::string& name, const std::string& unit, size_t quantity, const Place& place) :
	m_name{ name }, m_unit{ unit }, m_quantity{ quantity }, m_place{ place } {}

ProductInfo::ProductInfo(const ProductInfo & other) : m_name{ other.m_name }, m_unit{ other.m_unit },
m_quantity{ other.m_quantity }, m_place{ other.m_place } {}

/*! Parses string to ProductInfo. Accepts string in the format "{quantity} {unit} of {name} at {place}"*/
ProductInfo::ProductInfo(const std::string& text)
{
	size_t delim1_pos = text.find(" of ");
	size_t delim2_pos = text.find(" at ");
	std::string first_part = text.substr(0, delim1_pos);
	std::string second_part = text.substr(delim1_pos + 4, delim2_pos - delim1_pos - 4);
	std::string third_part = text.substr(delim2_pos + 4);

	size_t space_pos = first_part.find(' ');

	m_name = second_part;
	m_unit = first_part.substr(space_pos + 1);
	m_quantity = num_parse(first_part.substr(0, space_pos));
	m_place = { third_part };
}

ProductInfo::~ProductInfo() = default;

ProductInfo& ProductInfo::operator=(const ProductInfo & other)
{
	if (this != &other)
	{
		m_name = other.m_name;
		m_unit = other.m_unit;
		m_quantity = other.m_quantity;
		m_place = other.m_place;
	}

	return *this;
}

const std::string& ProductInfo::get_name() const
{
	return m_name;
}

const std::string& ProductInfo::get_unit() const
{
	return m_unit;
}

size_t ProductInfo::get_quantity() const
{
	return m_quantity;
}

const Place& ProductInfo::get_place() const
{
	return m_place;
}

/*! Prints ProductInfo object in the format "{quantity} {unit} of {name} at {place}"*/
std::ostream& operator<<(std::ostream& out, const ProductInfo& pr_info)
{
	out << pr_info.m_quantity << ' ' << pr_info.m_unit << " of " << pr_info.m_name << " at " << pr_info.m_place;

	return out;
}
