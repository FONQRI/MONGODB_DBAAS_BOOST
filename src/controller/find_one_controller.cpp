#include "find_one_controller.h"

#include "src/database/collectionmethods.h"
#include <iostream>
#include <vector>

dbaas::core::find_one_controller::find_one_controller(
	http::server::reply &rep, http::server::request request)
{
	// TODO [0] get values from content instade of hard code
	auto reply = dbaas::database::find_one(
	"userName", "dbname", "{\"hello\":\"test\" ,\"testVal1\": "
				  "{\"$gt\":25}}",
	"{\"hello\":1 ,\"testVal1\":1, \"_id\":0}", "{\"testVal1\":-1}", "{}",
	"{}");
	rep.content.append(reply.c_str(), reply.size());
}
