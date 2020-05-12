#pragma once
#include "Product.h"
#include "Date.h"
#include <string>
#include <vector>

enum class ChangeType
{
	added,
	removed,
	undefined
};

class Change
{
public:
	Change();
	Change(ChangeType, const std::string&, const Date&);
	void print(std::ostream&) const;
	const Date& get_date() const;
private:
	ChangeType m_type{ChangeType::undefined};
	std::string m_product_info{""};
	Date m_date{};
};

std::ostream& operator<<(std::ostream&, const Change&);
std::istream& operator>>(std::istream&, Change&);
