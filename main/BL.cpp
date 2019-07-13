#include "BL.h" // header in local directory
#include <iostream> // header in standard library
#include<string> // header in local directory
#include "DAL.h"
#include "cpprest/json.h"
#include <time.h>
#include<ctime>



using namespace bl;
using namespace std;
using namespace sf;
using namespace dal;
using namespace json;



DAL dals;
subfunc sfs;

json::value BL:: extract_request(http_request request) {
	json::value temp;
	string tmp;




	request.extract_json()
		.then([&temp](pplx::task<json::value> task)
	{
		
		temp = task.get();
		

	})
		.wait();
	return temp;
}

void BL::handle_login(http_request request) {
	MYSQL_ROW row;
	string url;
	string usersss;
	wcout << "Enterd login handle";
	json::value temp;
	
	temp = extract_request(request);//get request in json
	wcout << "IN handler:"<<temp;
	utility::string_t s;
	s = temp.at(U("user")).as_string();
	string id = sfs.return_to_string(s);
	s = temp.at(U("pass")).as_string();
	string name = sfs.return_to_string(s);
	cout << "out of BL userid=" << id << "Pass=" << name;
	MYSQL *conn = dals.connect();
	row = dals.login_DAL(conn,id, name,request);
	

}

int BL::handle_user_create(http_request request) {

	cout << "In BL";
	json::value temp;
	json::value inventory;
	vector <string> invent;
	string inventory_types[100] = {""},sss;
	int state;
	string empid,f_name, m_name, l_name,userid="",password,supervisor,role_id,start_date,end_date;

	temp = extract_request(request);//get request in json
	utility::string_t s;
	
	s = temp.at(U("f_name")).as_string();
	f_name = sfs.return_to_string(s);
	cout << f_name;
	s = temp.at(U("m_name")).as_string();
	m_name = sfs.return_to_string(s);
	cout << m_name;
	s = temp.at(U("l_name")).as_string();
	l_name = sfs.return_to_string(s);
	cout << l_name;
	s= temp.at(U("supervisor")).as_string();
	supervisor = sfs.return_to_string(s);
	s= temp.at(U("role_id")).as_string();
	role_id = sfs.return_to_string(s);
	s = temp.at(U("start_date")).as_string();
	start_date = sfs.return_to_string(s);
	s = temp.at(U("end_date")).as_string();
	end_date = sfs.return_to_string(s);


	MYSQL *conn = dals.connect();
	state=dals.create_user_DAL(conn,  f_name, m_name, l_name, supervisor,role_id,start_date,end_date,request);
	return state;

	
}

int BL::handle_role_create(http_request request) {
	cout << "In BL";
	json::value temp;
	int state;
	string role_id, role_name, descr,shift;

	temp = extract_request(request);//get request in json
	utility::string_t s;


	s = temp.at(U("role_name")).as_string();
	role_name = sfs.return_to_string(s);

	s = temp.at(U("descr")).as_string();
	descr = sfs.return_to_string(s);

	

	wcout << "out";
	
	MYSQL *conn = dals.connect();
	state=dals.create_role_DAL(conn, role_name,descr);
	return state;

}

int BL::handle_inventory_create(http_request request) {
	cout << "In BL";
	json::value temp;
	int state;
	string inventory_id,inventory_name,serial,unit,serialno="";
	int  serialnos;
	temp = extract_request(request);//get request in json
	utility::string_t s;


	s = temp.at(U("name")).as_string();
	inventory_name = sfs.return_to_string(s);

	s = temp.at(U("serialized")).as_string();
	serial = sfs.return_to_string(s);

	s = temp.at(U("unit")).as_string();
	unit = sfs.return_to_string(s);




	

	
		cout << "IN BL";
		MYSQL *conn = dals.connect();
		if (serial == "serial") {
			MYSQL_ROW row = dals.get_last_serial(conn);
			string tempp = row[0];
			cout <<"Row"<< row[0] << tempp;
			serialnos = stoi(tempp);
			cout << "to int" << serialnos;
			serialnos += 1;
			serialno = to_string(serialnos);
			cout <<"final"<< serialno;
			unit = "0";

		}
		else {
			serialno = "0";
		}
		state = dals.create_inventory_DAL(conn, inventory_name, serial, unit,serialno);


return state;

}

