#ifndef ama_perishable_h
#define ama_perishable_h
#include "Date.h"
#include "Product.h"

namespace ama {

	class Perishable : public Product {
	public:
		Perishable();
		std::ostream& write(std::ostream& os, int writemode) const;
		std::istream& read(std::istream& is, bool interractive);

	private:
		Date m_date;
	};
}

#endif