//Name : Juhwan Kim
//Section : SAA
//Student Number : 118363183
//E-mail : jkim528@myseneca.ca

#pragma once
#ifndef ama_ErrorState_h
#define ama_ErrorState_h
#include <ostream>

namespace ama {

	class ErrorState
	{
	public:
		explicit ErrorState(const char* errorMessage = nullptr);
		ErrorState(const ErrorState& other) = delete;
		~ErrorState();
		operator bool() const;
		void message(const char*);
		const char* message() const;
		ErrorState& operator=(const char*);
		ErrorState& operator=(const ErrorState& other) = delete;

	private:
		char* msg;

	};
	std::ostream& operator<<(std::ostream&, const ErrorState&); //helper function
}


#endif // !ama_ErrorState
