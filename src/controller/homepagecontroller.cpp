#include "homepagecontroller.h"
#include "src/database/collectionmethods.h"

#include <iostream>

iotdb::core::homePageController::homePageController(http::server::reply &rep,
							std::string params)
{
	auto reply = iotdb::database::count("userName", "dbname");
	rep.content.append(reply.c_str(), reply.size());
}
