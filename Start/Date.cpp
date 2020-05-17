#include <iostream>
#include <cassert>
#include <iomanip>

#include "Date.h"

Date::Date() = default;

Date::Date(size_t year, size_t month, size_t day)
{
	set_year(year);
	set_month(month);
	set_day(day);
}

Date::Date(const std::string& text_date)
{
	std::vector<std::string> tokens;
	split(text_date, tokens, '-');

	if (tokens.size() == 3)
	{
		set_year(num_parse(tokens[0]));
		set_month(num_parse(tokens[1]));
		set_day(num_parse(tokens[2]));
	}
}

Date::Date(const Date& other)
{
	set_year(other.m_year);
	set_month(other.m_month);
	set_day(other.m_day);
}

Date& Date::operator=(const Date& other)
{
	set_year(other.m_year);
	set_month(other.m_month);
	set_day(other.m_day);

	return *this;
}

Date::~Date() = default;

bool Date::operator==(const Date& other) const
{
	return m_year == other.m_year && m_month == other.m_month && m_day == other.m_day;
}

bool Date::operator!=(const Date& other) const
{
	return !(*this == other);
}

bool Date::operator<(const Date& other) const
{
	if (m_year < other.m_year)
	{
		return true;
	}
	else if (m_year > other.m_year)
	{
		return false;
	}

	if (m_month < other.m_month)
	{
		return true;
	}
	else if (m_month > other.m_month)
	{
		return false;
	}

	if (m_day < other.m_day)
	{
		return true;
	}

	return false;
}

bool Date::operator>(const Date& other) const
{
	return !(*this < other) && !(*this == other);
}

bool Date::operator<=(const Date& other) const
{
	return !(*this > other);
}

bool Date::operator>=(const Date& other) const
{
	return !(*this < other);
}

void Date::set_year(size_t year)
{
	assert(year);
	m_year = year;
}

void Date::set_month(size_t month)
{
	assert(month >= 1 && month <= 12);
	m_month = month;
}

void Date::set_day(size_t day)
{
	bool is_leap_year = false;

	if (m_year % 4 == 0)
	{
		if (m_year % 100 == 0)
		{
			if (m_year % 400 == 0)
			{
				is_leap_year = true;
			}
		}
		else
		{
			is_leap_year = true;
		}
	}

	size_t days_in_month = 0;

	if (m_month == 4 || m_month == 6 || m_month == 9 || m_month == 11)
	{
		days_in_month = 30;
	}
	else if (m_month == 2)
	{
		if (is_leap_year)
		{
			days_in_month = 29;
		}
		else
		{
			days_in_month = 28;
		}
	}
	else
	{
		days_in_month = 31;
	}

	assert(day >= 1 && day <= days_in_month);
	m_day = day;
}

size_t Date::get_year() const
{
	return m_year;
}

size_t Date::get_month() const
{
	return m_month;
}

size_t Date::get_day() const
{
	return m_day;
}

Date Date::current_date()
{
	time_t t = time(0);
	struct tm* now = localtime(&t);

	return { static_cast<size_t>(now->tm_year + 1900), static_cast<size_t>(now->tm_mon + 1), 
		static_cast<size_t>(now->tm_mday) };
}

std::ostream& operator<<(std::ostream& out, const Date& date)
{
	out << date.m_year << '-' << std::setw(2) << std::setfill('0') << date.m_month 
		<< '-' << std::setw(2) << std::setfill('0') << date.m_day;
	return out;
}

void split(const std::string& text, std::vector<std::string>& container, char delimeter)
{
	std::string word = "";

	for (auto x : text)
	{
		if (x == delimeter)
		{
			if (!word.empty())
			{
				container.push_back(word);
			}

			word = "";
		}
		else
		{
			word += x;
		}
	}

	if (!word.empty())
	{
		container.push_back(word);
	}
}

size_t num_parse(const std::string& text_num)
{
	size_t num = 0;

	for (size_t i = 0; i < text_num.length(); i++)
	{
		if (text_num[i] < '0' || text_num[i] > '9')
			return 0;

		num = num * 10 + (text_num[i] - '0');
	}

	return num;
}