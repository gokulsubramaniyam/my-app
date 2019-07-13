#pragma once
#include "mysql.h"
#include<iostream>
#include<string>
#include "subfunc.h"
#include "cpprest/json.h"
#include "cpprest/http_client.h"
#include "cpprest/filestream.h"
#include"cpprest/http_listener.h"
using namespace std;
using namespace json;
using namespace web;
using namespace web::http;
using namespace web::http::client;

namespace dal
{
	class DAL
	{
	public:

		MYSQL* connect();
		MYSQL_ROW login_DAL(MYSQL *conn, string id, string pass,http_request request);
		int create_user_DAL(MYSQL *conn,  string f_name, string m_name, string l_name, string supervisor, string role_id, string start_date, string end_date,http_request request);
		int create_role_DAL(MYSQL *conn, string role_name, string descr);
		int create_inventory_DAL(MYSQL *conn,  string inventory_name, string serial, string unit,string serialno);
		int create_activitytype_DAL(MYSQL *conn,  string activity_name, string reqd_duration, string color_code, string skill_id);
		int create_workskill_DAL(MYSQL *conn, string skill_name);
		int create_customer_DAL(MYSQL *conn, string cust_name, string address, string city, string states, string zip_code, string phone, string email,http_request request);
		int create_activity_DAL(MYSQL *conn, string activity_type, string time_slot, string dispatcher_comments, string amount, string cust_id, string status,string created_by,http_request request);
		int create_attendance_DAL(MYSQL *conn, string user_id, string date, string status, string reason);
		vector <string> getallusers(MYSQL *conn, string date, string empid);
		vector<string> getinactiveactivities(MYSQL *conn,string empid);
		json::value getuserdetails(MYSQL *conn, http_request request);
		json::value view_activity_type_DAL(MYSQL *conn);
		json::value view_activity_create_DAL(MYSQL *conn);
		int role_assign_DAL(MYSQL *conn, string user_id, string role_id, string start_date, string end_date);
		json::value view_activity_allocate_DAL(MYSQL *conn);
		json::value view_role_DAL(MYSQL *conn);
		json::value view_role_assign_DAL(MYSQL *conn);
		int initiate_activity(MYSQL *conn);
		json::value view_inventories_DAL(MYSQL *conn);
		int create_activity_allocate(MYSQL *conn, string activities, string users, string date, string reqd_inventory);
		json::value view_assigned_activity_DAL(MYSQL *conn, string user_id, string status);
		int mark_activity_status_DAL(MYSQL *conn, string activity_id, string status);
		int create_internal_activity_DAL(MYSQL *conn, string user_id, string int_activity, string duration);
		json::value view_closed_activities(MYSQL *conn);

		MYSQL_ROW search_user_DAL(MYSQL *conn, string user);
		MYSQL_ROW search_role_DAL(MYSQL *conn, string user);
		json::value search_user_role_DAL(MYSQL *conn, string user);
		MYSQL_ROW search_single_user_role_DAL(MYSQL *conn, string user);
		MYSQL_ROW search_activity_DAL(MYSQL *conn, string activity);

		json::value view_calendar_DAL(MYSQL *conn, string user_id);
		json::value view_work_skill_DAL(MYSQL *conn);
		void get_all_supervisors_DAL(MYSQL *conn,http_request request);
		void view_activity_in_super_DAL(MYSQL *conn, string supervisor, string status, http_request request);
		void get_activity_id(MYSQL *conn,string activity_name, http_request request);
		void get_employees_DAL(MYSQL *conn, string empid, http_request request);
		void view_my_activities(MYSQL *conn, string empid, http_request request);
		MYSQL_ROW get_last_serial(MYSQL *conn);
		void allocate_inventory(MYSQL *conn, string empid, string inventory_id, string serial_no, string unit, http_request request);
		void view_customers(MYSQL *conn, http_request request);
		MYSQL_ROW get_last_activity_type(MYSQL *conn);
		int insert_time_slots(MYSQL *conn,string activity_id, string start_time, string end_time);
		void assign_skill(MYSQL *conn, string empid, string skill_name, http_request request);
		void get_emp_skill_DAL(MYSQL *conn, string empid, http_request request);
		void get_time_slot(MYSQL *conn, string empid,http_request request);
		vector<web::json::value> get_user_status(MYSQL *conn,string user);
		MYSQL_ROW get_activity_status(MYSQL *conn,string activity);
		MYSQL_ROW get_act_skill_id(MYSQL * conn, string activitiy);
		vector<web::json::value> get_user_skill_id(MYSQL * conn, string user);

		MYSQL_ROW get_act_timers(MYSQL * conn, string time_id);

		 void dallocate_activity(MYSQL * conn, string activitiy,http_request request);
		 MYSQL_ROW get_my_details(MYSQL *conn, string empid);

		 void view_my_skills(MYSQL *conn, string empid, http_request request);


		 //void update_user_dal(MYSQL *conn, string empid, string old_username, string new_username,http_request request);
	};
}