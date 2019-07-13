// my_class.cpp

// header in local directory
#include <iostream> // header in standard library
#include<string>
 // header in local directory
#include "DAL.h"
#include "cpprest/json.h"
#include "ErrorHandler.h"
#include "mysql.h"

using namespace dal;
using namespace std;
using namespace json;
using namespace sf;
using namespace errs;
using namespace sf;



Errors err;


MYSQL* DAL:: connect() {
	MYSQL *conn = NULL;

	cout << "trying to connect:";
	try {

		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "localhost", "root", "root", "mydb", 3306, NULL, 0);
		if (conn) {
			cout << "Connected:";
		}
		else {
			cout << "not Connected:";
		}
	}
	catch (exception &e) {
		cout << e.what() << endl;
	}
	return conn;

}

MYSQL_ROW  get_a_single_row(MYSQL *conn, string query) {
	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate;

	const char *q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate) {
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
	}
	return row;
}
int insert(MYSQL *conn, string query) {
	int qstate;
	const char *q = query.c_str();
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	return qstate;
}

vector<web::json::value> get_result(MYSQL *conn, string query) {
	subfunc sfs;
	MYSQL_RES *res=NULL;
	MYSQL_ROW row;
	utility::string_t ss,es;
	vector<web::json::value> arrayObjects;
	int qstate;
	json::value obj;
	const char *q = query.c_str();
	qstate = mysql_query(conn, q);
	
	if (!qstate) {
		res = mysql_store_result(conn);
		cout << "Values Updated:" << mysql_num_rows(res);
		int num_rows = int(mysql_num_rows(res));
	
		if (num_rows != 0) {
			while ((row = mysql_fetch_row(res))) {
				string st = row[3];
				ss = sfs.return_to_string_t(st);
				string et = row[4];
				es = sfs.return_to_string_t(et);
				obj[L"start_time"] = json::value::string(ss);
				obj[L"end_time"] = json::value::string(es);
				arrayObjects.push_back(obj);

			
				
			}

			/*for (int i = 0; i < arrayObjects.size(); i++) {
				wcout <<"vlues"<< arrayObjects[i].at(U("start_time")).as_string();
			}*/
		}
	}
	return arrayObjects;
}
json::value get_my_skills(MYSQL *conn, string query,http_request request) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value close_activity;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"skill_name\":\"" + s1 + "\"}";
		}
		s += "]}";

	}
	wstring s1 = sfs.return_to_string_t(s);
	close_activity = json::value::string(s1);
	return close_activity;
}
json::value get_close_val(MYSQL *conn,string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value close_activity;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"Activity ID\":\"" + s1 + "\"," + "\"User Id\":\"" + row[1]+ "\"}";
		}
		s += "]}";

	}
	wstring s1 = sfs.return_to_string_t(s);
	close_activity = json::value::string(s1);
	return close_activity;
}
vector<web::json::value>  get_skill(MYSQL *conn, string query)
{
	subfunc sfs;
	MYSQL_RES *res = NULL;
	MYSQL_ROW row;
	utility::string_t ss, es;
	vector<web::json::value> arrayObjects;
	int qstate;
	json::value obj;
	const char *q = query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate) {
		res = mysql_store_result(conn);
		cout << "Values Updated:" << mysql_num_rows(res);
		int num_rows = int(mysql_num_rows(res));

		if (num_rows != 0) {
			while ((row = mysql_fetch_row(res))) {
				string st = row[0];
				ss = sfs.return_to_string_t(st);
				
				obj[L"skill_id"] = json::value::string(ss);
			
				arrayObjects.push_back(obj);



			}

			
		}
	}
	return arrayObjects;
}
json::value get_userstatus(MYSQL * conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value close_activity;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	int rows = int(mysql_affected_rows(conn));
	cout << "affected="<<rows;
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		if (res == NULL)
			cout << "IN DAL NULL";
		else
			cout << "IN DAL NOYT NULL";
		while ((row = mysql_fetch_row(res))) {
			cout << "1=" << row[0];
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";
			s += "{\"activity_type\":\"" + s1 + "\"," + "\"duration\":\"" + row[1] + "\"start_at\":\"" + row[2] + "\"end_at\":\"" + row[3] + "\"}";
		}
		s += "]}";
		cout << "s=" << s;
	}
	wstring s1 = sfs.return_to_string_t(s);
	close_activity = json::value::string(s1);
	return close_activity;

}

void DAL:: dallocate_activity(MYSQL * conn, string activity, http_request request) {
	int state2 ,state1;
	json::value resp;
	cout << "INDAL" << activity;
	string query1 = "delete from activity_allocate where activity_id="+activity;
	string query2 = "update activities set status='INACTIVE' where activity_id=" + activity;
	 state1 = insert(conn, query1);
	 cout << state1;
	if(!state1)
		 state2 = insert(conn, query2);
	if (!state1 && !state2) {
		resp= json::value::string(U("Deallocated Activity"));
		request.reply(status_codes::OK, resp);
	}
	else {
		resp = json::value::string(U(" Bad Request"));
		request.reply(status_codes::NotFound, resp);
	}
}
json::value get_time_slots(MYSQL *conn, string query) {

	subfunc sfs;
	 	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value time_slot;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"activity_type\":\"" + s1 + "\"," + "\" Time\":\"" + row[1] +"-"+row[2]+ "\"," + "\" id\":\"" + row[3]+ "\"}";
		}
		s += "]}";

	}
	wstring s1 = sfs.return_to_string_t(s);
	time_slot = json::value::string(s1);
	return time_slot;
}


