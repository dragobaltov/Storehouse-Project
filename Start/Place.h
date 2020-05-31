#include <iostream>
#include "Date.h"
#include <string>
#pragma once

/*! \brief Describes the location of a product in the storehouse.
 * 
 * Contains section, shelf and cell number.
*/
class Place
{
	friend std::ostream& operator<<(std::ostream&, const Place&);
public:
	Place();
	Place(size_t, size_t, size_t);
	Place(const Place&);
	Place(const std::string&);
	Place& operator=(const Place&);
	~Place();
	bool operator==(const Place&) const;

	void set_section(size_t);
	void set_shelf(size_t);
	void set_num(size_t);

	size_t get_section() const;
	size_t get_shelf() const;
	size_t get_num() const;
	std::string get_string_representation() const;

	void change(size_t, size_t, size_t);
private:
	size_t m_section{ 0 };
	size_t m_shelf{ 0 };
	size_t m_num{ 0 };
};