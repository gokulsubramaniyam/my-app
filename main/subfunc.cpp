// my_class.cpp
#include "subfunc.h" // header in local directory
#include <iostream> // header in standard library

using namespace sf;
using namespace std;


int subfunc::ret_double(int val) {
	return (2 * val);
}
string subfunc:: return_to_string(utility::string_t val) {
	wstring ws(val);
	string str(ws.begin(), ws.end());

	
	return str;
}
std::wstring subfunc::return_to_string_t(string val) {
	std::wstring str2(val.length(), L' '); // Make room for characters
	// Copy string to wstring.
	std::copy(val.begin(), val.end(), str2.begin());
	return str2;
}

