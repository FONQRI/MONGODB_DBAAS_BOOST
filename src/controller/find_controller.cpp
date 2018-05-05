#include "find_controller.h"

#include "src/database/collectionmethods.h"
#include <iostream>
#include <vector>

dbaas::core::find_controller::find_controller(http::server::reply &rep,
						  http::server::request request)
{
	// NOTE find usage example
	auto reply = dbaas::database::find(
	"userName", "dbname", "{\"hello\":\"test\" ,\"testVal1\": "
				  "{\"$gt\":25}}",
	"{\"hello\":1 ,\"testVal1\":1, \"_id\":0}", "{\"testVal1\":1}", "{}",
	"{}");
	rep.content.append(reply.c_str(), reply.size());
}
