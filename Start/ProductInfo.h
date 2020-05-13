#pragma once
#include <iostream>
#include <regex>
#include "Place.h"
#include <string>

class ProductInfo
{
	friend std::ostream& operator<<(std::ostream&, const ProductInfo&);
public:
	ProductInfo();
	ProductInfo(const std::string&, const std::string&, size_t, const Place&);
	ProductInfo(const ProductInfo&);
	ProductInfo(const std::string&);
	~ProductInfo();
	ProductInfo& operator=(const ProductInfo&);

	const std::string& get_name() const;
	const std::string& get_unit() const;
	size_t get_quantity() const;
	const Place& get_place() const;
private:
	std::string m_name{""};
	std::string m_unit{""};
	size_t m_quantity{0};
	Place m_place{};
};