json::value get_all_employee(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value employees;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"empid\":\"" + s1 + "\"," + "\"Name\":\"" + row[1] +" " + row[2] + "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		employees = json::value::string(s1);
	}

	return employees;
}


json::value  get_role_user(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_create;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"Role Id\":\"" + s1 + "\"," + "\"Role name\":\"" + row[1] + "\"," + "\"User Id\":\"" + row[2] + "\"," + "\"Name\":\"" + row[3]  + "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		activity_create = json::value::string(s1);
	}

	return activity_create;
}

json::value get_all_acti_in_supervisor(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_create;
	const char *q = query.c_str();
	string s = "{\"data\":[",empid,name;
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		cout << "In";
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			//cout << "Row=" << row[0] << row[1] << row[2] << row[3] << row[4]<<endl;
			cout << "s1=" << s1;
			if (start == 1)
				start = 0;
			else
				s += ",";
			if (row[5] == NULL)
				empid = "Not assigned";
			else
				empid = row[5];

			if (row[6] == NULL)
				name = "Not assigned";
			else
				name = row[6];

				
			cout << "Before";
			s += "{ \"activity_name\":\"" + s1 + "\"," + "\" activity_id\":\"" + row[1] + "\"," + "\"activity_type\":\"" + row[2] + "\"," + "\"time_id\":\"" + row[3] + "\"," + "\"status\":\"" +row[4]+ "\"," + "\"empid\":\"" + empid + "\"," + "\"Name\":\"" + name+ "\"}";
		
		}
		s += "]}";
		
	}
	wstring s1 = sfs.return_to_string_t(s);
	activity_create = json::value::string(s1);
	return activity_create;
}

json::value  get_my_activities(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_create;
	const char *q = query.c_str();
	string s = "{\"data\":[",status;
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"activity_name\":\"" + s1 + "\"," + "\"activity_type\":\"" + row[1] + "\"," + "\"activity_status\":\"" + row[2] + "\"," + "\"cust_id\":\"" + row[3] + "\"," + "\"cust_name\":\"" + row[4] + "\"," + "\"address\":\"" + row[5] + "\"," + "\"city\":\"" + row[6] + "\"," + "\"phone\":\"" + row[7] + "\"}";
		}
		s += "]}";

	}
	wstring s1 = sfs.return_to_string_t(s);
	activity_create = json::value::string(s1);
	return activity_create;
}


json::value  get_allcustomers(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_create;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"cust_id\":\"" + s1 + "\"," + "\"cust_name\":\"" + row[1] + "\"," + "\"address\":\"" + row[2] + "\"," + "\"city\":\"" + row[3] + "\"," + "\"state\":\"" + row[4] + "\"," + "\"zipcode\":\"" + row[5] + "\"," + "\"phone\":\"" + row[6] + "\"," + "\"email\":\"" + row[7] + "\"}";
		}
		s += "]}";

	}
	wstring s1 = sfs.return_to_string_t(s);
	activity_create = json::value::string(s1);
	return activity_create;
}

json::value get_all_activty(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_create;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"activity_name\":\"" + s1 + "\"," + "\"activity_type\":\"" + row[1] + "\"," + "\"cust_id\":\"" + row[2] + "\"," + "\"cust_name\":\"" + row[3] + "\"," + "\"address\":\"" + row[4] + "\"," + "\"city\":\"" + row[5] + "\"," + "\"phone\":\"" + row[6] + "\"}";
		}
		s += "]}";
	
	}
	wstring s1 = sfs.return_to_string_t(s);
	activity_create = json::value::string(s1);
	return activity_create;
}

json::value  get_calendar(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value calendar;
	const char *q = query.c_str();
	string s = "{\"data\":[",reason;
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[1];
			if (start == 1)
				start = 0;
			else
				s += ",";
			if (row[3] == NULL) {
				reason = "null";
			}
			else
				reason = row[3];

			s += "{\"status\":\"" + s1 + "\"," + "\"date\":\"" + row[2] + "\"," + "\"reason\":\"" + reason  + "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		calendar = json::value::string(s1);
	}

	return calendar;
}

