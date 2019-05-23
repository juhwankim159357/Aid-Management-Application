//name : juhwan kim
//section : SAA
//student number : 118363183
//email : jkim528@myseneca.ca
#pragma once

#ifndef ama_Date_h
#define ama_Date_h
#include <iostream>

namespace ama
{
	const int min_year = 2019;
	const int max_year = 2028;
	const int no_error = 0;
	const int error_year = 1;
	const int error_mon = 2;
	const int error_day = 3;
	const int error_invalid_operation = 4;
	const int error_input = 5;

	class Date
	{
	public:
		Date();
		Date(int, int, int);
		int status() const;
		void clearError();
		bool isGood();
		Date& operator+=(int);
		Date& operator++();
		Date operator++(int);
		Date operator+(int);
		bool operator==(const Date&);
		bool operator!=(const Date&);
		bool operator<(const Date&);
		bool operator>(const Date&);
		bool operator<=(const Date&);
		bool operator>=(const Date&);
		std::istream& read(std::istream&);
		std::ostream& write(std::ostream&)const;



	private:
		int Year;
		int Month;
		int Day_of_the_Month;
		int Status;
		void status(int);
		int mdays(int, int) const;

		// added private member functions
		int date_calculator() const; // To calculate how assigned date have days from 0000/00/00.
		void set(); // To make safe empty state without assigning Status.
	// End of added private member funtions.


	};

	std::ostream& operator<<(std::ostream& cout, const Date& D);
	std::istream& operator>>(std::istream& cin, Date& D);


}










#endif // !ama_Date_h
