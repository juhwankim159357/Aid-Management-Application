//Name : Juhwan Kim
//Section : SAA
//Student Number : 118363183
//E-mail : jkim528@myseneca.ca


#include <iostream>
#include <ostream>
#include <string.h>
#include "ErrorState.h"

using namespace std;

namespace ama {

	ErrorState::ErrorState(const char* errorMessage) {
		if (errorMessage != nullptr && errorMessage[0] != '\0') {
			msg = new char[strlen(errorMessage) + 1];
			strncpy(msg, errorMessage, strlen(errorMessage) + 1);
		}
		else {
			msg = nullptr;
		}
	}

	ErrorState::~ErrorState() {
		delete[] msg;
		msg = nullptr;
	}

	ErrorState::operator bool() const {
		if (msg != nullptr) {
			return true;
		}
		else {
			return false;
		}
	}

	ErrorState& ErrorState::operator=(const char* pText) {

		if (pText == nullptr || pText[0] == '\0') {
			delete[] msg;
			msg = nullptr;
		}
		else {
			msg = new char[strlen(pText) + 1];
			strncpy(msg, pText, strlen(pText) + 1);
		}
		return *this;
	}

	void ErrorState::message(const char* pText) {

		if (pText == nullptr || pText[0] == '\0') {
			delete[] msg;
			msg = nullptr;
		}
		else {
			msg = new char[strlen(pText) + 1];
			strncpy(msg, pText, strlen(pText) + 1);
		}
	}
	const char* ErrorState::message() const {
		if (this->msg != nullptr) {
			return msg;
		}
		else {
			return nullptr;
		}
	}
	//helper function start---------------------------
	ostream& operator<<(ostream& ostr, const ErrorState& Object) {
		if (Object.message() != nullptr) {
			ostr << Object.message();
		}
		return ostr;
	}
	//helper function ends---------------------------
}