web::json::value getall_ativity_create_list(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_create;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"Activity ID\":\"" + s1 + "\"," + "\"Activity Type\":\"" + row[1] + "\"," + "\"Time slot\":\"" + row[2] + "\"," + "\"Customer Id\":\"" + row[3] + "\"," + "\"DispatcherComments\":\"" + row[4] + "\"," + "\"Amount\":\"" + row[5]+ +"\"," + "\"Status\":\"" + row[6] + "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		activity_create = json::value::string(s1);
	}

	return activity_create;

}
json::value getall_user_list(MYSQL *conn, string query,http_request request) {

	subfunc sfs;
	
	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;
	std::vector<web::json::value> arrayUsers;
	string name="",role_name="";
	json::value user;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			if (row[5] != NULL) {
				string super = row[5];
				string query = "select first_name,last_name from user_data where empid=" + super;
				MYSQL_ROW row1 = get_a_single_row(conn, query);
				string s1 = row1[0];
				string s2 = row1[1];
				name = s1 + " " + s2;

			}
			cout << "Before";
			string s1 = row[0];
			cout << s1;
			string query= "select role_name from role where role_id = (select role_id from role_assign where empid ="+s1+")";
			MYSQL_ROW row1 = get_a_single_row(conn, query);
			role_name = row1[0];
			cout << "role_name" << row1[0] << " nesxt:" << role_name;
			if (start == 1)
				start = 0;
			else
				s += ",";
			//s += ",{\"username\":" + s1 + ",\"" + "empid\":" + row[1] + ",\"" + "f_name\":" + row[2] + "," + "m_name\":" + row[3] + ",\"" + "l_name\":" + row[4] + ",\"" + "supervisor\":" + row[5] + "}";
			if(row[5]!=NULL)
				s += "{ \"empid\":\"" + s1 + "\"," + "\"f_name\":\"" + row[2] + "\","+ "\"m_name\":\"" + row[3] + "\"," + "\"l_name\":\"" + row[4] + "\"," + "\"supervisor\":\"" + name + "\"," + "\"role_name\":\"" + role_name +"\"}";
			else
				s += "{\"empid\":\"" + s1 + "\"," + "\"f_name\":\"" + row[2] + "\"," + "\"m_name\":\"" + row[3] + "\"," + "\"l_name\":\"" + row[4] + "\"," + "\"supervisor\":\"" + "" + "\"," + "\"role_name\":\"" + role_name + "\"}";

	}
		s += "]}";
	wstring s1 = sfs.return_to_string_t(s);
	user = json::value::string(s1);
		}
		request.reply(status_codes::OK,user );
	
json::value userss=json::value::string(U("hello"));
return userss;

}
json::value getall_ativity_allocate_list(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_allocate;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	string sub,sub1;
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";
			if (row[2] == NULL) 
				sub = "NULL";
			
			else
				sub = row[2];
			if (row[3] == NULL)
				sub1 = "NULL";

			else
				sub1 = row[2];
			s += "{\"Activity Id\":\"" + s1 + "\"," + "\"User Id\":\"" + row[1] + "\"," + "\"Start Date Time\":\"" +sub + "\"," + "\"End Date time\":\"" + sub1 + "\"," + "\"Requiered Inventory\":\"" + row[4] + "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		activity_allocate = json::value::string(s1);
	}

	return activity_allocate;

}
json::value getall_inventory_list(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10],unit;
	string serial;
	int start = 1;

	json::value inventories;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";
			
			

			s += "{\"Inventory Id\":\"" + s1 + "\"," + "\"Inventory Name\":\"" + row[1] + "\"," + "\"Serial Type\":\"" + row[2] + "\"," + "\"Unit\":\"" + row[3]  +"\"," + "\"serialno\":\"" + row[4]+ "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		inventories = json::value::string(s1);
	}

	return inventories;
}
json::value getall_ativity_type_list(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;
	
	json::value activity_types;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";
		
				s += "{\"Activity Type\":\"" + s1 + "\"," + "\"Activity Name\":\"" + row[1] + "\"," + "\"Duration\":\"" + row[2]  + "\"}";
			}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		activity_types = json::value::string(s1);
	}
	
	return activity_types;

}
vector<string>  getlist(MYSQL *conn,string query) {

	vector<string> list;
	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate,i=0;
	string a;
	const char *q = query.c_str();
	qstate = mysql_query(conn, q);
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			
			a = row[0];
			list.push_back(a);
		
				
		}
	}
	return list;

}



json::value get_work_skill(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_types;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	string ss1;
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";
			
				

			s += "{\"Skill Id\":\"" + s1 + "\"," + "\"Skill Name\":\"" + row[1] + "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		activity_types = json::value::string(s1);
	}

	return activity_types;
}

json::value getall_role_list(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_types;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	string ss1;
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";
			if (row[3] == NULL)
				ss1 = "NULL";
			else
				ss1 = row[3];
				
			s += "{\"Role Id\":\"" + s1 + "\"," + "\"Role Name\":\"" + row[1] + "\"," + "\"Descr\":\"" + row[2] +   "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		activity_types = json::value::string(s1);
	}

	return activity_types;
}

json::value getall_role_assign_list(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_types;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"User Id\":\"" + s1 + "\"," + "\"Role Id\":\"" + row[1] + "\"," + "\"Role Name\":\"" + row[2] + "\"," + "\"Start Date\":\"" + row[3] + "\"," + "\"End date\":\"" + row[4] + "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		activity_types = json::value::string(s1);
	}

	return activity_types;
}

