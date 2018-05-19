#include "insert_one_controller.h"

#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include <iostream>
#include <vector>

dbaas::core::insert_one_controller::insert_one_controller(
	http::server::reply &rep, http::server::request request)
{
	// TODO [0] get values from content instade of hard code

	bsoncxx::document::value request_document =
	bsoncxx::from_json(request.content);

	std::string username =
	request_document.view()["username"].get_utf8().value.to_string();
	std::string client_key =
	request_document.view()["client_key"].get_utf8().value.to_string();

	bsoncxx::types::b_document query_document =
	request_document.view()["query"].get_document();

	auto reply = dbaas::database::insert_one(username,  dbaas::database::password::check_key(client_key),
						 query_document);
	rep.content.append(reply.c_str(), reply.size());
}
