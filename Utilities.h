//Name : Juhwan Kim
//Section : SAA
//Student Number : 118363183
//E-mail : jkim528@myseneca.ca



#pragma once
#ifndef ama_Utilities_h
#define ama_Utilities_h
#include "Product.h"
namespace ama {

	double& operator+=(double& total, const iProduct& prod);
	std::ostream& operator<<(std::ostream& out, const iProduct& prod);
	std::istream& operator>>(std::istream& in, iProduct& prod);
	iProduct* createInstance(char tag);

}
#endif // !ama_Utilities_h
