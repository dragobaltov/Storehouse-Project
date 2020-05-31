#include <iostream>
#include "Place.h"

Place::Place() = default;

Place::Place(size_t section, size_t shelf, size_t num)
{
	change(section, shelf, num);
}

/*! Parses string to Place.*/
Place::Place(const std::string& text_place)
{
	// section #, shelf #, number #
	std::string copy = text_place;
	
	size_t section = 0;
	size_t shelf = 0;
	size_t number = 0;

	int index = 0;
	std::string text;

	index = copy.find(", ");
	text = copy.substr(0, index);
	section = num_parse(text.substr(text.find(' ') + 1));
	
	copy = copy.substr(index + 2);

	index = copy.find(", ");
	text = copy.substr(0, index);
	shelf = num_parse(text.substr(text.find(' ') + 1));

	copy = copy.substr(index + 2);

	number = num_parse(copy.substr(copy.find(' ') + 1));
	
	change(section, shelf, number);
}

Place::Place(const Place& other)
{
	change(other.m_section, other.m_shelf, other.m_num);
}

Place::~Place() = default;

Place& Place::operator=(const Place& other)
{
	if (this != &other)
	{
		change(other.m_section, other.m_shelf, other.m_num);
	}

	return *this;
}

/*! Compares section, shelf and cell number.*/
bool Place::operator==(const Place& other) const
{
	return m_section == other.m_section && m_shelf == other.m_shelf && m_num == other.m_num;
}

void Place::change(size_t section, size_t shelf, size_t num)
{
	set_section(section);
	set_shelf(shelf);
	set_num(num);
}

void Place::set_section(size_t section)
{
	m_section = section;
}

void Place::set_shelf(size_t shelf)
{
	m_shelf = shelf;
}

void Place::set_num(size_t num)
{
	m_num = num;
}

size_t Place::get_section() const
{
	return m_section;
}

size_t Place::get_shelf() const
{
	return m_shelf;
}

size_t Place::get_num() const
{
	return m_num;
}

/*! Returns a string in the format "section {#section}, shelf {#shelf}, number {#cell}"*/
std::string Place::get_string_representation() const
{
	return "section " +  std::to_string(m_section) + ", shelf " + std::to_string(m_shelf)
		+ ", number " + std::to_string(m_num);
}

std::ostream& operator<<(std::ostream & out, const Place& place)
{
	out << place.get_string_representation();
	return out;
}

