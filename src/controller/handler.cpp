#include "handler.h"

#include "homepagecontroller.h"

#include "delete/delete_many.h"
#include "delete/delete_one.h"
#include "delete/find_one_and_delete.h"
#include "find/find.h"
#include "find/find_one.h"
#include "get_info/count.h"
#include "insert/insert_many.h"
#include "insert/insert_one.h"
#include "update/find_one_and_update.h"
#include "update/update_many.h"
#include "update/update_one.h"

#include <iostream>

typedef void controller(http::server::reply &rep,
			http::server::request request);
typedef std::map<std::string, controller *> function_mapper;

extern function_mapper controller_mapper;

dbaas::core::handler::handler(http::server::request request,
				  http::server::reply &rep)
{

	// split url
	std::istringstream string_stream(request.uri);
	std::string temp_str;
	std::vector<std::string> url_list;

	while (getline(string_stream, temp_str, '/')) {
		url_list.push_back(temp_str);
	}

	// TODO [1] create mapping system by inhrence controller classes from
	// base controller class
	if (url_list.size() < 2) {
		home_page_controller controller(rep, request);
	}
	else if (controller_mapper[url_list.at(1)] != 0) {
		controller_mapper[url_list.at(1)](rep, request);
	}
	//	if (url_list.at(1) == "find_one") {
	//		find_one controller(rep, request);
	//	}
	//	else if (url_list.at(1) == "find") {
	//		controller_mapper["find"](rep, request);
	//	}
	//	else if (url_list.at(1) == "insert_one") {
	//		insert_one controller(rep, request);
	//	}
	//	else if (url_list.at(1) == "insert_many") {
	//		insert_many controller(rep, request);
	//	}
	//	else if (url_list.at(1) == "count") {
	//		count controller(rep, request);
	//	}
	//	else if (url_list.at(1) == "delete_one") {
	//		delete_one controller(rep, request);
	//	}
	//	else if (url_list.at(1) == "delete_many") {
	//		delete_many controller(rep, request);
	//	}
	//	else if (url_list.at(1) == "find_one_and_delete") {
	//		find_one_and_delete controller(rep, request);
	//	}
	//	else if (url_list.at(1) == "update_one") {
	//		update_one controller(rep, request);
	//	}
	//	else if (url_list.at(1) == "update_many") {
	//		update_many controller(rep, request);
	//	}
	//	else if (url_list.at(1) == "find_one_and_update") {
	//		find_one_and_update controller(rep, request);
	//	}

	// auto test = request.headers;
	//	for (auto it : test) {
	//		std::clog << "name : " << std::endl
	//			  << it.name << " value : " << it.value << std::endl;
	//	}
	//	rep.content.append(m_response.c_str(), m_response.size());
}
