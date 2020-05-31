#pragma once
#include "Date.h"
#include "ProductInfo.h"

/*! Represents the type of the change.\n
 * Possible values: added, removed, cleaned, undefined*/
enum class ChangeType
{
	added,
	removed,
	cleaned,
	undefined
};

/*! \brief Keeps the info for a change.
 *
 * Contains:\n 
 * type, which is of type enum ChangeType. Indicates the type of the change that was made - added, removed or cleaned.\n
 * date - the date when the change was made\n
 * product info - object of type ProductInfo - gives a short description of the product
*/
class Change
{
public:
	Change();
	Change(ChangeType, const ProductInfo&, const Date&);
	Change(const Change&);
	~Change();
	Change& operator=(const Change&);
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
