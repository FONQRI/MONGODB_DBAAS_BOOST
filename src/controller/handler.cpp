#include "handler.h"

#include "homepagecontroller.h"

#include "count_controller.h"
#include "find_controller.h"
#include "find_one_controller.h"
#include "insert_many_controller.h"
#include "insert_one_controller.h"

#include <iostream>
dbaas::core::handler::handler(http::server::request request,
				  http::server::reply &rep)
{

	//	std::clog << "method :" << request.method << std::endl;
	//	std::clog << "content :" << request.content << std::endl;
	//	std::clog << "full url : " << request.uri << std::endl;

	// split url
	std::istringstream string_stream(request.uri);
	std::string temp_str;
	std::vector<std::string> url_list;

	while (getline(string_stream, temp_str, '/')) {
		url_list.push_back(temp_str);
	}

	if (url_list.size() < 2) {
		home_page_controller controller(rep, request);
	}
	else if (url_list.at(1) == "find_one") {
		find_one_controller controller(rep, request);
	}
	else if (url_list.at(1) == "find") {
		find_controller controller(rep, request);
	}
	else if (url_list.at(1) == "insert_one") {
		insert_one_controller controller(rep, request);
	}
	else if (url_list.at(1) == "insert_many") {
		insert_many_controller controller(rep, request);
	}
	else if (url_list.at(1) == "count") {
		count_controller controller(rep, request);
	}

	// auto test = request.headers;
	//	for (auto it : test) {
	//		std::clog << "name : " << std::endl
	//			  << it.name << " value : " << it.value << std::endl;
	//	}
	//	rep.content.append(m_response.c_str(), m_response.size());
}
