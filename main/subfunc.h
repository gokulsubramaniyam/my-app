
#pragma once

#include "cpprest/details/web_utilities.h"
//#ifndef SOME_STRING_H
//#define SOME_STRING_H

using namespace std;
using namespace web;

namespace sf {
	class subfunc
	{

	public:
		string return_to_string(utility::string_t val);
		std::wstring return_to_string_t(string val);
		int ret_double(int val);
		
		

	};
}
//#endif 
