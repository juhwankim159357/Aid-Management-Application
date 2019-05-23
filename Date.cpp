//name : juhwan kim
//section : SAA
//student number : 118363183
//email : jkim528@myseneca.ca

#include <iostream>
#include <ostream>
#include <iomanip>
#include "Date.h"

using namespace std;


namespace ama {

	//private members and private member funtions======

	void Date::status(int newStatus) {
		if (newStatus == 0) {
			Status = no_error;
		}
		if (newStatus == 1) {
			Status = error_year;
		}
		if (newStatus == 2) {
			Status = error_mon;
		}
		if (newStatus == 3) {
			Status = error_day;
		}
		if (newStatus == 4) {
			Status = error_invalid_operation;
		}
		if (newStatus == 5) {
			Status = error_input;
		}
	}

	int Date::mdays(int year, int mon) const {
		int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
		int month = mon >= 1 && mon <= 12 ? mon : 13;
		month--;
		return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
	}

	int Date::date_calculator() const {

		return Year * 372 + Month * 12 + Day_of_the_Month;
	}
	// e.g. 2010/10/31 = 2010 * 372 + 10 * 12 + 31
	//				   = 8972791 days 
	// 	               = 2010/10/31 has 8972791 days from 0000/00/00. 

	void Date::set() {
		Year = 0;
		Month = 0;
		Day_of_the_Month = 0;
	}
	// To make safe empty state without assigning Status.
	// e.g. 0000/00/00 should be safe empty state and Status is no_error
	// but with this funtion 0000/00/00 is safe empty state but Status is not assigned.
	// This funtion is for seting int variables to safe empty state.
	// Status is assgined by status(int ) funtion;

//End of private members and private member funtions======


//Public member functions=====

	Date::Date() {
		set();
		status(no_error);
	}

	Date::Date(int year, int mon, int day) {

		if (year < min_year || year > max_year) {
			this->status(error_year);
			set();
		}
		else if (mon < 1 || mon > 12) {
			this->status(error_mon);
			set();
		}
		else if (day < 1 || day > mdays(year, mon)) {
			this->status(error_day);
			set();
		}
		else {
			this->status(no_error);
			Year = year;
			Month = mon;
			Day_of_the_Month = day;
		}
	}

	int Date::status() const {
		return Status;
	}

	void Date::clearError() {
		Status = no_error;
	}

	bool Date::isGood() {
		if (Year != 0 && Month != 0 && Day_of_the_Month != 0 && Status == no_error) {
			return true;
		}
		else {
			return false;
		}
	}
	// 'Year != 0 && Month != 0 && Day_of_the_Month != 0 && Status == no_error' means object has vaild values and Status is 'no_error'
	// The reason why I use this condition is Status 'no_error' has two meaning.
	// Firstly, 'no_error' means object is in safe empty state.
	// Secondly, 'no_error' means object has vaild values.
	// Therefore, there need to classify these two meanings, this condition refers to second meaning.
	// If isGood()' return value is true, object has no_error and has vaild values
	// If isGood()' return value is false, object has an error or is in safe empty state.

//End of Public member functions=====

//Public member operator=============

	Date& Date::operator+=(int days) {
		if (isGood() == false) {
			status(error_invalid_operation);
		}
		else {
			this->Day_of_the_Month += days;
			if (this->Day_of_the_Month < 1 || this->Day_of_the_Month > mdays(this->Year, this->Month)) {
				this->Day_of_the_Month -= days;
				status(error_invalid_operation);
			}
		}
		return *this;
	}

	Date& Date::operator++() {
		if (isGood() == false) {
			status(error_invalid_operation);
		}
		else {
			this->Day_of_the_Month += 1;
			if (this->Day_of_the_Month < 1 || this->Day_of_the_Month > mdays(this->Year, this->Month)) {
				this->status(error_invalid_operation);
				this->Day_of_the_Month--;
			}
		}
		return *this;
	}

	Date Date::operator++(int day) {
		Date temp = *this;
		if (isGood() == false) {
			status(error_invalid_operation);
		}
		else {
			++*this;
			if (temp.Day_of_the_Month < 1 || temp.Day_of_the_Month > mdays(temp.Year, temp.Month)) {
				temp.status(error_invalid_operation);
			}
		}
		return temp;
	}
	Date Date::operator+(int days) {
		Date temp = *this;
		if (this->isGood() == false) {
			temp.status(error_invalid_operation);
		}
		else {
			temp.Day_of_the_Month += days;
			if (temp.Day_of_the_Month < 1 || temp.Day_of_the_Month > mdays(temp.Year, temp.Month)) {
				temp.status(error_invalid_operation);
				temp.Day_of_the_Month -= days;
			}
		}
		return temp;
	}

	bool Date::operator==(const Date& rhs) {
		if (this->date_calculator() == rhs.date_calculator()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Date::operator!=(const Date& rhs) {
		if (this->date_calculator() != rhs.date_calculator()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Date::operator<(const Date& rhs) {
		if (this->date_calculator() < rhs.date_calculator()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Date::operator>(const Date& rhs) {
		if (this->date_calculator() > rhs.date_calculator()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Date::operator<=(const Date& rhs) {
		if (this->date_calculator() <= rhs.date_calculator()) {
			return true;
		}
		else {
			return false;
		}
	}

	bool Date::operator >= (const Date& rhs) {
		if (this->date_calculator() >= rhs.date_calculator()) {
			return true;
		}
		else {
			return false;
		}
	}
	//End of public member operator================================

	//IO member functions=========================================

	istream& Date::read(istream& is) {

		char divider;
		is >> Year >> divider >> Month >> divider >> Day_of_the_Month;
		if (is.fail() == true) {
			this->status(error_input);
			this->set();
		}
		else if (Year < min_year || Year > max_year) {
			this->status(error_year);
			this->set();
		}
		else if (Month < 1 || Month > 12) {
			this->status(error_mon);
			this->set();
		}
		else if (Day_of_the_Month < 1 || Day_of_the_Month > mdays(this->Year, this->Month)) {
			this->status(error_day);
			this->set();
		}
		else {
			this->status(no_error);
		}
		return is;
	}

	ostream& Date::write(ostream& ostr)const {
		ostr.fill('0');
		ostr.width(4);
		ostr.setf(ios::right);
		ostr << Year << "/";
		ostr.width(2);
		ostr << Month << "/";
		ostr.width(2);
		ostr << Day_of_the_Month << setfill(' ');
		// For formatting

		return ostr;
	}

	//End IO member Functions==================================

	//Helper Functions=========================================

	ostream& operator<<(ostream& out, const Date& Object) {
		return Object.write(out);
	}

	istream& operator>>(istream& in, Date& Object) {
		return Object.read(in);
	}

	//End Helper Functions=====================================
}

