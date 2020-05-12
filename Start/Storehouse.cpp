#include "Storehouse.h"

Storehouse::Storehouse()
{
	for (size_t i = 1; i <= COUNT_SECTIONS; ++i)
	{
		m_sections.emplace_back(Section(i));
	}
}

void Storehouse::add_product(const Product& product)
{
	m_sections[product.get_place().get_section() - 1].add(product);

	Change ch = Change(ChangeType::added, product.get_short_info(), Date::current_date());
	m_changes.emplace_back(ch);
	std::cout << ch;
}

void Storehouse::increase_quantity_of(const Product& product)
{
	size_t section = product.get_place().get_section();

	m_sections[section - 1].increase_quantity_of(product);
}

void Storehouse::remove_product(const std::string& name, size_t quantity)
{
	std::vector<Product> products;
	get_sorted_products_by_exp_date(products, name);

	size_t total_quantity = get_total_quantity(products);

	if (total_quantity == 0)
	{
		std::cout << "There aren't any " << name << ".\n";
	}
	else if (total_quantity < quantity)
	{
		std::string question = "There are only " + std::to_string(total_quantity) + " units of " + name
			+ " left. Would you like to remove them?(Y/N)\n";
		char answer = get_answer(question);

		if (answer == 'Y' || answer == 'y')
		{
			Change ch{};
			Date curr_date = Date::current_date();

			for (size_t i = 0; i < products.size(); i++)
			{
				size_t section = products[i].get_place().get_section();
				m_sections[section - 1].remove(products[i], products[i].get_quantity());

				ch = Change(ChangeType::removed, products[i].get_short_info(), curr_date);
				m_changes.emplace_back(ch);
				std::cout << ch;
			}
		}
	}
	else
	{
		Change ch;
		Date curr_date = Date::current_date();
		size_t section = 0;
		std::string info = "";
		size_t quantity_to_remove = 0;

		for (size_t i = 0; i < products.size() && quantity > 0; i++)
		{
			section = products[i].get_place().get_section();
			quantity_to_remove = fmin(products[i].get_quantity(), quantity);
			info = std::to_string(quantity_to_remove) + " " + products[i].get_unit() + " of " + products[i].get_name() +
				" at " + products[i].get_place().get_string_representation();

			m_sections[section - 1].remove(products[i], quantity_to_remove);

			ch = Change(ChangeType::removed, info, curr_date);
			m_changes.emplace_back(ch);
			std::cout << ch;

			quantity -= quantity_to_remove;
		}
	}
}

void Storehouse::clean()
{
	Date curr_date = Date::current_date();
	Change ch{};

	for (size_t i = 0; i < COUNT_SECTIONS; i++)
	{
		size_t size = m_sections[i].get_count_products();

		for (size_t j = 0; j < size; j++)
		{
			if (m_sections[i][j].get_expiration_date() <= curr_date)
			{
				ch = Change(ChangeType::removed, m_sections[i][j].get_short_info(), curr_date);

				bool is_removed = m_sections[i].remove(m_sections[i][j], m_sections[i][j].get_quantity());

				if (is_removed)
				{
					--j;
					--size;
				}

				m_changes.emplace_back(ch);
				std::cout << ch;
			}
		}
	}
}

void Storehouse::log(const Date& date1, const Date& date2) const
{
	if (date1 > date2)
	{
		std::cout << "No changes in the period from " << date1 << " to " << date2 << '\n';
		return;
	}

	Date date{};

	for (size_t i = 0; i < m_changes.size(); i++)
	{
		date = m_changes[i].get_date();
		if (date >= date1 && date <= date2)
		{
			std::cout << m_changes[i];
		}
	}
}

bool Storehouse::place_is_free(const Place& place) const
{
	return m_sections[place.get_section()].place_is_free(place);
}

void Storehouse::print_products(std::ostream& out) const
{
	std::vector<std::string> names{};
	std::vector<size_t> quantities{};

	for (size_t i = 0; i < COUNT_SECTIONS; ++i)
	{
		size_t size = m_sections[i].get_count_products();

		for (size_t j = 0; j < size; ++j)
		{
			std::string name = m_sections[i][j].get_name();
			int index = get_index_of(names, name);

			if (index == -1)
			{
				names.emplace_back(name);
				quantities.emplace_back(m_sections[i][j].get_quantity());
			}
			else
			{
				quantities[index] += m_sections[i][j].get_quantity();
			}
		}
	}

	for (size_t i = 0; i < names.size(); ++i)
	{
		std::cout << names[i]<< " - " << quantities[i] << " units\n";
	}
}

std::ostream& operator<<(std::ostream& out, const Storehouse& storehouse)
{
	out << "Products:\n";

	for (size_t i = 0; i < COUNT_SECTIONS; ++i)
	{
		out << storehouse.m_sections[i];
	}

	out << "Changes:\n";

	for (size_t i = 0; i < storehouse.m_changes.size(); ++i)
	{
		out << storehouse.m_changes[i];
	}

	return out;
}

std::istream& operator>>(std::istream& in, Storehouse& storehouse)
{
	in.ignore(256, '\n');

	Product pr;
	std::string line;
	std::getline(in, line);

	while (!in.eof() && line != "Changes:")
	{
		in.seekg(-(static_cast<int>(line.size()) + 2), std::ios::cur);
		in >> pr;

		size_t section = pr.get_place().get_section();
		storehouse.m_sections[section - 1].add(pr);

		std::getline(in, line);
	}

	Change ch;
	std::getline(in, line);

	while (!in.eof() && line != "")
	{
		in.seekg(-(static_cast<int>(line.size()) + 2), std::ios::cur);
		in >> ch;

		storehouse.m_changes.emplace_back(ch);

		std::getline(in, line);
	}

	return in;
}

char Storehouse::get_answer(const std::string& question) const
{
	std::string ans;
	std::cout << question << "< ";
	std::getline(std::cin, ans);

	while (ans[0] != 'Y' && ans[0] != 'y' && ans[0] != 'N' && ans[0] != 'n')
	{
		std::cout << "Invalid answer! Please, answer with Yes(Y) or No(N).\n" << "< ";
		std::getline(std::cin, ans);
	}

	return ans[0];
}

void Storehouse::get_sorted_products_by_exp_date(std::vector<Product>& products, const std::string& name) const
{
	for (size_t i = 0; i < COUNT_SECTIONS; ++i)
	{
		size_t size = m_sections[i].get_count_products();

		for (size_t j = 0; j < size; ++j)
		{
			if (m_sections[i][j].get_name() == name)
			{
				products.emplace_back(m_sections[i][j]);
			}
		}
	}
}

size_t Storehouse::get_total_quantity(const std::vector<Product>& products) const
{
	size_t total = 0;

	for (size_t i = 0; i < products.size(); ++i)
	{
		total += products[i].get_quantity();
	}

	return total;
}

Place Storehouse::product_place(const Product& product) const
{
	for (size_t i = 0; i < COUNT_SECTIONS; ++i)
	{
		size_t size = m_sections[i].get_count_products();

		for (size_t j = 0; j < size; ++j)
		{
			if (m_sections[i][j] == product)
			{
				return m_sections[i][j].get_place();
			}
		}
	}

	return {};
}

int Storehouse::get_index_of(const std::vector<std::string>& names, const std::string& name) const
{
	for (size_t i = 0; i < names.size(); ++i)
	{
		if (names[i] == name)
		{
			return i;
		}
	}

	return -1;
}