json::value  get_empskills(MYSQL *conn, string query) {

	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_types;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"Skill Id\":\"" + s1  + "\"," + "\"Skill Name\":\"" +row[1]+ "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		activity_types = json::value::string(s1);
	}

	return activity_types;
}


json::value get_supervisor(MYSQL *conn, string query) {
	subfunc sfs;

	MYSQL_ROW row = NULL;
	MYSQL_RES *res;
	int qstate, i = 0;
	string a[10];
	int start = 1;

	json::value activity_types;
	const char *q = query.c_str();
	string s = "{\"data\":[";
	qstate = mysql_query(conn, q);
	cout << "qstate=" << qstate;
	if (!qstate) {
		res = mysql_store_result(conn);
		while ((row = mysql_fetch_row(res))) {
			string s1 = row[0];
			if (start == 1)
				start = 0;
			else
				s += ",";

			s += "{\"Empid\":\"" + s1 + "\"," + "\"Name\":\"" + row[1] +" "+row[2]+  "\"}";
		}
		s += "]}";
		wstring s1 = sfs.return_to_string_t(s);
		activity_types = json::value::string(s1);
	}

	return activity_types;
}



MYSQL_ROW  DAL:: login_DAL(MYSQL *conn,string id, string pass, http_request request) {
	subfunc sfs;
	string query = "select user_id,empid,first_name from user_data where user_id=(select user_id from user where user_id='" + id + "' and password='" + pass + "')";
	MYSQL_ROW row = get_a_single_row(conn, query);
	if (row) {
		std::string emp = row[1];
		std::string name = row[2];
		string query = "Select role_name from role where role_id in (select role_id from role_assign where empid= (select empid from user_data where user_id='" + id + "'))";
		 row = get_a_single_row(conn, query);
		if (row) {
			cout << "Row=" << row[0];
			err.set_Login_Error(0);//Ok
			web::json::value resp;
			std::string roles = row[0];
			

			std::wstring empid = sfs.return_to_string_t(emp);
			std::wstring role = sfs.return_to_string_t(roles);
			std::wstring user = sfs.return_to_string_t(id);
			std::wstring wname = sfs.return_to_string_t(name);

			resp[L"role_name"] = json::value::string(role);
			resp[L"user"] = json::value::string(user);
			resp[L"empid"] = json::value::string(empid);
			resp[L"name"] = json::value::string(wname);

			request.reply(status_codes::OK, resp); //send the reply as a json.
		}
			
			else {
				err.set_Login_Error(2);//no role_id
				json::value errorresp = json::value::string(U("Role Id not set"));
				request.reply(status_codes::NotFound, errorresp);
		}
	
			

	}
	else {
		err.set_Login_Error(1);//User_id password wrong
		json::value errorresp = json::value::string(U("Wrong Credentials"));
		request.reply(status_codes::NotFound, errorresp);
	}
	return row;

}
int DAL::create_user_DAL(MYSQL *conn, string f_name, string m_name, string l_name, string supervisor, string role_id, string start_date, string end_date, http_request request) {
	subfunc sfs;
	string query;
	
	int state1, state2;
	cout << "Before Inserting" << endl;
	cout << f_name << m_name << l_name << supervisor << endl;
	query = "INSERT INTO USER_DATA(first_name,middle_name,last_name,supervisor) values('" + f_name + "','" + m_name + "','" + l_name +"','"+ supervisor+ "')";
	state1=insert(conn, query);
	cout << "Insert state" << state1;
	if (!state1) {
		query = "select empid from user_data where empid=(select max(empid) from user_data)";
		MYSQL_ROW row = get_a_single_row(conn, query);

		string empid = row[0];
		string user, pass;
		user = pass = "USR" + empid;

		cout << "INDAL user_id= " << user << "pass= " << pass << endl;

		query = "INSERT INTO USER VALUES('" + user + "','" + pass + "')";
		state2 = insert(conn, query);


		if (!state2) {
			query = "UPDATE USER_DATA SET USER_ID='" + user + "' where empid=" + empid;
			insert(conn, query);
			query = "INSERT INTO role_assign VALUES('" + empid + "','" + role_id + "','" +start_date+"','" +end_date+ "')";
			cout << "emp:" << empid << "rolle:" << role_id << "start:" << start_date << "end:" << end_date;
			int state3=insert(conn, query);
			cout << "state3=" << state3;
			wstring val = sfs.return_to_string_t(empid);
			json::value okresp;
			okresp[L"empid"] = json::value::string(val);
			val = sfs.return_to_string_t(user);
			okresp[L"userid"] = json::value::string(val);
			okresp[L"pass"] = json::value::string(val);
			
			okresp[L"message"] = json::value::string(U("Created successfully"));
			request.reply(status_codes::OK, okresp);
		}
		else
		{
			json::value resp = json::value::string(U("User and password error"));
			query = " delete from user_data order by empid desc limit 1;";
			int state3=insert(conn, query);
			if (state3 != 0) {
				json::value resp = json::value::string(U("User and password error and deletion Error"));
				request.reply(status_codes::NotFound, resp);
			
			}
			
		}
	}
	else {
		json::value resp = json::value::string(U("Wrong Data"));
		request.reply(status_codes::NotFound, resp);
		}
	
	cout <<"state:"<< state2;
	return state2;
}
int DAL::create_role_DAL(MYSQL *conn, string role_name, string descr) {
	int state;
	string query = "INSERT INTO ROLE(role_name,descr)  VALUES('" + role_name + "','" +descr+ "')";
	state=insert(conn, query);
	return state;
}
int DAL::create_inventory_DAL(MYSQL *conn,  string inventory_name, string serial, string unit,string serialnos) {

	int state;
	cout << "Indal" << unit << serialnos;
	string query = "INSERT INTO INVENTORY (NAME,SERIALIZED_TYPE,UNIT,SERIALNO)  VALUES('" + inventory_name + "','" + serial + "',"+ unit+ "," + serialnos + ")";
	state = insert(conn, query);
	return state;
}

