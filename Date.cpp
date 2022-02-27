#include "Date.h"

namespace elc {

	Date::Date(int day, int month, int year) : _day(day), _month(month), _year(year)
	{
		if ((month < 0) || (month > 12))
			throw invalid_argument("Invalid Month");
		else if (year < 0)
			throw invalid_argument("Invalid Year");
		else if (month == 2 && (day > 0 && day <= 28))
			throw invalid_argument("Invalid Day");
		else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && (day >= 1 && day <= 31))
			throw invalid_argument("Invalid Day");
		else if ((month == 4 || month == 6 || month == 8 || month == 9 || month == 11) && (day >= 0 && day <= 30))
			throw invalid_argument("Invalid Day");
	}

    Date::Date() : _day(0), _month(0), _year(0)
    {
    }

	void Date::setDate(int day, int month, int year) {
		if ((month < 0) || (month > 12))
			throw invalid_argument("Invalid Month");
		else if (year < 0)
			throw invalid_argument("Invalid Year");
		else if (month == 2 && !(day > 0 && day <= 28))
			throw invalid_argument("Invalid Day");
		else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && !(day >= 1 && day <= 31))
			throw invalid_argument("Invalid Day");
		else if ((month == 4 || month == 6 || month == 8 || month == 9 || month == 11) && !(day >= 0 && day <= 30))
			throw invalid_argument("Invalid Day");
		else {
			_day = day;
			_month = month;
			_year = year;
		}
	}

	void Date::load(istream& in)
	{
		in.read(reinterpret_cast<char*>(&_day), sizeof(_day));
		in.read(reinterpret_cast<char*>(&_month), sizeof(_month));
		in.read(reinterpret_cast<char*>(&_year), sizeof(_year));
		//if ((_month < 0) || (_month > 12))
		//	throw invalid_argument("Invalid Month");
		//else if (_year < 0)
		//	throw invalid_argument("Invalid Year");
		//else if (_month == 2 && !(_day > 0 && _day <= 28))
		//	throw invalid_argument("Invalid Day");
		//else if ((_month == 1 || _month == 3 || _month == 5 || _month == 7 || _month == 8 || _month == 10 || _month == 12) && !(_day >= 1 && _day <= 31))
		//	throw invalid_argument("Invalid Day");
		//else if ((_month == 4 || _month == 6 || _month == 8 || _month == 9 || _month == 11) && !(_day >= 0 && _day <= 30))
		//	throw invalid_argument("Invalid Day");
	}
    void Date::save(ostream& out) const
    {
        out.write(reinterpret_cast<const char*>(&_day), sizeof(_day));
        out.write(reinterpret_cast<const char*>(&_month), sizeof(_month));
        out.write(reinterpret_cast<const char*>(&_year), sizeof(_year));
    }
}