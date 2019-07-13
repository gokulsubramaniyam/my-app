
	
#pragma once
#include "cpprest/filestream.h"
#include"cpprest/http_listener.h"
using namespace std;


namespace errs
{
	class Errors
	{
	
		
	public:
		int LoginVal;
		void set_Login_Error(int val);
		int get_Login_Error();
	};
}