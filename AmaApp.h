#ifndef ama_AmaApp_h
#define ama_AmaApp_h

#include"iProduct.h"

namespace ama {
	class AmaApp {
	public:
		AmaApp(const char* filename);
		~AmaApp();
		int run();

	private:
		char m_filename[256];
		iProduct* m_products[100];
		int m_noOfProducts = 0;
		AmaApp(const AmaApp& other) = delete;
		AmaApp& operator=(const AmaApp& other) = delete;
		void pause() const;
		int menu() const;
		void loadProductRecords();
		void saveProductRecords() const;
		void listProducts() const;
		iProduct* find(const char* sku) const;
		void addQty(iProduct* product);
		void addProduct(char tag);
	};


}








#endif // !ama_AmaApp_h