int BL::handle_activitytype_create(http_request request) {
	cout << "In BL createtype";
	json::value temp;
	int state=1,i;
	string activity_type, activity_name, reqd_duration, color_code,time_slots,skill_id;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	//s = temp.at(U("activity_type")).as_string();
	///activity_type = sfs.return_to_string(s);
	std::ostringstream strs;
	s = temp.at(U("activity_name")).as_string();
	activity_name = sfs.return_to_string(s);
	cout << activity_name;

	s = temp.at(U("reqd_duration")).as_string();
	reqd_duration = sfs.return_to_string(s);
	cout << "reqd" << reqd_duration;
	double nr = temp.at(U("color_code")).at(U("_r")).as_double();
	//string r = sfs.return_to_string(s);
	cout << "red";
	double ng = temp.at(U("color_code")).at(U("_g")).as_double();
	
	double nb = temp.at(U("color_code")).at(U("_b")).as_double();
	//string b = sfs.return_to_string(s);
	double na = temp.at(U("color_code")).at(U("_a")).as_double ();
	
	strs << na;
	std::string a  = strs.str();
	cout << "a=" << a;
	strs << nb;
	std::string b = strs.str();
	strs << ng;
	std::string g = strs.str();
	strs << nr;
	std::string r = strs.str();


	color_code = "{\"r\":" + r + ",\"g\":" + g + ",\"b\"" + b + ",\"a\":" + a + "}";
	cout << color_code;


	s = temp.at(U("skill_id")).as_string();
	skill_id = sfs.return_to_string(s);


	cout << "Out Bl<";
		MYSQL *conn = dals.connect();
		state = dals.create_activitytype_DAL(conn, activity_name, reqd_duration, color_code,skill_id);
		MYSQL_ROW row = dals.get_last_activity_type(conn);
		 activity_type = row[0];
		 cout << "activityid"<<activity_type;
		 auto st = temp.at(U("start_time")).as_array();
		 auto et = temp.at(U("end_time")).as_array();
		 int state1 = 1;
		 if (!state) {
			 for (i = 0; i < st.size(); i++) {

				 s = st[i].as_string();
				 string start = sfs.return_to_string(s);
				 s = et[i].as_string();
				 string end = sfs.return_to_string(s);
				 cout << "staert" << start << "end" << end;
				 state1 = dals.insert_time_slots(conn, activity_type, start, end);
				 cout << "qstaate2" << state1;
			 }
		 }
	return state1;

}

void BL:: get_time_slots(http_request request) {
	cout << "In BL";
	json::value temp;

	string skill_id, activity_type;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("activity_type")).as_string();
	activity_type = sfs.return_to_string(s);

	MYSQL *conn = dals.connect();
	 dals.get_time_slot(conn, activity_type,request);


}


int BL::handle_workskill_create(http_request request) {
	cout << "In BL";
	json::value temp;
	int state;
	string skill_id,skill_name;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	//s = temp.at(U("skill_id")).as_string();
	//skill_id = sfs.return_to_string(s);

	s = temp.at(U("skill_name")).as_string();
	skill_name = sfs.return_to_string(s);
	cout << "BL_OUT";

		MYSQL *conn = dals.connect();
		state = dals.create_workskill_DAL(conn, skill_name);
	

	return state;

}


void BL::assign_work_skill(http_request request) {

	cout << "In BL assign";
	json::value temp;

	string empid, skill_name;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	//s = temp.at(U("skill_id")).as_string();
	//skill_id = sfs.return_to_string(s);

	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);
	cout << "empid" << empid;
	s = temp.at(U("skill_id")).as_string();
	skill_name = sfs.return_to_string(s);
	cout << "empid" << skill_name;
	cout << "BL_OUT";

	MYSQL *conn = dals.connect();
	dals.assign_skill(conn, empid,skill_name,request);


}

