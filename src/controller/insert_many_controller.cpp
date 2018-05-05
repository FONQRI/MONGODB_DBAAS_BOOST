#include "insert_many_controller.h"

#include "src/database/collectionmethods.h"
#include <iostream>
#include <vector>

dbaas::core::insert_many_controller::insert_many_controller(
	http::server::reply &rep, http::server::request request)
{

	// TODO [0] get values from content instade of hard code
	bsoncxx::document::value document =
	bsoncxx::from_json("{\"query\":{\"hello\":\"test\" }}");

	// NOTE get value from bson
	//	bsoncxx::types::b_document document_query =
	//	document.view()["query"].get_document();
	//	std::clog << bsoncxx::to_json(document_query.value);

	auto reply = dbaas::database::insert_many("userName", "dbname",
						  "[{\"hello\":\"test\" }]");

	rep.content.append(reply.c_str(), reply.size());
}