void DAL::assign_skill(MYSQL *conn, string empid, string skill_name, http_request request) {
	int state;
	string query = "INSERT INTO skill_allocate VALUES(" +empid+","+ skill_name + ")";
	state = insert(conn, query);
	if (!state) {
		json::value resp = json::value::string(U("Successfully assigned"));
		request.reply(status_codes::OK, resp); //send the reply as a json.
	}
	else {

			json::value resp = json::value::string(U("Bad Request"));
			request.reply(status_codes::NotFound, resp); //send the reply as a json.
	}
	cout << "CReate state" << state;

}
void DAL::get_emp_skill_DAL(MYSQL *conn, string empid, http_request request) {

	string query = " select skill_id,skill_name from work_skill where skill_id in (select skill_id from work_skill where skill_id not in(select skill_id from skill_allocate where empid="+empid+"))";
	json::value resp = get_empskills(conn, query);
	
		//json::value resp = json::value::string(U("Successfully assigned"));
		request.reply(status_codes::OK, resp); //send the reply as a json.
	
	
}
int DAL::create_workskill_DAL(MYSQL *conn, string skill_name) {
	int state;
	string query = "INSERT INTO WORK_SKILL (skill_name) VALUES('" +  skill_name + "')";
	state = insert(conn, query);
	cout << "CReate state" << state;
	return state;
}
int DAL::create_activitytype_DAL(MYSQL *conn,  string activity_name, string reqd_duration, string color_code, string skill_id) {
	int state;
	cout << "vlues=" << activity_name << reqd_duration << color_code<<skill_id;
	string query = "INSERT INTO ACTIVITY_TYPE(activity_name,duration,color_code,skill_id) VALUES('" +  activity_name + "'," + reqd_duration  + ",'" + color_code+ "','" + skill_id+"')";
	state = insert(conn, query);
	cout << "state=" << state;
	return state;

}
int DAL:: create_customer_DAL(MYSQL *conn,  string cust_name, string address, string city, string states, string zip_code, string phone, string email,http_request request) {
	subfunc sfs;
	int state;
	string query = "INSERT INTO CUSTOMER (name,address,city,state,zipcode,phone,email) VALUES('" + cust_name + "','" + address + "','" + city + "','" + states + "'," + zip_code +  "," + phone + ",'" + email + "')";
	state = insert(conn, query);
	query = "Select max(cust_id) from customer";
	MYSQL_ROW row = get_a_single_row(conn, query);
	string cust = row[0];
	wstring cust_id = sfs.return_to_string_t(cust);
	if (!state) {
		
		json::value resp = json::value::string(cust_id);
		request.reply(status_codes::OK, resp); //send the reply as a json.
	}
	else
		request.reply(status_codes::NotFound);
	return state;

}