void BL:: get_emp_skills(http_request request) {
	cout << "In BL assign";
	json::value temp;

	string empid, skill_name;

	temp = extract_request(request);//get request in json
	utility::string_t s;



	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);

		cout << "BL_OUT";

	MYSQL *conn = dals.connect();
	dals.get_emp_skill_DAL(conn, empid, request);
}
int BL::handle_customer_create(http_request request) {
	cout << "In BL customer";
	json::value temp;
	int state;
	string cust_id, cust_name,address,city,states,zip_code,phone,email;

	temp = extract_request(request);//get request in json
	utility::string_t s;


	s = temp.at(U("cust_name")).as_string();
	cust_name = sfs.return_to_string(s);

	s = temp.at(U("address")).as_string();
	address = sfs.return_to_string(s);

	s = temp.at(U("city")).as_string();
	city = sfs.return_to_string(s);

	s = temp.at(U("state")).as_string();
	states = sfs.return_to_string(s);

	s = temp.at(U("zip_code")).as_string();
	zip_code = sfs.return_to_string(s);

	s = temp.at(U("phone")).as_string();
	phone = sfs.return_to_string(s);

	s = temp.at(U("email")).as_string();
	email = sfs.return_to_string(s);

	MYSQL *conn = dals.connect();
	state = dals.create_customer_DAL(conn,  cust_name, address, city, states, zip_code, phone, email,request);


	return state;

}


int BL:: role_assign(http_request request) {
	cout << "In BL_role";
	json::value temp;
	int state;
	string role_id, user_id, start_date, end_date;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	

	s = temp.at(U("empid")).as_string();
	user_id = sfs.return_to_string(s);
	user_id = "USR" + user_id;
	cout << "userid=" << user_id;

	s = temp.at(U("role_id")).as_string();
	role_id = sfs.return_to_string(s);
	cout << "roleid=" << role_id;

	s = temp.at(U("start_date")).as_string();
	start_date = sfs.return_to_string(s);
	cout << "start=" << start_date;

	s = temp.at(U("end_date")).as_string();
	end_date = sfs.return_to_string(s);
	cout << "end=" << end_date;

		MYSQL *conn = dals.connect();
		state = dals.role_assign_DAL(conn, user_id, role_id, start_date, end_date);
	
	return state;
}

int BL::handle_activity_create(http_request request) {
	
	cout << "In BL_activity";
	json::value temp;
	int state;
	string activity_id,activity_type,time_slot,dispatcher_comments,amount,cust_id,status;

	temp = extract_request(request);//get request in json
	utility::string_t s;



	s = temp.at(U("activity_type")).as_string();
	activity_type = sfs.return_to_string(s);
	cout << "activity_type" << activity_type;
	s = temp.at(U("time_slot")).as_string();
	time_slot = sfs.return_to_string(s);
	cout << "time_slot"<<time_slot;
	s = temp.at(U("cust_id")).as_string();
	cust_id = sfs.return_to_string(s);
	cout << "cust_id"<<cust_id;
	s = temp.at(U("created_by")).as_string();
	string created_by = sfs.return_to_string(s);
	cout << "created_by"<<created_by;
	s = temp.at(U("dispatcher_comments")).as_string();
	dispatcher_comments = sfs.return_to_string(s);
	cout << dispatcher_comments;
	s = temp.at(U("amount")).as_string();
	amount = sfs.return_to_string(s);
	cout << amount;
	status = "INACTIVE";

	
	MYSQL *conn = dals.connect();
	state = dals.create_activity_DAL(conn, activity_type, time_slot, dispatcher_comments, amount, cust_id, status,created_by,request);
	cout << "IN BL state=" << state;
	return state;
}

int BL::handle_mark_attendance(http_request request) {

	
	cout << "In BL_attnd";
	json::value temp;
	int state=1;
	string user_id,date,status,reason;

	temp = extract_request(request);//get request in json
	utility::string_t s;



	s = temp.at(U("empid")).as_string();
	user_id = sfs.return_to_string(s);
	cout << user_id;
	s = temp.at(U("date")).as_string();
	date = sfs.return_to_string(s);
	cout << date;
	s = temp.at(U("status")).as_string();
	status = sfs.return_to_string(s);
	cout << status;
	s = temp.at(U("reason")).as_string();
	reason = sfs.return_to_string(s);
	cout << reason;
	cout << "After";


	MYSQL *conn = dals.connect();
	state = dals.create_attendance_DAL(conn,user_id,date,status,reason);
	cout << "IN BL state=" << state;
	return state;

}


int BL:: StringToTime(std::string time_24h) {

	time_t theTime = time(NULL);
	


	std::string delimiter = ":";

	size_t pos = 0;
	std::string token;
	int hr, min,sec, time;
	while ((pos = time_24h.find(delimiter)) != std::string::npos) {
		token = time_24h.substr(0, pos);
		 hr = atoi(token.c_str());
		time_24h.erase(0, pos + delimiter.length());

		token = time_24h.substr(0, pos);
		 min = atoi(token.c_str());
		time_24h.erase(0, pos + delimiter.length());

		
	}
	sec = atoi(time_24h.c_str());

	time = hr * 60 * 60 + min * 60 + sec;
	return  time;

}

