#pragma once
#include <iostream>
#include <fstream>
using namespace std;
/*Implementation of Date class
*This class manage date information
*@param  private : _day ( day ) , _month (month ) , _year (year)
*/
namespace elc {

    class Date
    {
    private :
        int _day;
        int _month;
        int _year;
    public:
        /*Date constructor
        *@param day , month , year
        *@return The Date object
        */
        Date(int day , int month , int year);
        /*Date empty constructor
        *@return The Date object
        */
        Date();
        /*Gets day
        *@return day
        */
        int getDay() const { return _day; }
        /*Gets month
        *@return month
        */
        int getMonth() const { return _month; }
        /*Gets year
        *@return year
        */
        int getYear() const { return _year; }
        /*Set Date
        *@param day , month , year
        */
        void setDate(int day, int month, int year);
        //This function printing Date
        friend ostream& operator<<(ostream& os, const Date& date)
        {
            os << "Date : " << date.getDay() << " / " << date.getMonth() << " / " << date.getYear();
            return os;
        }
		//This method load date data to input file
        virtual void load(istream& in);
		//This method save date data to output file
        virtual void save(ostream& out) const;
    };

}
