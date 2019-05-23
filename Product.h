#pragma once
#ifndef ama_Product_h
#define ama_Product_h
#include "ErrorState.h"
#include "iProduct.h"

namespace ama {



	class Product : public iProduct
	{
	public:
		// Public members are declared by instructions' order
		Product(char type = 'N');
		Product(const char* p_sku, const char* p_name, const char* p_unit, double p_price = 0.0, int p_nqty = 0, int p_qty = 0, bool p_status = true);

		Product(const Product& other);
		//Copy constructor

		~Product();
		//Destructor

		Product& operator=(const Product& other);
		//Copy Assignment Operator

		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator>(const char* sku) const;
		bool operator>(const iProduct& other) const;
		//Member operators

		int qtyAvailable() const;
		int qtyNeeded() const;
		double total_cost() const;
		const char* name() const;

		bool isEmpty() const;
		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;



	protected:
		void message(const char* pText);
		bool isClear() const;


	private:
		const char m_type;
		char m_sku[max_length_sku + 1];
		char m_unit[max_length_unit + 1];
		char * m_name;
		int m_qty;
		int m_nqty;
		double m_price;
		bool m_status;
		ErrorState errorstate;

	};





}
#endif // !ama_Product_h
