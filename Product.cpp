//Name : Juhwan Kim
//Section : SAA
//Student Number : 118363183
//E-mail : jkim528@myseneca.ca




#include <iostream>
#include <string.h>
#include <iomanip>
#include "Product.h"

using namespace std;


namespace ama {
	//Protected members
	void Product::message(const char* p_Text) {
		errorstate.message(p_Text);
	}

	bool Product::isClear() const {
		if (errorstate.message() == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}


	//Public members
	Product::Product(char p_type) : m_type(p_type) {

		m_sku[0] = '\0';
		m_unit[0] = '\0';
		m_name = nullptr;
		m_qty = 0;
		m_nqty = 0;
		m_price = 0.0;
		m_status = false;
		//this state is safe empty state.
	}

	Product::Product(const char* p_sku, const char* p_name, const char* p_unit, double p_price, int p_nqty, int p_qty, bool p_status) : m_type('N') {

		m_price = p_price;
		m_nqty = p_nqty;
		m_qty = p_qty;
		m_status = p_status;

		strncpy(m_sku, p_sku, max_length_sku);
		m_sku[max_length_sku] = '\0';

		strncpy(m_unit, p_unit, max_length_unit);
		m_unit[max_length_unit] = '\0';

		if (p_name != nullptr)
		{
			m_name = new char[max_length_name + 1];
			strncpy(m_name, p_name, max_length_name);
			m_name[max_length_name] = '\0';

		}
		else {

			m_sku[0] = '\0';
			m_unit[0] = '\0';
			m_name = nullptr;
			m_qty = 0;
			m_nqty = 0;
			m_price = 0.0;
			m_status = false;
		}


	}

	Product::Product(const Product & other) : m_type(other.m_type) {

		m_qty = other.m_qty;
		m_nqty = other.m_nqty;
		m_price = other.m_price;
		m_status = other.m_status;

		strncpy(m_sku, other.m_sku, max_length_sku);
		m_sku[max_length_sku] = '\0';

		strncpy(m_unit, other.m_unit, max_length_unit);
		m_unit[max_length_unit] = '\0';

		if (other.m_name != nullptr) {
			m_name = nullptr;
			m_name = new char[max_length_name + 1];
			strncpy(m_name, other.m_name, max_length_name);
			m_name[max_length_name] = '\0';
		}
		else {
			m_name = nullptr;
		}

	}

	Product::~Product() {
		delete[] m_name;
		m_name = nullptr;

	}

	Product &Product::operator=(const Product &other) {
		if (this != &other) {

			m_qty = other.m_qty;
			m_nqty = other.m_nqty;
			m_price = other.m_price;
			m_status = other.m_status;

			strncpy(m_sku, other.m_sku, max_length_sku);
			m_sku[max_length_sku] = '\0';
			strncpy(m_unit, other.m_unit, max_length_unit);
			m_unit[max_length_unit] = '\0';

			if (other.m_name != nullptr) {
				delete[] m_name;
				m_name = new char[max_length_name + 1];
				strncpy(m_name, other.m_name, max_length_name);
				m_name[max_length_name] = '\0';

			}
			else {
				m_name = nullptr;
			}
		}

		return *this;
	}

	int Product::operator+=(int cnt) {
		if (cnt > 0) {
			m_qty += cnt;
		}
		return m_qty;
	}

	bool Product::operator==(const char* tsku) const {
		if (strcmp(this->m_sku, tsku) == 0) {
			return true;
		}
		else {
			return false;
		}

	}

	bool Product::operator>(const char* tsku) const {
		if (strcmp(this->m_sku, tsku) > 0)
		{
			return true;
		}
		else {
			return false;
		}
	}

	bool Product::operator>(const iProduct& other) const {
		if (strcmp(this->m_name, other.name()) > 0)
		{
			return true;
		}
		else {
			return false;
		}
	}

	int Product::qtyAvailable() const {
		return m_qty;
	}

	int Product::qtyNeeded() const {
		return m_nqty;
	}

	const char* Product::name() const {
		return m_name;
	}

	double Product::total_cost() const {
		if (m_status == true)
		{
			return (m_price + (m_price * tax_rate)) * m_qty;
		}
		else
		{
			return m_price * m_qty;

		}



	}

	bool Product::isEmpty() const {
		if (m_name == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	istream& Product::read(istream& in, bool interractive) {
		char tm_sku[max_length_sku];
		char *tm_name = new char[max_length_name + 1];
		char tm_unit[max_length_unit];
		int tm_qty;
		int tm_nqty;
		double tm_price;
		char tm_tax;
		bool tm_status;
		// these are for reading values

		if (interractive == true) {

			cout << setw(max_length_label) << right << "Sku: ";
			in >> tm_sku;
			cout << setw(max_length_label) << right << " Name (no spaces): ";
			in >> tm_name;
			cout << setw(max_length_label) << right << " Unit: ";
			in >> tm_unit;
			cout << setw(max_length_label) << right << " Taxed? (y/n): ";
			in >> tm_tax;
			if (tm_tax == 'Y' || tm_tax == 'y')
			{
				tm_status = true;
			}
			else if (tm_tax == 'N' || tm_tax == 'n') {
				tm_status = false;
			}
			else {
				errorstate.message("Only (Y)es or (N)o are acceptable!");
				in.setstate(ios::failbit);
			}
			if (!in.fail()) {
				cout << setw(max_length_label) << right << "Price: ";
				in >> tm_price;
				if (in.fail()) {
					errorstate.message("Invalid Price Entry!");
					in.setstate(ios::failbit);
				}
			}
			if (!in.fail()) {
				cout << setw(max_length_label) << right << "Quantity on hand: ";
				in >> tm_qty;
				if (in.fail()) {
					errorstate.message("Invalid Quantity Available Entry!");
					in.setstate(ios::failbit);
				}
			}
			if (!in.fail()) {
				cout << setw(max_length_label) << right << "Quantity needed: ";
				in >> tm_nqty;

				if (in.fail()) {
					errorstate.message("Invalid Quantity Needed Entry!");
					in.setstate(ios::failbit);
				}
			}

			if (!in.fail()) {
				Product temp = Product(tm_sku, tm_name, tm_unit, tm_price, tm_nqty, tm_qty, tm_status);
				*this = temp;
			}


		}

		else
		{
			char divider = ',';
			//cin.getline
			in.getline(tm_sku, max_length_sku, ',');
			in.getline(tm_name, max_length_name, ',');
			in.getline(tm_unit, max_length_unit, ',');
			in >> tm_price >> divider >> tm_status >> divider >> tm_qty >> divider >> tm_nqty;

			Product temp = Product(tm_sku, tm_name, tm_unit, tm_price, tm_nqty, tm_qty, tm_status);
			*this = temp;


		}
		delete[] tm_name;
		tm_name = nullptr;
		return in;
	}

	ostream& Product::write(ostream& out, int writemode) const {
		if (isClear() == false) {
			out << errorstate.message();
		}
		if (isEmpty() == false && isClear() == true) {
			if ((writemode == write_condensed)) {
				char divider = ',';
				out << m_type << divider << m_sku << divider << m_name << divider << m_unit
					<< divider << m_price << divider << m_status
					<< divider << m_qty << divider << m_nqty;
			}
			else if (writemode == write_table) {
				const char *decision = "yes";
				out << " ";
				out << setw(max_length_sku) << right << m_sku;
				out << " " << '|';
				out << " ";
				if (strlen(m_name) > 16) {
					for (int i = 0; i < 13; i++)
					{
						out << m_name[i];
					}
					out << "...";
				}

				else {
					out << setw(16) << left << m_name;
				}
				out << " " << '|';
				out << " ";
				out << setw(10) << left << m_unit;
				out << " " << '|';
				out << " ";
				out << setw(7) << right << setprecision(2) << m_price;
				out << " " << '|';
				if (m_status == 1) {
					out << " ";
					out << setw(3) << right << decision;
					out << " " << '|';
				}
				else {
					decision = "no";
					out << " ";
					out << setw(3) << right << decision;
					out << " " << '|';
				}

				out << " ";
				out << setw(6) << right << m_qty;
				out << " " << '|';
				out << " ";
				out << setw(6) << right << m_nqty;
				out << " " << '|';

			}
			else if (writemode == write_human) {
				out << setw(max_length_label) << right << "Sku: " << m_sku << endl;
				out << setw(max_length_label) << right << "Name: " << m_name << endl;
				out << setw(max_length_label) << right << fixed << setprecision(2) << "Price: " << m_price << endl;
				if (m_status == true)
				{
					out << setw(max_length_label) << right << fixed << setprecision(2) << "Price after Tax: " << m_price + m_price * tax_rate << endl;
				}
				else
				{
					out << setw(max_length_label) << right << fixed << setprecision(2) << "Price after Tax: " << m_price << endl;
				}

				out << setw(max_length_label) << right << "Quantity Available: " << m_qty << " " << m_unit << endl;
				out << setw(max_length_label) << right << "Quantity Needed: " << m_nqty << " " << m_unit << endl;
			}

		}
		return out;



	}






}