int check_user_status(MYSQL *conn,string user,int act_start,int act_end) {
	BL bl;
	vector<web::json::value> result;
	utility::string_t s;
	int check_flag = 1;
	result = dals.get_user_status(conn, user);
	if (result.size() == 0) {
		cout << "No activities for " << user;
		check_flag = 2;
	}
	
	for (int i = 0; i < result.size(); i++) {
		s = result[i].at(U("start_time")).as_string();
		string usst = sfs.return_to_string(s);
		s = result[i].at(U("end_time")).as_string();
		string uset = sfs.return_to_string(s);
		int start_t = bl.StringToTime(usst);
		int end_t = bl.StringToTime(uset);

		cout << "\nUSER:"<<user<<" "<<"User Time:" << " Start:" << usst << " " << start_t << " End Time:" << uset << " " << end_t<<"\n";
		if (act_end>start_t && act_start<end_t) {
			check_flag = 0;
			break;
		}

	}
	return check_flag;
}

int BL::activity_assign(http_request request) { 
	
	cout << "In BL_assign";
	BL bl;
	json::value temp;
	int state=0,allocate_count=0;
	string empid, date, status, reason,reqd_inventory;
	
	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("date")).as_string();
	date = sfs.return_to_string(s);

	//s = temp.at(U("reqd_inventory")).as_string();
	//reqd_inventory = sfs.return_to_string(s);

	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);

	MYSQL *conn = dals.connect();
	vector <string> users = dals.getallusers(conn,date,empid);
	cout << "Printing in BL:Users are";

	if (users.size() == 0) {
		cout << "0";
		json::value resp = json::value::string(U("No users present"));
		request.reply(status_codes::NotFound, resp);
	}
	else
		cout << users.size();
	vector <string> activities = dals.getinactiveactivities(conn,empid);
	cout << "size_activity=" << activities.size();
	if (activities.size() == 0) {
		json::value resp = json::value::string(U("No activities present"));
		request.reply(status_codes::NotFound, resp);
	}
	
	int j = -1,allocate_flag=1,check_flag=1,k;
	string user_start_arr[100], user_end_arr[100];
	
	int actflag = 0;
	
	if (users.size() != 0 && activities.size() != 0) {
		for (int i = 0; i < activities.size(); i++) {
			cout << "\n\n\n";
			MYSQL_ROW row1= dals.get_activity_status(conn,activities[i]);

			string st = row1[0];
			string et = row1[1];
			
			int user_assigned_count = 0;
			int act_start = bl.StringToTime(st);
			int act_end = bl.StringToTime(et);
			cout << "start:" << st << " " << act_start << " end:" << et << " " << act_end << "\n";
				int actflag = 0;
			MYSQL_ROW reqd_skill = dals.get_act_skill_id(conn, activities[i]);
			string act_skill = reqd_skill[0];
			cout << "act_skills" << act_skill;
			allocate_flag = 1;
			if (j == users.size() - 1)
				j = 0;
			else
				j += 1;

			cout << "\n\nusersize" << users.size() << "j=" << j << "user=" << users[j] << "activity=" << activities[i] << "\n";
			cout << "Activity_time" << st << " " << act_start << " "<<et<<" "<<act_end<<"\n";
				k = 0;
				while (allocate_flag == 1 && k < users.size()) {
					actflag = 0;
					check_flag = check_user_status(conn, users[k], act_start,act_end);
					vector<web::json::value> user_skill = dals.get_user_skill_id(conn, users[k]);
					cout << "user_skillsize=" << user_skill.size();
					for (int l = 0; l < user_skill.size(); l++) {
						s = user_skill[l].at(U("skill_id")).as_string();
						string usrskill = sfs.return_to_string(s);
						cout << "act_skilling" << usrskill << " " << act_skill;
						if (usrskill == act_skill) {
							actflag = 1;
						}
						cout << "actflag=" << actflag;
					}
					if (check_flag == 2) {
						cout << "No activities for user:";
						if (actflag == 1) {
							state = dals.create_activity_allocate(conn, activities[i], users[k], date, reqd_inventory);
							cout << state;
							allocate_flag = 0;
							allocate_count += 1;
						}
						else {
							allocate_flag = 1;
							k += 1;
							if (k >= users.size())
								break;
						}
						
					}
					else if (check_flag == 1) {
						cout << "In if";
						cout << activities[i] << users[k];
						allocate_flag = 0;
						if (actflag == 1) {
							state = dals.create_activity_allocate(conn, activities[i], users[k], date, reqd_inventory);
							cout << state;
							allocate_flag = 0;
							allocate_count += 1;
						}
						else {
							allocate_flag = 1;
							k += 1; k += 1;
							if (k >= users.size())
								break;
						}
					
					}
					else {
			
						k  += 1;
						if (k >= users.size())
							break;
						cout << "NOT user:" << users[k]<<" k="<<k<<"\n";
					}
			}
				cout << "\nOutside while\n";
				cout << "i=" << i;
		}

		state = int(activities.size());
	}
		return allocate_count;

}

