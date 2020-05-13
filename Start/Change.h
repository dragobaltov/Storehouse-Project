#pragma once
#include "Date.h"
#include "ProductInfo.h"
#include <string>
#include <vector>

enum class ChangeType
{
	added,
	removed,
	cleaned,
	undefined
};

class Change
{
public:
	Change();
	Change(ChangeType, const ProductInfo&, const Date&);
	void print(std::ostream&) const;
	const Date& get_date() const;
	const ChangeType get_type() const;
	const ProductInfo& get_info() const;
private:
	ChangeType m_type{ChangeType::undefined};
	ProductInfo m_product_info{};
	Date m_date{};
};

std::ostream& operator<<(std::ostream&, const Change&);
std::istream& operator>>(std::istream&, Change&);
