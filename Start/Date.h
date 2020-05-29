#include <iostream>
#include <vector>
#include <string>
#pragma once

void split(const std::string&, std::vector<std::string>&, char);
size_t num_parse(const std::string&);

class Date
{
	friend std::ostream& operator<<(std::ostream&, const Date&);
public:
	Date();
	Date(size_t, size_t, size_t);
	Date(const std::string&);
	Date(const Date&);
	Date& operator=(const Date&);
	~Date();

	bool operator==(const Date&) const;
	bool operator!=(const Date&) const;
	bool operator<(const Date&) const;
	bool operator>(const Date&) const;
	bool operator<=(const Date&) const;
	bool operator>=(const Date&) const;

	void set_year(size_t);
	void set_month(size_t);
	void set_day(size_t);

	size_t get_year() const;
	size_t get_month() const;
	size_t get_day() const;

	static Date current_date();
private:
	size_t m_year{0};
	size_t m_month{0};
	size_t m_day{0};
};