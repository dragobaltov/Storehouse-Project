#include <iostream>
#include <vector>
#include "Product.h"
#pragma once

const size_t COUNT_SECTIONS = 10;
const size_t COUNT_SHELVES = 10;
const size_t SHELF_CAPACITY = 10;
const size_t CAPACITY = COUNT_SHELVES * SHELF_CAPACITY;

class Section
{
public:
	Section();
	Section(size_t);
	Section(const Section&);
	Section& operator=(const Section&);
	~Section();
	const Product& operator[](size_t) const;

	void set_num(size_t);
	size_t get_num() const;

	void add(const Product&);
	bool remove(const Product&, size_t);
	void increase_quantity_of(const Product&);

	bool place_is_free(const Place&) const;
	size_t get_count_products() const;
private:
	std::vector<Product> m_products{};
	size_t m_num{ 0 };
};

std::ostream& operator<<(std::ostream&, const Section&);