#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
#include "AmaApp.h"
#include "Product.h"
#include "Utilities.h"

using namespace std;

namespace ama {

	//All functions are declared by instruction's order
	AmaApp::AmaApp(const char* filename) {
		strncpy(m_filename, filename, strlen(filename));
		m_filename[strlen(filename)] = '\0';
		m_noOfProducts = 0;
		for (int i = 0; i < m_noOfProducts; i++) {
			m_products[i] = NULL;
		}
		// Set all the m_product elements to null 
		loadProductRecords();
	}

	AmaApp::~AmaApp() {
		for (int i = 0; i < m_noOfProducts; i++) {
			delete m_products[i];
		}
	}
	//deallocates all dynamic instances stored in the m_products array.

	void AmaApp::pause() const {
		cout << "Press Enter to continue...";
		cin.ignore(2000, '\n');
		// If the user hits any other key before pressing enter, the key is ignored
		cout << endl;
	}

	int AmaApp::menu() const {
		int selection = 10;

		cout << "Disaster Aid Supply Management Program" << endl;
		cout << "--------------------------------------" << endl;
		cout << "1- List products" << endl;
		cout << "2- Search product" << endl;
		cout << "3- Add non-perishable product" << endl;
		cout << "4- Add perishable product" << endl;
		cout << "5- Add to product quantity" << endl;
		cout << "6- Delete product" << endl;
		cout << "7- Sort products" << endl;
		cout << "0- Exit program" << endl;
		cout << "> ";
		cin >> selection;

		if (selection == 1 || selection == 2 || selection == 3 || selection == 4 || selection == 5 || selection == 0) {
			cin.ignore(200, '\n');
			//clearing input buffer before return
			return selection;
		}
		else {
			cin.ignore(200, '\n');
			return -1;
		}

	}

	void AmaApp::loadProductRecords() {
		for (int i = 0; i < m_noOfProducts; i++) {
			delete m_products[i];
		}
		//Delete all products from the array 

		int index = 0;
		//Set reading index to zero 

		char s;
		//declare one char to read one char

		std::fstream read_file;
		read_file.open(m_filename, ios::in);
		//Open the file for reading (use ios::in)

		if (read_file.is_open()) {
			while (!read_file.eof()) {
				//if the file is open, then   until reading fails loop 

				read_file >> s;
				//read one char character to identify type of Product 

				iProduct* temp_tp = createInstance(s);
				// call the ama::createInstance(tag) to create an instance 

				if (temp_tp != NULL) {
					// if createInstance(tag) returns not null 

					m_products[index] = temp_tp;
					// store the product in the array at the read index 

					read_file.ignore();
					//skip the comma from the file

					m_products[index]->read(read_file, false);
					//read the product from the file (non-interractive mode) 

					index++;
					//increment the read index 
				}
			}
			m_noOfProducts = index;
			//set number of products to readIndex 
		}
		read_file.close();
		//close the datafile 
	}

	void AmaApp::saveProductRecords() const {
		std::fstream write_file;
		write_file.open(m_filename, ios::out);
		for (int i = 0; i < m_noOfProducts; i++) {
			if (write_file.is_open()) {
				m_products[i]->write(write_file, write_condensed) << std::endl;
			}
		}
		write_file.close();

	}

	void AmaApp::listProducts() const {
		double cost = 0.0;
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "| Row |     SKU | Product Name     | Unit       |   Price | Tax |   QtyA |   QtyN | Expiry     |" << endl;
		cout << "|-----|---------|------------------|------------|---------|-----|--------|--------|------------|" << endl;

		for (int i = 0; i < m_noOfProducts - 1; i++) {
			//On our inventory txt file, there is 10 items. Therefore, from 0 to 9 of m_noOfProducts must be called
			//However because of our txt files' eof setting, firstly 11 array elements are created. even if there are only 10 items.
			//11th item doesn't have meaningful data so there is no need to list.
			//And also 11th meaningless item will be replaced by addProduct function.
			//So listProduct function will display meaningful data items and addProduct funtion will replace last item which is meaningless to meaningful item.

			cout << "|";
			cout << setw(4) << right << i + 1;
			cout << " " << "|";
			cout << fixed;
			cout.precision(2);
			m_products[i]->write(cout, write_table) << std::endl;
			cost += m_products[i]->total_cost();
		}

		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << "|                                                      Total cost of support ($): | ";
		cout << fixed;
		cout.precision(2);
		cout << setw(10) << right << cost;
		cout << " |" << endl;
		cout << "------------------------------------------------------------------------------------------------" << endl;
		cout << endl;

		pause();
	}

