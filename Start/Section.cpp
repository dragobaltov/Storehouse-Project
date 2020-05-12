#include <iostream>
#include <cassert>
#include "Section.h"
#include "Product.h"

Section::Section() = default;

Section::Section(size_t num)
{
	set_num(num);
	
}

Section::Section(const Section& other)
{
	m_num = other.m_num;
	m_products = other.m_products;
}

Section& Section::operator=(const Section& other)
{
	if (this != &other)
	{
		m_num = other.m_num;
		m_products = other.m_products;
	}

	return *this;
}

Section::~Section() = default;

const Product& Section::operator[](size_t index) const
{
	return m_products[index];
}

void Section::add(const Product& product)
{
	m_products.emplace_back(product);
}

bool Section::remove(const Product& product, size_t quantity)
{
	for (size_t i = 0; i < m_products.size(); i++)
	{
		if (m_products[i] == product)
		{
			if (m_products[i].get_quantity() > quantity)
			{
				m_products[i].decrease_quantity(quantity);
			}
			else
			{
				m_products.erase(m_products.begin() + i);

				return true;
			}

			return false;
		}
	}

	return false;
}

void Section::increase_quantity_of(const Product& product)
{
	for (size_t i = 0; i < m_products.size(); i++)
	{
		if (m_products[i] == product)
		{
			m_products[i].increase_quantity(product.get_quantity());
		}
	}
}

void Section::set_num(size_t num)
{
	assert(num >= 1 && num <= COUNT_SECTIONS);
	m_num = num;
}

size_t Section::get_num() const
{
	return m_num;
}

bool Section::place_is_free(const Place& place) const
{
	for (size_t i = 0; i < m_products.size(); i++)
	{
		if (m_products[i].get_place() == place)
		{
			return false;
		}
	}

	return true;
}

size_t Section::get_count_products() const
{
	return m_products.size();
}

std::ostream& operator<<(std::ostream& out, const Section& section)
{
	size_t size = section.get_count_products();

	for (size_t i = 0; i < size; i++)
	{
		out << section[i];
	}

	return out;
}