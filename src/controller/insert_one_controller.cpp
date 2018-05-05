#include "insert_one_controller.h"

#include "src/database/collectionmethods.h"
#include <iostream>
#include <vector>

dbaas::core::insert_one_controller::insert_one_controller(
	http::server::reply &rep, http::server::request request)
{
	// TODO [0] get values from content instade of hard code
	auto reply = dbaas::database::insert_one("userName", "dbname",
						 "{\"hello\":\"test\" }");
	rep.content.append(reply.c_str(), reply.size());
}
