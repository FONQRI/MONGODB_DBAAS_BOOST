#include "handler.h"

#include "homepagecontroller.h"

#include <iostream>
iotdb::core::handler::handler(http::server::request request,
				  http::server::reply &rep)
{
	//	m_response = "answer";
	//	std::clog << request.method << std::endl;
	//	std::clog << "request.uri " << request.content << std::endl;
	homePageController test1(rep, "");
	// auto test = request.headers;
	//	for (auto it : test) {
	//		std::clog << "name : " << std::endl
	//			  << it.name << " value : " << it.value << std::endl;
	//	}
	//	rep.content.append(m_response.c_str(), m_response.size());
}
