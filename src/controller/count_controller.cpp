#include "count_controller.h"

#include "src/database/collectionmethods.h"
#include <iostream>
#include <vector>

dbaas::core::count_controller::count_controller(http::server::reply &rep,
						http::server::request request)
{
	// NOTE count usage example
	auto reply = dbaas::database::count("userName", "dbname",
					"{\"hello\":\"test\" ,\"testVal1\": "
					"{\"$gt\":25}}",
					1, 2);
	rep.content.append(reply.c_str(), reply.size());
}
