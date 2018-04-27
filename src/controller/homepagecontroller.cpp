#include "homepagecontroller.h"
#include "src/database/query.h"
#include <iostream>

iotdb::core::homePageController::homePageController(http::server::reply &rep,
							std::string params)
{
	//	iotdb::database::InsertOne on("userName", "dbname",
	//"{\"hello\":\"test\"}");
	auto reply =
	iotdb::database::find("userName", "dbname", "{\"hello\":\"test\"}");

	rep.content.append(reply.c_str(), reply.size());
}