int DAL::create_activity_DAL(MYSQL *conn, string activity_type, string time_slot, string dispatcher_comments, string amount, string cust_id, string status,string created_by, http_request request) {
	int state;
	string query = "INSERT INTO ACTIVITIES (activity_type,cust_id,dispatcher_comments,time_id,amount,status,created_by) VALUES('" + activity_type  + "'," + cust_id + ",'" + dispatcher_comments + "'," + time_slot + "," + amount + ",'INACTIVE" + "'," + created_by + ")";
	state = insert(conn, query);
	if (state == 0) {
		string query2 = "select max(activity_id) from activities";
		MYSQL_ROW row = get_a_single_row(conn, query2);
		string act_id = row[0];
		string act_name = "ACTIVITY" + act_id;
		string query3 = "INSERT INTO ACTIVITY_IDENTIFIER VALUES(" + act_id + ",'" + act_name + "')";
		int state = insert(conn, query3);
		json::value resp = json::value::string(U("Activity Created successfully:"));
		request.reply(status_codes::OK, resp); //send the reply as a json.
	}
	else {
		json::value resp = json::value::string(U("Error inserting :"));
		request.reply(status_codes::NotFound,resp);
	}
	return state;

}
int DAL::role_assign_DAL(MYSQL *conn, string user_id, string role_id, string start_date,string end_date) {
	int state;
	string query = "INSERT INTO ROLE_ASSIGN  VALUES('"+ user_id+"','"+ role_id + "','" + start_date+ "','" + end_date + "')";
	state = insert(conn, query);
	return state;
}
int DAL::create_attendance_DAL(MYSQL *conn, string user_id, string date, string status, string reason) {

	int state;
	cout << "DAL started:";
	string query1 = "select empid from attendance where empid=" + user_id + " and date='" + date + "'";
	MYSQL_ROW row = get_a_single_row(conn, query1);
	cout << "Row Dal=";
	
	if (row == NULL) {
		cout << "Inside DAL1";
		string query = "INSERT INTO attendance  VALUES('" + user_id + "','" + status + "','" + date + "','" + reason + "')";
		state = insert(conn, query);
	}
	else {
		cout << "Inside DAL2";
		state = 2;
	}
	return state;


}
vector <string> DAL ::getallusers(MYSQL *conn, string date,string empid){
	//string query = "select user_id from user_data as ud where ud.user_id in (select user_id from attendance where status='Present' and date='" + date + "') and user_id not in (select aa.user_id from activity_allocate as aa where aa.activity_id in(select ac.activity_id from activity_create as ac where status='INACTIVE'))";
	string query = "select empid from user_data as ud where ud.empid in (select empid from attendance where status='Present' and date='"+date+"') and empid in (select empid from user_data where supervisor="+empid+") and empid in (select empid from role where role_id in (select role_id from role where role_name='TECHNICIAN'))";
	vector<string> user = getlist(conn, query);
	cout << "size=" << user.size();
	cout << "Printing in Dal";
	/*for (int i = 0; i < user.size(); i++) {
		cout << "Users in Dal=" << user[i];
	}*/
	return user;
}

vector<string> DAL::getinactiveactivities(MYSQL *conn,string empid) {
	string query = "select activity_id from activities as ac where ac.status='Inactive' and created_by="+empid;
	vector<string> activity = getlist(conn, query);
	return activity;
}

int DAL::create_activity_allocate(MYSQL *conn, string activities, string users, string date, string reqd_inventory) {
	int state;
	string query = "INSERT INTO  ACTIVITY_ALLOCATE(activity_id,empid,start_date_time) VALUES('" + activities + "','" + users + "'," + "curdate()" + ")";
	string query2 = "UPDATE ACTIVITIES SET STATUS='INITIATED' WHERE ACTIVITY_ID='" + activities+"'";

	state = insert(conn, query);
	state = insert(conn, query2);
	return state;
}

json::value DAL::getuserdetails(MYSQL *conn,http_request request) {


	string query = "select * from user_data";
	web::json::value users=getall_user_list(conn, query,request);
	cout << "dal OUT";
	return users ;
}
json::value DAL::view_activity_type_DAL(MYSQL *conn) {
	string query = "select * from activity_TYPE ";
	web::json::value users = getall_ativity_type_list(conn, query);
	cout << "dal OUT";
	return users;
}

json::value DAL:: view_activity_create_DAL(MYSQL *conn) {
	string query = "select * from activities ";
	json::value users = getall_ativity_create_list(conn, query);
	cout << "dal OUT";
	return users;
}
json::value DAL::view_activity_allocate_DAL(MYSQL *conn) {
	string query = "select * from activity_allocate";
	json::value users = getall_ativity_allocate_list(conn, query);
	cout << "dal OUT";
	return users;
}
json::value DAL::view_role_DAL(MYSQL *conn) {
	string query = "select * from role";
	json::value users = getall_role_list(conn, query);
	cout << "dal OUT";
	return users;
}
json::value DAL::view_role_assign_DAL(MYSQL *conn) {
	string query = "select ra.user_id,ra.role_id,r.role_name,ra.start_date,ra.end_date from role_assign ra inner join role r on ra.role_id=r.role_id";
	json::value users = getall_role_assign_list(conn, query);
	cout << "dal OUT";
	return users;
}
json::value DAL::view_inventories_DAL(MYSQL *conn){
	string query = "select * from inventory i where i.inventory_id not in (select inventory_id from inventory_alloc)";
	json::value users = getall_inventory_list(conn, query);
	cout << "dal OUT";
	return users;
}
json::value DAL:: view_assigned_activity_DAL(MYSQL *conn,string user_id,string status) {
	cout << "user_id=" << user_id;
	string query1 ="select ai.activity_name,a.activity_name,c.cust_id,c.name,c.address,c.city,c.phone from activity_TYPE a inner join activities ac on a.activity_type=ac.activity_type inner join  activity_allocate aa on ac.activity_id=aa.activity_id inner join customer c on c.cust_id=ac.cust_id inner join activity_identifier ai on aa.activity_id =ai.activity_id where aa.empid="+user_id+ " and ac.status='"+status+"'";

	json::value activity = get_all_activty(conn, query1);
	//MYSQL_ROW row = get_a_single_row(conn, query1);
	//wcout << "Row=" << row[0];
	cout << "dal OUT";
	return activity;
}
int DAL:: mark_activity_status_DAL(MYSQL *conn, string activity_id, string status) {

	int state;
	string query = "UPDATE ACTIVITIES SET STATUS='"+status+"' WHERE ACTIVITY_ID='"+ activity_id+"'";
	state = insert(conn, query);
	return state;
}
int DAL::create_internal_activity_DAL(MYSQL *conn,string user_id, string int_activity, string duration) {

	int state;
	string query = "INSERT INTO Internal_activity values('"+user_id+"','"+int_activity+"','"+duration+"')";
	state = insert(conn, query);
	return state;
}
json::value DAL::view_closed_activities(MYSQL *conn) {
	
	string query = "select activity_id,user_id from activity_allocate where activity_id in (select activity_id from activities where status='CLOSE')";
	json::value state = get_close_val(conn,query);
	return state;
}

