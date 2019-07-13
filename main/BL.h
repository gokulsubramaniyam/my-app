
#pragma once

#include "cpprest/http_client.h"
#include "cpprest/filestream.h"
#include"cpprest/http_listener.h"


using namespace std;
using namespace web;
using namespace web::http;
using namespace web::http::client;

using namespace web::http::experimental::listener;

namespace bl{
	class BL
	{
	public:
		
		void handle_login(http_request request);
		int handle_user_create(http_request request);
		int handle_role_create(http_request request);
		int handle_inventory_create(http_request request);
		int handle_workskill_create(http_request request);
		int handle_activitytype_create(http_request request);
		int handle_activity_create(http_request request);
		int handle_customer_create(http_request request);
		
	
		int handle_mark_attendance(http_request request);
		int role_assign(http_request request);
		web::json::value view_users(http_request request);
		int activity_assign(http_request request);
		json::value extract_request(http_request);
		json::value view_activity_type(http_request request);
		json::value view_activity_create(http_request request);
		json::value view_activity_allocate(http_request request);
		web::json::value view_role(http_request request);
		web::json::value view_role_assign(http_request request);
		json::value  view_inventories(http_request request);
		json::value view_assigned_activities(http_request request);
		int handle_mark_activity_status(http_request request);
		int handle_create_internal_activity(http_request request);
		json::value view_closed_activities();

		json::value search_user(http_request request);
		//json::value search_role(http_request request);
		json::value search_user_role(http_request request);
		//json::value search_activity_type(http_request request);
		//json::value search_activity(http_request request);
		json::value search_single_user_role(http_request request);
		json::value search_activity(http_request request);

		json::value view_calendar(http_request request);
		json::value  view_work_skill(http_request requst);
		void  get_all_supervisors(http_request request);

		void view_activity_in_super(http_request request);
		void get_activity_id(http_request request);
		void get_employees(http_request request);
		void view_my_activities(http_request request);
		void allocate_inventory(http_request request);
		void view_customers(http_request request);
		void assign_work_skill(http_request request);
		void get_emp_skills(http_request request);
		void get_time_slots(http_request request);
		void get_user_data_for_manual_routiung(http_request request);
		void deallocate_activity(http_request request);
		void return_activity_id_for_manual_routing(http_request request);
		void  get_my_details(http_request request);
		void create_route(http_request request);
		void view_my_skills(http_request request);
		int StringToTime(std::string time_24h);
		/*void update_user_name(http_request request);
		void update_password(http_request request);*/
	};

}