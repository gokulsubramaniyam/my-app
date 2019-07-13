#pragma once

#include "ErrorHandler.h" // header in local directory
#include <iostream> // header in standard library
#include<string>
#include "subfunc.h" // header in local directory
#include "DAL.h"
#include "cpprest/json.h"


using namespace std;
using namespace sf;
using namespace dal;
using namespace json;
using namespace errs;

void Errors::set_Login_Error(int val) {

	Errors err;
	err.LoginVal = val;//0 =Ok,1=username present role not decided ,2 username or password is wrong
}
int Errors::get_Login_Error() {
	Errors err;
	int val = err.LoginVal;
	return val;
}