MYSQL_ROW DAL:: search_user_DAL(MYSQL *conn, string user) {
	string query = "select empid,first_name,middle_name,last_name,supervisor from user_data where empid='"+user+"'";
	MYSQL_ROW state =get_a_single_row(conn, query);
	return state;
}
json::value DAL:: search_user_role_DAL(MYSQL *conn, string user) {
	string query = "select ra.role_id,r.role_name,u.empid,u.first_name from role_assign ra inner join role r  inner join user_data u on ra.role_id=r.role_id and ra.user_id=u.user_id  where r.role_name='"+user+"'";
	json::value state = get_role_user(conn, query);
	return state;
}
MYSQL_ROW DAL::search_single_user_role_DAL(MYSQL *conn, string user) {
	string query = "select ra.role_id,r.role_name,u.empid,u.first_name from role_assign ra inner join role r  inner join user_data u on ra.role_id=r.role_id and ra.user_id=u.user_id  where u.empid='"+user+"'";
	MYSQL_ROW state = get_a_single_row(conn, query);
	return state;
}

MYSQL_ROW DAL::search_activity_DAL(MYSQL *conn, string activity){
	string query = "select ac.activity_id,ac.activity_type,ac.status,u.empid,u.first_name from activities ac left join activity_allocate aa on ac.activity_id=aa.activity_id left join user_data u on aa.user_id=u.user_id where ac.activity_id='"+activity+"'";
	MYSQL_ROW state = get_a_single_row(conn, query);
	return state;
	}

json::value DAL:: view_calendar_DAL(MYSQL *conn, string user_id) {
	string query = "select * from attendance where empid=" + user_id ;
	json::value state = get_calendar(conn, query);
	return state;
}

json::value DAL:: view_work_skill_DAL(MYSQL *conn) {
	string query = "select * from work_skill";
	json::value state = get_work_skill(conn, query);
	return state;
}

void DAL::get_all_supervisors_DAL(MYSQL *conn,http_request request ) {
	string query = "select empid,first_name,last_name from user_data where empid in (select empid from role_assign where role_id in (select role_id from role where role_name='ADMIN' or role_name='SUPERVISOR'))";
	json::value state = get_supervisor(conn, query);

	request.reply(status_codes::OK, state);
}

void DAL::view_activity_in_super_DAL(MYSQL *conn, string supervisor, string status, http_request request) {

	string query = "SELECT AI.ACTIVITY_NAME,AC.ACTIVITY_TYPE,A.ACTIVITY_NAME,ac.time_id,AC.STATUS,UD.EMPID,UD.FIRST_NAME,UD.LAST_NAME FROM ACTIVITIES AC LEFT JOIN ACTIVITY_ALLOCATE AA ON AC.ACTIVITY_ID=AA.ACTIVITY_ID LEFT JOIN USER_DATA UD ON AA.EMPID=UD.EMPID INNER JOIN ACTIVITY_TYPE A ON A.ACTIVITY_TYPE=AC.ACTIVITY_TYPE INNER JOIN ACTIVITY_IDENTIFIER AI ON AC.ACTIVITY_ID=AI.ACTIVITY_ID WHERE AC.STATUS='"+status+"' AND AC.CREATED_BY="+supervisor;
	json::value state = get_all_acti_in_supervisor(conn, query);
	wcout <<"Dal"<< state;
	request.reply(status_codes::OK, state);

}

void DAL::get_activity_id(MYSQL *conn,string activity_name, http_request request) {
	subfunc sfs;
	string query = "SELECT activity_id from activity_identifier where activity_name='"+ activity_name+"'";
	MYSQL_ROW row = get_a_single_row(conn, query);
	if (row != NULL) {
		string name = row[0];
		wstring nam = sfs.return_to_string_t(name);
		json::value resp;
		resp[L"activity_id"] = json::value::string(nam);
		request.reply(status_codes::OK, resp);
	}
	else {
		request.reply(status_codes::NotFound);
	}
}


