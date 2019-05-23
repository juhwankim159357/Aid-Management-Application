#include <iostream>
#include <iomanip>
#include "Perishable.h"
using namespace std;

namespace ama {
	Perishable::Perishable() : Product('P') {}

	ostream& Perishable::write(std::ostream& os, int writemode) const {
		Product::write(os, writemode);
		if (m_date.status() == no_error) {
			if (writemode == write_human) {
				cout << setw(max_length_label) << right << "Expiry Date: ";
				os << m_date << endl;
			}
			if (writemode == write_table)
			{
				os << " " << m_date << " |";
			}
			if (writemode == write_condensed)
			{
				os << "," << m_date;
			}
		}
		return os;
	}

	istream& Perishable::read(std::istream& is, bool interractive) {
		Product::read(is, interractive);

		if (interractive == true) {
			cout << setw(max_length_label) << right << "Expiry date (YYYY/MM/DD): ";
			is >> m_date;
			if (m_date.status() == error_year) {
				message("Invalid Year in Date Entry");
				is.setstate(std::ios::failbit);
			}

			if (m_date.status() == error_mon) {
				message("Invalid Month in Date Entry");
				is.setstate(std::ios::failbit);
			}

			if (m_date.status() == error_day) {
				message("Invalid Day in Date Entry");
				is.setstate(std::ios::failbit);
			}

			if (m_date.status() == error_input) {
				message("Invalid Date Entry");
				is.setstate(std::ios::failbit);
			}
		}
		else {
			is.ignore();
			m_date.read(is);
		}
		return is;
	}




}