void BL::create_route(http_request request) {

	
	cout << "In BL_route";
	json::value temp;
	int state = 0, allocate_count = 0;
	string activity_id, time_id, status, reason, reqd_inventory, date, empid;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("date")).as_string();
	date = sfs.return_to_string(s);
	cout << "Date=" << date;
	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);
	cout << "empid=" << empid;
	s = temp.at(U("activity_id")).as_string();
	activity_id = sfs.return_to_string(s);
	cout << "actiivty_id=" << activity_id;

	MYSQL *conn = dals.connect();

	state = dals.create_activity_allocate(conn, activity_id, empid, date, reqd_inventory);
	if (!state) {
		json::value resp = json::value::string(U("Routed Successfully"));
		request.reply(status_codes::OK, resp);
	}
	else {
		json::value resp = json::value::string(U("Not Found"));
		request.reply(status_codes::NotFound, resp);
	}
}


void BL::get_user_data_for_manual_routiung(http_request request) {
	
	cout << "In BL_assign";
	BL bl;
	json::value temp;
	int state = 0, allocate_count = 0;
	string activity_id, time_id, status, reason, reqd_inventory,date,empid;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("date")).as_string();
	date = sfs.return_to_string(s);


	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);
	s = temp.at(U("activity_id")).as_string();
	activity_id = sfs.return_to_string(s);

	

	/*s = temp.at(U("time_id")).as_string();
	time_id = sfs.return_to_string(s);*/



	MYSQL *conn = dals.connect();


	MYSQL_ROW reqd_skill = dals.get_act_skill_id(conn, activity_id);
	string act_skill = reqd_skill[0];

	MYSQL_ROW row = dals.get_act_timers(conn,activity_id);

	string start = row[0];
	string end = row[1];
	
	int act_start = bl.StringToTime(start);
	int act_end = bl.StringToTime(end);
	cout << "activity_start_time=" << start <<" "<<act_start<< "activity_end_time=" << end<<" "<<act_end<<endl;
	int actflag=0;
	vector <string> users = dals.getallusers(conn, date, empid);
	string str = "{\"data\":[";
	int starts = 1;
	for (int i = 0; i < users.size(); i++) {
		int check_flag = check_user_status(conn, users[i], act_start, act_end);
		cout << "\ncheckflag=" << check_flag;
		
		vector<web::json::value> user_skill = dals.get_user_skill_id(conn, users[i]);
		cout << "user_skillsize=" << user_skill.size();
		
		for (int l = 0; l < user_skill.size(); l++) {
			
			s = user_skill[l].at(U("skill_id")).as_string();
			string usrskill = sfs.return_to_string(s);
			cout << "act_skilling" << usrskill << " " << act_skill;
			if (usrskill == act_skill) {
				actflag = 1;
			}
			cout << "actflag=" << actflag;
		}

		if (check_flag == 2) {
			cout << "No activities for user:";
			if (actflag == 1)
			{
				MYSQL_ROW row1 = dals.get_my_details(conn, users[i]);
				string f_name = row1[0];
				string l_name = row1[1];
				string name = f_name + " " + l_name;
				if (starts== 1)
					starts = 0;
				else
					str += ",";
				str += "{\"userId\":\"" + users[i] + "\",\"Name\":\"" + name + "\"}";
			}

		}
		else if (check_flag == 1) {
			cout << "In else if";
			MYSQL_ROW row1 = dals.get_my_details(conn, users[i]);
			string f_name = row1[0];
			string l_name = row1[1];
			string name = f_name + " " + l_name;

			if (actflag == 1) {
				if (starts == 1)
					starts = 0;
				else
					str += ",";
				str += "{\"userId\":\"" + users[i] + "\",\"Name\":\"" + name + "\"}";
			}

		}
	}
	str += "]}";
	wstring s1 = sfs.return_to_string_t(str);
	json::value resp = json::value::string(s1);
	request.reply(status_codes::OK, resp);

}


