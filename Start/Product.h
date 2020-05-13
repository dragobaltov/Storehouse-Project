#include <iostream>
#include <ctime>
#include "Place.h"
#include "Date.h"
#include "ProductInfo.h"
#pragma once

const size_t COUNT_UNITS = 6;
const std::string UNITS[COUNT_UNITS] = { "kg", "l", "kilograms", "liters", "kilogram", "liter" };

bool is_in_units(const std::string& unit);
std::string to_lower(const std::string&);
int get_first_index(const std::string&, char);
std::string get_data(std::istream&);

class Product
{
	friend std::ostream& operator<<(std::ostream&, const Product&);
	friend std::istream& operator>>(std::istream&, Product&);
public:
	Product();
	Product(const std::string&, const Date&, const Date&, const std::string&,
		const std::string&, size_t, const Place&, const std::string&);
	Product(const Product&);
	Product& operator=(const Product&);
	~Product();
	bool operator==(const Product&) const;

	void set_name(const std::string&);
	void set_expiration_date(const Date&);
	void set_arrival_date(const Date&);
	void set_manifacturer_name(const std::string&);
	void set_unit(const std::string&);
	void set_quantity(size_t);
	void set_place(const Place&);
	void set_comment(const std::string&);
	
	const std::string& get_name() const;
	const Date& get_expiration_date() const;
	const Date& get_arrival_date() const;
	const std::string& get_manifacturer_name() const;
	const std::string& get_unit() const;
	size_t get_quantity() const;
	const Place& get_place() const;
	const std::string& get_comment() const;

	ProductInfo get_short_info() const;
	void increase_quantity(size_t);
	void decrease_quantity(size_t);
private:
	std::string m_name;
	Date m_expiration_date;
	Date m_arrival_date;
	std::string m_manifacturer_name;
	std::string m_unit;
	size_t m_quantity;
	Place m_place;
	std::string m_comment;

	void set_data(const std::string&, const Date&, const Date&, const std::string&,
		const std::string&, size_t, const Place&, const std::string&);
};

