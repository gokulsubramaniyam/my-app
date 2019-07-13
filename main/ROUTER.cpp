#include "ROUTER.h" // header in local directory
#include <iostream> // header in standard library
#include "subfunc.h" // header in local directory
#include "BL.h" // header in local directory

using namespace route;
using namespace std;
using namespace sf;
using namespace bl;




BL bls;
subfunc sfsrouter;

void ROUTER::route(http_request request) {
	uri urls = request.absolute_uri();
	utility::string_t urlss = urls.to_string();
	int state;
	string abs_url = sfsrouter.return_to_string(urlss);
	//cout << "url=" << abs_url << endl;
	if (abs_url == "/login") {
		bls.handle_login(request);
	}
	if (abs_url == "/create_user") {
		cout << "Routing:";
		state = bls.handle_user_create(request);

	}
	if (abs_url == "/create_role") {
		cout << "Routing:";
		state = bls.handle_role_create(request);
		if (!state) {
			json::value resp = json::value::string(U("Role created successfully"));
			request.reply(status_codes::OK, resp); //send the reply as a json.
		}
		else
			request.reply(status_codes::NotFound);
	}
	if (abs_url == "/create_inventory") {
		cout << "Routing:";
		state = bls.handle_inventory_create(request);
		if (!state) {
			cout << "In router";
			json::value resp = json::value::string(U("Inventory created successfully"));
			wcout << resp;
			request.reply(status_codes::OK, resp); //send the reply as a json.
		}
		else if (state == 1) {
			json::value resp = json::value::string(U("No unit for non serialized value"));
			request.reply(status_codes::BadRequest, resp);
		}
		else
			request.reply(status_codes::NotFound);
	}
	if (abs_url == "/role_assign") {
		cout << "Routing:";
		state = bls.role_assign(request);
		if (!state) {
			json::value resp = json::value::string(U("Role assigned successfully"));
			request.reply(status_codes::OK, resp); //send the reply as a 
		}

		else
			request.reply(status_codes::NotFound);
	}
	if (abs_url == "/create_workskill") {
		cout << "Routing:";
		state = bls.handle_workskill_create(request);
		if (!state) {
			json::value resp = json::value::string(U("Workskill created succssfully"));
			request.reply(status_codes::OK, resp); //send the reply as a json.
		}

		else
			request.reply(status_codes::NotFound);
	}
	if (abs_url == "/create_activity_type") {
		cout << "Routing:";
		state = bls.handle_activitytype_create(request);
		if (!state) {
			json::value resp = json::value::string(U("Activity_type created successfully"));

			request.reply(status_codes::OK, resp); //send the reply as a json.
		}
		else
			request.reply(status_codes::NotFound);
	}


	if (abs_url == "/create_activity") {
		cout << "Routing:";
		state = bls.handle_activity_create(request);
	}
	if (abs_url == "/create_customer") {
		cout << "Routing:";
		state = bls.handle_customer_create(request);
		cout << "state=" << state;
		
	}
	if (abs_url == "/view_users") {
		cout << "Routing:";
		web::json::value users = bls.view_users(request);
		wcout << "In router" << users.at(U("data")).as_string();
		cout << "Router out";
		//request.reply(status_codes::OK,users); //send the reply as a json.

	}
	if (abs_url == "/view_role") {
		cout << "Routing:";
		web::json::value users = bls.view_role(request);
		//wcout << "In router" << users.at(U("data")).as_string();
		cout << "Router out";
		request.reply(status_codes::OK, users); //send the reply as a json.

	}
	if (abs_url == "/view_role_assign") {
		cout << "Routing:";
		web::json::value users = bls.view_role_assign(request);

		cout << "Router out";
		request.reply(status_codes::OK, users); //send the reply as a json.

	}

	if (abs_url == "/mark_attendance") {
		cout << "Routing:";
		state = bls.handle_mark_attendance(request);
		cout << "state=" << state;
		if (state==0) {
			json::value resp = json::value::string(U("Attendance Marked"));
			request.reply(status_codes::OK, resp); //send the reply as a json.
		}

		else {
			json::value resp = json::value::string(U("Already maarked"));
			request.reply(status_codes::NotFound,resp);
		}
	}
	if (abs_url == "/activity_assign") {
		cout << "Routing:";
		state = bls.activity_assign(request);
		cout << "In router state=" << state;
		
		if (state!=0) {
			json::value resp = json::value::number(state);
			request.reply(status_codes::OK,resp); //send the reply as a json.
		}

		else
			request.reply(status_codes::NotFound);
	}

	if (abs_url == "/view_activity_type") {
		cout << "Routing:";
		json::value activity_types = bls.view_activity_type(request);
		cout << "In router state=" << state;


		request.reply(status_codes::OK, activity_types); //send the reply as a json.


	}

	if (abs_url == "/view_activity_create") {
		cout << "Routing:";
		json::value activity_create = bls.view_activity_create(request);



		request.reply(status_codes::OK, activity_create); //send the reply as a json.


	}
	if (abs_url == "/view_activity_allocate") {
		cout << "Routing:";
		json::value activity_allocate = bls.view_activity_allocate(request);



		request.reply(status_codes::OK, activity_allocate); //send the reply as a json.


	}

	if (abs_url == "/view_inventories") {
		cout << "Routing:";
		json::value activity_allocate = bls.view_inventories(request);



		request.reply(status_codes::OK, activity_allocate); //send the reply as a json.


	}

	if (abs_url == "/view_assigned_activities") {
		cout << "Routing:";
		json::value activity_allocate = bls.view_assigned_activities(request);
		request.reply(status_codes::OK, activity_allocate); //send the reply as a json.
	}

	if (abs_url == "/mark_activity_status") {
		cout << "Routing:";
		state = bls.handle_mark_activity_status(request);
		cout << "state=" << state;
		if (!state) {
			json::value resp = json::value::string(U(" Marked Open"));
			request.reply(status_codes::OK, resp); //send the reply as a json.
		}

		else
			request.reply(status_codes::NotFound);
	}


	if (abs_url == "/create_internal_activity") {
		cout << "Routing:";
		state = bls.handle_create_internal_activity(request);
		cout << "state=" << state;
		if (!state) {
			json::value resp = json::value::string(U("Created Internal Activity"));
			request.reply(status_codes::OK, resp); //send the reply as a json.
		}

		else
			request.reply(status_codes::NotFound);
	}

	if (abs_url == "/view_closed_activities") {
		cout << "Routing:";

		json::value activity_allocate = bls.view_closed_activities();
		request.reply(status_codes::OK, activity_allocate); //send the reply as a json.
	}

	if (abs_url == "/search_user") {
		cout << "Routing:";

		json::value user = bls.search_user(request);
		request.reply(status_codes::OK, user); //send the reply as a json.
	}
	if (abs_url == "/search_user_role") {
		cout << "Routing:";

		json::value user = bls.search_user_role(request);
		request.reply(status_codes::OK, user); //send the reply as a json.
	}
	if (abs_url == "/search_single_user_role") {
		cout << "Routing:";

		json::value user = bls.search_single_user_role(request);
		request.reply(status_codes::OK, user); //send the reply as a json.
	}
	if (abs_url == "/search_activity") {
		cout << "Routing:";

		json::value user = bls.search_activity(request);
		request.reply(status_codes::OK, user); //send the reply as a json.
	}
	if (abs_url == "/view_calendar") {
		cout << "Routing:";

		json::value user = bls.view_calendar(request);
		request.reply(status_codes::OK, user); //send the reply as a json.
	}

	if (abs_url == "/view_work_skill") {
		cout << "Routing:";

		json::value user = bls.view_work_skill(request);
		request.reply(status_codes::OK, user); //send the reply as a json.
	}

	if (abs_url == "/get_emp_skills") {
		cout << "Routing:";

		 bls.get_emp_skills(request);
		
	}

	if (abs_url == "/assign_skill") {
		cout << "Routing:";
		bls.assign_work_skill(request);
	}
	if (abs_url == "/get_all_supervisors") {
		cout << "Routing:";

		bls.get_all_supervisors(request);
	}

	if (abs_url == "/view_activity_in_super"){ 
		cout << "Routing:";

		bls.view_activity_in_super(request);
	}
	if (abs_url == "/get_activity_id") {
		bls.get_activity_id(request);
	}
	if (abs_url == "/deallocate_activity") {
		bls.deallocate_activity(request);
	}
	
	if (abs_url == "/get_employees") {
		bls.get_employees(request);
	}


	if (abs_url == "/view_my_activities") {
		bls.view_my_activities(request);
	}

	if (abs_url == "/allocate_inventory") {
		bls.allocate_inventory(request);
	}
	if (abs_url == "/view_customers") {
		bls.view_customers(request);
	}
	if (abs_url == "/get_time_slots") {
		bls.get_time_slots(request);
	}
	if (abs_url == "/manual_route") {
		bls.get_user_data_for_manual_routiung(request);
	}

	if (abs_url == "/get_my_details") {
		bls.get_my_details(request);
	}
	if (abs_url == "/create_route") {
		bls.create_route(request);
	}
	if (abs_url == "/view_my_skills") {
		bls.view_my_skills(request);
	}

	/*if (abs_url == "/update_user_name") {
		bls.update_user_name(request);
	}
	if (abs_url == "/update_password") {
		bls.update_password(request);
	}*/

}	

	