void BL::return_activity_id_for_manual_routing(http_request request) {
	cout << "In BL_assign";
	BL bl;
	json::value temp;
	int state = 0, allocate_count = 0;
	string activity_id, time_id, status, reason, reqd_inventory, date, empid;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	/*s = temp.at(U("date")).as_string();
	date = sfs.return_to_string(s);


	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);*/
	s = temp.at(U("activity_id")).as_string();
	activity_id = sfs.return_to_string(s);

	/*s = temp.at(U("time_id")).as_string();
	time_id = sfs.return_to_string(s);*/

	MYSQL *conn = dals.connect();
	MYSQL_ROW reqd_skill = dals.get_act_skill_id(conn, activity_id);
	string act_skill = reqd_skill[0];

	vector <string> users = dals.getallusers(conn, date, empid);

	MYSQL_ROW row = dals.get_act_timers(conn, activity_id);

	string start = row[0];
	string end = row[1];

	int act_start = bl.StringToTime(start);
	int act_end = bl.StringToTime(end);
	
	

}
void BL::deallocate_activity(http_request request) {
	
	cout << "In BL_assign";
	json::value temp;
	int state = 0, allocate_count = 0;
	string activity_id, time_id, status, reason, reqd_inventory, date, empid;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("activity_id")).as_string();
	activity_id=sfs.return_to_string(s);
	 MYSQL *conn = dals.connect();
	 dals.dallocate_activity(conn,activity_id, request);

}
web::json::value BL::view_users(http_request request) {
	
	cout << "In BL_attnd";
	json::value temp;
	int state = 1;
	string user_id, date, status, reason, reqd_inventory;




	//s = temp.at(U("user_id")).as_string();
	//user_id = sfs.return_to_string(s);


	MYSQL *conn = dals.connect();
	web::json::value  users = dals.getuserdetails(conn,request);
	cout << "BL out";
	return users;

}

json::value BL::view_activity_type(http_request request) {
	MYSQL *conn = dals.connect();
	json::value activity_types = dals.view_activity_type_DAL(conn);
	cout << "BL out";
	return activity_types;

}

json::value BL::view_activity_create(http_request request) {
	MYSQL *conn = dals.connect();
	json::value activity_create = dals.view_activity_create_DAL(conn);
	cout << "BL out";
	return activity_create;
}
json::value BL:: view_activity_allocate(http_request request) {
	MYSQL *conn = dals.connect();
	json::value activity_allocate = dals.view_activity_allocate_DAL(conn);
	cout << "BL out";
	return activity_allocate;
}
web::json::value BL:: view_role(http_request request) {
	MYSQL *conn = dals.connect();
	json::value activity_allocate = dals.view_role_DAL(conn);
	cout << "BL out";
	return activity_allocate;
}
web::json::value BL:: view_role_assign(http_request request) {
	MYSQL *conn = dals.connect();
	json::value activity_allocate = dals.view_role_assign_DAL(conn);
	cout << "BL out";
	return activity_allocate;
}
json::value BL::  view_inventories(http_request request) {
	MYSQL *conn = dals.connect();
	json::value activity_allocate = dals.view_inventories_DAL(conn);
	cout << "BL out";
	return activity_allocate;
}

json::value BL::view_assigned_activities(http_request request) {
	MYSQL *conn = dals.connect();
	
	json::value temp;
	string user_id,status;
	temp = extract_request(request);//get request in json
	utility::string_t s;



	 s = temp.at(U("empid")).as_string();
	user_id = sfs.return_to_string(s);

	s = temp.at(U("status")).as_string();
	status = sfs.return_to_string(s);

	json::value assigned_activity = dals.view_assigned_activity_DAL(conn,user_id,status);
	cout << "BL out";
	return assigned_activity;
}

