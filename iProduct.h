//Name : Juhwan Kim
//Section : SAA
//Student Number : 118363183
//E-mail : jkim528@myseneca.ca


#ifndef ama_IPRODUCT_H
#define ama_IPRODUCT_H
#include <iostream>

namespace ama {
	const int max_length_label = 30;
	const int max_length_sku = 7;
	const int max_length_name = 75;
	const int max_length_unit = 10;
	const int write_condensed = 0;
	const int write_table = 1;
	const int write_human = 2;
	const double tax_rate = 0.13;
	// These are const values

	class iProduct
	{
	public:
		virtual ~iProduct() {};
		virtual std::ostream& write(std::ostream& os, int writeMode) const = 0;
		virtual std::istream& read(std::istream& is, bool interractive) = 0;
		virtual bool operator==(const char* sku) const = 0;
		virtual double total_cost() const = 0;
		virtual int qtyNeeded() const = 0;
		virtual int qtyAvailable() const = 0;
		virtual const char* name() const = 0;
		virtual int operator+=(int qty) = 0;
		virtual bool operator>(const iProduct& others) const = 0;

	};


}

#endif