void DAL:: get_employees_DAL(MYSQL *conn, string empid, http_request request) {
	string query = "select empid,first_name,last_name from user_data where supervisor=" + empid;
	json::value state = get_all_employee(conn, query);
	wcout << "Dal" << state;
	request.reply(status_codes::OK, state);
}
void DAL::view_my_activities(MYSQL *conn, string empid, http_request request) {
	string query = "select ai.activity_name,a.activity_name,ac.status,c.cust_id,c.name,c.address,c.city,c.phone from activity_TYPE a inner join activities ac on a.activity_type=ac.activity_type inner join  activity_allocate aa on ac.activity_id=aa.activity_id inner join customer c on c.cust_id=ac.cust_id inner join activity_identifier ai on aa.activity_id =ai.activity_id where aa.empid=" + empid;
		json::value state = get_my_activities(conn, query);
	wcout << "Dal" << state;
	request.reply(status_codes::OK, state);
}

MYSQL_ROW DAL::get_last_serial(MYSQL *conn) {

	string query = "select max(serialno) from inventory";
	MYSQL_ROW row = get_a_single_row(conn, query);
	return row;

}

void DAL::allocate_inventory(MYSQL *conn, string empid, string inventory_id, string serial_no, string unit, http_request request) {

	string query = "insert into inventory_alloc values("+ inventory_id +","+empid+","+serial_no+"," +  unit+")";
	int state = insert(conn, query);
	if (state == 0)
	{
		json::value resp = json::value::string(U("Value Inserted"));
		request.reply(status_codes::OK, resp);
	}
	else {
		json::value resp = json::value::string(U("Data Error"));
		request.reply(status_codes::NotFound, resp);
	}
	
}

void DAL::view_customers(MYSQL *conn,http_request request) {
	string query = "select * from customer";
	json::value state = get_allcustomers(conn, query);
	//wcout << "Dal" << state;
	request.reply(status_codes::OK, state);
}

MYSQL_ROW DAL::get_last_activity_type(MYSQL *conn) {
	string query = "select max(activity_type) from activity_TYPE";
	MYSQL_ROW row = get_a_single_row(conn, query);

	return row;

}

int DAL::insert_time_slots(MYSQL *conn,string activity_type, string start_time, string end_time) {
	cout << "IN DAL VALUES:" << activity_type << start_time << end_time;
	string query = "insert into time_slots(activity_type,start_at,end_at) values('" + activity_type + "','" + start_time + "','" + end_time + "')";
	int state = insert(conn, query);
	cout << "In dal:" << state << endl;
	return state;
}
void DAL::get_time_slot(MYSQL *conn, string activity_type, http_request request) {

	string query = "select * from time_slots where activity_type=" + activity_type;
	json::value resp = get_time_slots(conn, query);

	request.reply(status_codes::OK, resp);
}
vector<web::json::value> DAL::get_user_status(MYSQL *conn, string user) {
	json::value resp;
	string query= "select aa.empid, aa.activity_id, a.activity_type, ts.start_at, ts.end_at from activity_allocate aa inner join activities ac on aa.activity_id = ac.activity_id inner join activity_TYPE a on ac.activity_type = a.activity_type inner join time_slots ts on ac.activity_type = ts.activity_type and ts.time_id = ac.time_id where aa.empid ="+user;	
	vector<web::json::value>result = get_result(conn, query);
	return result;
}
MYSQL_ROW DAL::get_activity_status(MYSQL *conn,string activity) {
	json::value resp;
	cout << "activity in dal" << activity;
	string query = "select start_at,end_at,time_id from time_slots where time_id = (select time_id from activities where activity_id="+activity+")";
	MYSQL_ROW row = get_a_single_row(conn, query);
	return row;
}

MYSQL_ROW DAL:: get_act_skill_id(MYSQL * conn, string activity) {
	string query = "select skill_id from activity_type where activity_type=(select activity_type from activities where activity_id=" + activity + ")";
	MYSQL_ROW row = get_a_single_row(conn,query);
	return row;
}
vector<web::json::value>DAL::get_user_skill_id(MYSQL * conn, string user) {
	string query = "select skill_id from skill_allocate where empid=" + user ;
	vector<web::json::value> resp = get_skill(conn, query);
		return resp;
	
}
MYSQL_ROW DAL:: get_act_timers(MYSQL * conn,string act_id) {
	string query = "select start_at,end_at  from time_slots where time_id =(select time_id from activities where activity_id=" +act_id+")";
	MYSQL_ROW row = get_a_single_row(conn, query);
	return row;
}

MYSQL_ROW DAL:: get_my_details(MYSQL *conn, string empid) {
	string query = "select first_name,last_name from user_data where empid="+empid;
	MYSQL_ROW row = get_a_single_row(conn, query);
	return row;
}
void DAL::view_my_skills(MYSQL * conn,string empid, http_request request) {

	string query = "select skill_name from work_skill where skill_id in (select skill_id from skill_allocate where empid=" + empid+")";
	json::value resp = get_my_skills(conn, query, request);
	request.reply(status_codes::OK, resp);

}

/*void DAL::update_user_dal(MYSQL *conn, string empid, string old_username, string new_username, http_request request) {
	string query = "update user set user_id='" + new_username + "' where user_id='" + old_username + "'";
	int qstate = insert(conn, query);
	if (qstate == 0) {
		string query = "update user set user_id='" + new_username + "' where user_id='" + old_username + "'";
	}

}*/