int BL::handle_mark_activity_status(http_request request) {
	
	cout << "In BL_activitystatus";
	json::value temp;
	int state = 1;
	string activity_id, status;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("activity_id")).as_string();
	activity_id = sfs.return_to_string(s);

	s = temp.at(U("status")).as_string();
	status = sfs.return_to_string(s);

	
	MYSQL *conn = dals.connect();
	state = dals.mark_activity_status_DAL(conn, activity_id, status);
	cout << "IN BL state=" << state;
	return state;

}
int  BL:: handle_create_internal_activity(http_request request) {
	
	cout << "In BL_activitystatus";
	json::value temp;
	int state = 1;
	string int_activity, duration,user_id;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("user_id")).as_string();
	user_id = sfs.return_to_string(s);

	s = temp.at(U("internal_activity")).as_string();
	int_activity = sfs.return_to_string(s);

	s = temp.at(U("duration")).as_string();
	duration = sfs.return_to_string(s);

	s = temp.at(U("duration")).as_string();
	duration = sfs.return_to_string(s);


	MYSQL *conn = dals.connect();
	state = dals.create_internal_activity_DAL(conn, user_id,int_activity,duration);
	cout << "IN BL state=" << state;
	return state;

}
json::value BL::view_closed_activities() {

	MYSQL *conn = dals.connect();
	json::value state = dals.view_closed_activities(conn);
	wcout << "IN BL state=" << state;
	return state;
}
json::value BL::search_user(http_request request) {

	json::value temp;

	string user;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("emp_id")).as_string();
	user = sfs.return_to_string(s);

	json::value resp;
	MYSQL *conn = dals.connect();
	MYSQL_ROW row = dals.search_user_DAL(conn,user);
	wcout << "IN BL state=" << row[1];
	
	std::string ss = row[0];
	std::wstring emp_id = sfs.return_to_string_t(ss);
	 ss = row[1];
	std::wstring f_name = sfs.return_to_string_t(ss);
	 ss = row[2];
	std::wstring m_name = sfs.return_to_string_t(ss);
	 ss = row[3];
	std::wstring l_name = sfs.return_to_string_t(ss);
	 ss = row[3];
	std::wstring supervisor = sfs.return_to_string_t(ss);



	wcout << "super" << supervisor;
	resp[L"empid"] = json::value::string(emp_id);
	resp[L"f_name"] = json::value::string(f_name);
	resp[L"m_name"] = json::value::string(m_name);
	resp[L"l_name"] = json::value::string(l_name);
	resp[L"supervisor"] = json::value::string(supervisor);

	return resp;
}
json::value BL:: search_user_role(http_request request) {
	json::value temp;

	string role_name;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("role_name")).as_string();
	role_name = sfs.return_to_string(s);


	MYSQL *conn = dals.connect();
	json::value resp = dals.search_user_role_DAL(conn, role_name);
	return resp;
}

json::value BL::search_single_user_role(http_request request) {
	json::value temp,resp;
	cout << "IN BL";
	string user;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("empid")).as_string();
	user = sfs.return_to_string(s);


	MYSQL *conn = dals.connect();
	MYSQL_ROW row = dals.search_single_user_role_DAL(conn, user);

	std::wstring role_id = sfs.return_to_string_t(row[0]);
	std::wstring role_name = sfs.return_to_string_t(row[1]);
	std::wstring empid = sfs.return_to_string_t(row[2]);
	std::wstring name = sfs.return_to_string_t(row[3]);



	resp[L"role_id"] = json::value::string(role_id);
	resp[L"role_name"] = json::value::string(role_name);
	resp[L"empid"] = json::value::string(empid);
	resp[L"name"] = json::value::string(name);




	return resp;
}

json::value BL::search_activity(http_request request) {
	json::value temp, resp;
	cout << "IN BL";
	string activity;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("activity_id")).as_string();
	activity = sfs.return_to_string(s);


	MYSQL *conn = dals.connect();
	MYSQL_ROW row = dals.search_activity_DAL(conn, activity);

	std::wstring activity_id = sfs.return_to_string_t(row[0]);
	resp[L"activity_id"] = json::value::string(activity_id);
	std::wstring activity_type = sfs.return_to_string_t(row[1]);
	resp[L"activity_type"] = json::value::string(activity_type);
	std::wstring status = sfs.return_to_string_t(row[2]);
	resp[L"status"] = json::value::string(status);
	if (row[3] != NULL) {
		std::wstring empid = sfs.return_to_string_t(row[3]);
		resp[L"empid"] = json::value::string(empid);
	}
	else
		resp[L"empid"] = json::value::string(U("NULL"));
	if (row[4] != NULL) {
		std::wstring f_name = sfs.return_to_string_t(row[3]);
		resp[L"f_name"] = json::value::string(f_name);
	}
	else
		resp[L"f_name"] = json::value::string(U("NULL"));


	return resp;

}

