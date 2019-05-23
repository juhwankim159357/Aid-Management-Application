//Name : Juhwan Kim
//Section : SAA
//Student Number : 118363183
//E-mail : jkim528@myseneca.ca



#include <iostream>
#include <string.h>
#include <iomanip>
#include "Product.h"
#include "Utilities.h"
#include "Perishable.h"
using namespace std;

namespace ama {

	double& operator+=(double& total, const iProduct& prod) {
		total += prod.total_cost();
		return total;

	}

	ostream& operator<<(ostream& out, const iProduct& prod) {
		return prod.write(out, write_human);
	}

	istream& operator>>(istream& in, iProduct& prod) {
		prod.read(in, true);
		return in;
	}

	iProduct* createInstance(char tag) {
		if (tag == 'n' || tag == 'N') {
			Product* test = new Product();
			return test;

		}
		else if (tag == 'p' || tag == 'P') {

			Perishable* test = new Perishable();
			return test;
		}
		else
		{
			return NULL;
		}

	}


}