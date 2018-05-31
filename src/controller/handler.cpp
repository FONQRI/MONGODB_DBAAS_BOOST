#include "handler.h"

#include "homepagecontroller.h"

#include "delete/delete_many.h"
#include "delete/delete_one.h"
#include "delete/find_one_and_delete.h"
#include "find/find.h"
#include "find/find_one.h"
#include "get_info/count.h"
#include "get_info/list_indexes.h"
#include "get_info/name.h"
#include "insert/insert_many.h"
#include "insert/insert_one.h"
#include "update/create_index.h"
#include "update/find_one_and_update.h"
#include "update/update_many.h"
#include "update/update_one.h"

#include <iostream>

/**
 * @brief controller	: a function for controller mapping
 * @param rep			: reply of http
 * @param request		: request of http
 */
typedef void controller(http::server::reply &rep,
			http::server::request request);

/**
 * @brief function_mapper : controller mapper type
 */
typedef std::map<std::string, controller *> function_mapper;

/**
 * @brief controller_mapper
 */
extern function_mapper controller_mapper;

// handler
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

	// map controllers
	if (url_list.size() < 2) {
		home_page_controller controller(rep, request);
	}
	else if (controller_mapper[url_list.at(1)] != 0) {
		controller_mapper[url_list.at(1)](rep, request);
	}
}