	iProduct* AmaApp::find(const char* psku) const {
		int find_index = 200;
		bool temp = false;
		for (int i = 0; i < m_noOfProducts; i++) {
			temp = (*m_products[i] == psku);
			if (temp == true) {
				find_index = i;
			}
		}
		if (find_index <= 100) {
			return m_products[find_index];
		}
		else {
			return NULL;
		}
	}

	void AmaApp::addQty(iProduct* ppproduct) {
		int answer = 0;
		ppproduct->write(cout, write_human);
		cout << endl;
		cout << endl;
		cout << "Please enter the number of purchased items: ";
		cin >> answer;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(200, '\n');
			cout << "Invalid quantity value!" << endl;
			cout << endl;
		}
		else
		{
			if (answer <= (ppproduct->qtyNeeded() - ppproduct->qtyAvailable()))
			{
				*ppproduct += answer;
				cout << endl;
				cout << "Updated!" << endl;
				cout << endl;
			}
			else
			{
				cout << "Too many items; only " << ppproduct->qtyNeeded() - ppproduct->qtyAvailable() << " is needed. Please return the extra " << answer - (ppproduct->qtyNeeded() - ppproduct->qtyAvailable()) << " items." << endl;
				*ppproduct += ppproduct->qtyNeeded() - ppproduct->qtyAvailable();
				cout << endl;
				cout << "Updated!" << endl;
				cout << endl;
			}
		}
	}

	void AmaApp::addProduct(char ppptag) {
		iProduct* temp_p = createInstance(ppptag);
		if (temp_p != NULL)
		{
			m_products[m_noOfProducts - 1] = temp_p;
			cin >> *m_products[m_noOfProducts - 1];


			if (cin.fail()) {
				cin.clear();
				cout << endl;
				cout << *m_products[m_noOfProducts - 1] << endl;
				cout << endl;
			}
			else
			{
				saveProductRecords();
				cout << endl;
				cout << "Success!" << endl;
				cout << endl;
			}
		}
	}

	int AmaApp::run() {
		int selection = 10;
		char answer[100] = {};
		do
		{
			selection = menu();
			if (selection == 1) {
				AmaApp::listProducts();
			}
			else if (selection == 2) {
				cout << "Please enter the product SKU: ";
				cin >> answer;
				cin.ignore(200, '\n');
				cout << endl;
				find(answer);
				if (find(answer) != NULL) {
					find(answer)->write(cout, write_human);
					cout << endl;
				}
				else {
					cout << "No such product!" << endl;
				}
				pause();
			}

			else if (selection == 3) {
				addProduct('n');
				loadProductRecords();
				cin.ignore(200, '\n');
			}
			else if (selection == 4) {
				addProduct('p');
				loadProductRecords();
				cin.ignore(200, '\n');
			}
			else if (selection == 5)
			{
				char answer[100];
				cout << "Please enter the product SKU: ";
				cin >> answer;
				cin.ignore(200, '\n');
				cout << endl;
				find(answer);
				if (find(answer) != NULL) {
					addQty(find(answer));
				}
				else {
					cout << "No such product!" << endl;
					cout << endl;
				}
			}

			else if (selection == 0) {
				cout << "Goodbye!" << endl;
			}

			else {
				cout << "~~~Invalid selection, try again!~~~" << endl;
				pause();
			}

		} while (selection != 0);

		return 0;
	}
}

