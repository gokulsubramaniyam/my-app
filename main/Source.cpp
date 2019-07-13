#include<iostream>
#include "mysql.h"
#include "cpprest/http_client.h"
#include "cpprest/filestream.h"
#include"cpprest/http_listener.h"

#include "cpprest/details/web_utilities.h"
#include<string>
#include<fstream>

#include "Router.h"
using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;
using namespace std;
using namespace web::http::experimental::listener;
using namespace route;


#define TRACE(msg)            wcout << msg
#define TRACE_ACTION(a, k, v) wcout << a << L" (" << k << L", " << v << L")\n"
int qstate;

http_response res;
ROUTER router;

/*MYSQL_ROW get_a_single_row (MYSQL *conn, string query) {
	MYSQL_ROW row=NULL;
	MYSQL_RES *res;
	
	const char *q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate) {
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		}
	return row;
}

MYSQL* connect() {

	MYSQL *conn=NULL;
	
	cout << "trying to connect:";
	try {

		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "root", "testdb", 3306, NULL, 0);
		if (conn) {
			cout << "Connected";
		}
		else {
			cout << "not";
		}
	}
	catch (exception &e) {
		cout << e.what() << endl;
	}
	return conn;

}

string return_to_string(utility::string_t val){
	wstring ws(val);
	string str(ws.begin(), ws.end());
	
	cout <<"converting:"<< str;
	return str;

}

MYSQL_ROW login_DAL(string id,string name) {

	MYSQL *conn = connect();
	string query = ("Select * from test where id="+id);
	MYSQL_ROW row = get_a_single_row(conn, query);
	if (row != NULL) {
		cout << "ID=" << row[0] << "Name=" << row[1];
	}
	return row;
}

void handle_login(http_request request)
{

	MYSQL_ROW row;
	string url;
	string usersss;
	wcout << "Enterd handle";
	json::value temp;
	
	request.extract_json()
		.then([&temp](pplx::task<json::value> task)
	{
		temp = task.get();
	
	})
		.wait();
	//do whatever you want with 'temp' here
	//wcout << "1" << temp[0] << "2" << temp[1];*/
	/*wcout << "Printing temp:" << temp << endl;
	uri urls = request.absolute_uri();
	utility::string_t urlss = urls.to_string();
	string abs_url = return_to_string(urlss);
	cout <<"url="<< abs_url<<endl;*/
	/*utility::string_t s;
	s = temp.at(U("id")).as_string();
	string ids = return_to_string(s);
	s = temp.at(U("name")).as_string();
	string name = return_to_string(s);
	//int id = std::stoi(ids);
	string id = ids;
	cout << id << " " << name<<endl;
	row=login_DAL(id,name);
	if(row!=NULL)
		request.reply(status_codes::OK, temp); //send the reply as a json.
	else
		request.reply(status_codes::NotFound, temp);

}
void handle_user_create(http_request request) {
	json::value temp;

	request.extract_json()
		.then([&temp](pplx::task<json::value> task)
	{
		temp = task.get();

	})
		.wait();
	//get_user_details(temp);
}
void handle_routes(http_request request) {
	uri urls = request.absolute_uri();
	utility::string_t urlss = urls.to_string();
	string abs_url = return_to_string(urlss);
	cout << "url=" << abs_url << endl;
	if (abs_url == "/login") {
		handle_login(request);
	}
	if (abs_url == "/create_user") {
		handle_user_create(request);
	}
	else {
		cout << "Not routed:" << endl;
	}
}
*/

void handle_listen(http_request request) {
	router.route(request);
}
void listen() {

	string url;
	
	http_listener server_listener(L"http://localhost"); //define a listener for login.
	
	server_listener.support(methods::POST, handle_listen);
	try
	{
		server_listener
			.open()                     //start listening
			.then([&server_listener]() {TRACE(L"\nstarting to  listen\n"); })
			.wait();

			while (true);
	}
	catch (exception const & e)
	{
		wcout << e.what() << endl;
	}
}




int main() {
	listen();
}









