#pragma once
#include "mysql.h"
#include"cpprest/http_listener.h"


using namespace std;

using namespace web::http;

namespace route
{
	class ROUTER
	{
	public:
		
		void route(http_request request);
	};
}
