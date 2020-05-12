#include "Change.h"

Change::Change() = default;

Change::Change(ChangeType type, const std::string& product_info, const Date& date) :
	m_type{ type }, m_product_info{ product_info }, m_date{ date } {}

void Change::print(std::ostream& out) const
{
	std::string result = "";

	switch (m_type)
	{
	case ChangeType::added:
		result += "added ";
		break;
	case ChangeType::removed:
		result += "removed ";
		break;
	default:
		result += "undefined ";
		break;
	}

	result += m_product_info;

	out << result << ' ' << m_date << '\n';
}

const Date& Change::get_date() const
{
	return m_date;
}

std::ostream& operator<<(std::ostream& out, const Change& change)
{
	change.print(out);
	return out;
}

std::istream& operator>>(std::istream& in, Change& change)
{
	std::string line{};
	std::getline(in, line);

	if (line == "")
	{
		return in;
	}

	std::vector<std::string> tokens{};
	split(line, tokens, ' ');

	ChangeType type;

	if (tokens[0] == "added")
	{
		type = ChangeType::added;
	}
	else if (tokens[0] == "removed")
	{
		type = ChangeType::removed;
	}
	else
	{
		type = ChangeType::undefined;
	}

	Date date = { tokens[tokens.size() - 1] };
	std::string info = "";

	for (size_t i = 1; i < tokens.size() - 2; ++i)
	{
		info += tokens[i] + ' ';
	}
	info += tokens[tokens.size() - 2];

	change = Change(type, info, date);

	return in;
}