#pragma once
#include "Section.h"
#include "Product.h"
#include "Change.h"
#include <utility>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Storehouse
{
	friend std::istream& operator>>(std::istream&, Storehouse&);
	friend std::ostream& operator<<(std::ostream&, const Storehouse&);
public:
	Storehouse();
	
	void add_product(const Product&);
	void remove_product(const std::string&, size_t);
	void clean();
	void log(const Date&, const Date&) const;
	void increase_quantity_of(const Product&);
	void loss(const std::string&, double, const Date&, const Date&) const;

	Place product_place(const Product&) const;
	bool place_is_free(const Place&) const;

	void print_products(std::ostream&) const;
private:
	std::vector<Section> m_sections{};
	std::vector<Change> m_changes{};

	void get_sorted_products_by_exp_date(std::vector<Product>&, const std::string&) const;
	size_t get_total_quantity(const std::vector<Product>&) const;
	char get_answer(const std::string&) const;
	int get_index_of(const std::vector<std::string>&, const std::string&) const;
};