json::value BL::view_calendar(http_request request) {
	json::value temp;

	string user_id;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("empid")).as_string();
	user_id = sfs.return_to_string(s);


	MYSQL *conn = dals.connect();
	json::value resp = dals.view_calendar_DAL(conn, user_id);
	return resp;
}

json::value BL:: view_work_skill(http_request requst) {
	json::value temp;

	string user_id;


	MYSQL *conn = dals.connect();
	json::value resp = dals.view_work_skill_DAL(conn);
	return resp;
}
void BL::  get_all_supervisors(http_request request) {
	json::value temp;

	string user_id;


	MYSQL *conn = dals.connect();
	dals.get_all_supervisors_DAL(conn,request);
	
}

void BL:: view_activity_in_super(http_request request) {
	cout << "In BL_activitystatus";
	json::value temp;
	int state = 1;
	string activity_id, status,supervisor;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("supervisor")).as_string();
	supervisor = sfs.return_to_string(s);

	s = temp.at(U("status")).as_string();
	status = sfs.return_to_string(s);


	MYSQL *conn = dals.connect();
	dals.view_activity_in_super_DAL(conn, supervisor, status,request);
	
	

}
void BL::get_activity_id(http_request request) {
	json::value temp;
	int state = 1;
	string activity_name;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("activity_name")).as_string();
	activity_name = sfs.return_to_string(s);

	MYSQL *conn = dals.connect();
	dals.get_activity_id(conn,activity_name, request);
	}

void BL::get_employees(http_request request) {

	json::value temp;
	int state = 1;
	string empid;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);

	MYSQL *conn = dals.connect();
	dals.get_employees_DAL(conn, empid, request);
}
void BL::view_my_activities(http_request request) {
	json::value temp;
	int state = 1;
	string empid;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);

	MYSQL *conn = dals.connect();
	dals.view_my_activities(conn, empid, request);
}

void BL:: allocate_inventory(http_request request){
	
	json::value temp;
	int state = 1;
	string empid,inventory_id,serial_no,unit;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);

	s = temp.at(U("inventory_id")).as_string();
	inventory_id = sfs.return_to_string(s);

	s = temp.at(U("serial_no")).as_string();
	serial_no = sfs.return_to_string(s);

	s = temp.at(U("unit")).as_string();
	unit = sfs.return_to_string(s);

	MYSQL *conn = dals.connect();
	dals.allocate_inventory(conn, empid,inventory_id,serial_no,unit ,request);
}

void BL::view_customers(http_request request) {
	json::value temp;
	int state = 1;
	string empid;



	MYSQL *conn = dals.connect();
	dals.view_customers(conn,request);
}
void BL::  get_my_details(http_request request) {
	json::value temp;
	int state = 1;
	string empid;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);

	MYSQL *conn = dals.connect();
	MYSQL_ROW row = dals.get_my_details(conn, empid);
	string f_name = row[0];
	string l_name = row[1];
	string name = f_name +" "+ l_name;
	wstring s1 = sfs.return_to_string_t(name);
	json::value resp = json::value::string(s1);
	request.reply(status_codes::OK, resp);

}

void BL::view_my_skills(http_request request) {
	json::value temp;
	int state = 1;
	string empid;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);

	MYSQL *conn = dals.connect();

	dals.view_my_skills(conn, empid, request);
}

/*void BL ::update_user_name(http_request request) {
	json::value temp;
	int state = 1;
	string empid,old_username,new_username;

	temp = extract_request(request);//get request in json
	utility::string_t s;

	s = temp.at(U("empid")).as_string();
	empid = sfs.return_to_string(s);

	s = temp.at(U("username")).as_string();
	old_username = sfs.return_to_string(s);

	s = temp.at(U("username")).as_string();
	new_username = sfs.return_to_string(s);

	MYSQL *conn = dals.connect();
	//update_user_dal(conn, empid, old_username, new_username,request);
}
void update_password(http_request request) {
	
}*/