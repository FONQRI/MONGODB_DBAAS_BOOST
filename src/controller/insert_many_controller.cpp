#include "insert_many_controller.h"

#include "src/database/collectionmethods.h"
#include "src/database/password.h"

#include <iostream>
#include <vector>

dbaas::core::insert_many_controller::insert_many_controller(
	http::server::reply &rep, http::server::request request)
{
	bsoncxx::document::value request_document =
	bsoncxx::from_json(request.content);

	bool ordered = request_document.view()["ordered"].get_double();
	std::string username =
	request_document.view()["username"].get_utf8().value.to_string();

	std::string client_key =
	request_document.view()["client_key"].get_utf8().value.to_string();

	auto array = request_document.view()["query"].get_array().value;
	std::vector<bsoncxx::document::value> query_array;
	for (auto &doc : array) {
		query_array.push_back(
		bsoncxx::from_json(bsoncxx::to_json(doc.get_document())));
	}

	auto reply = dbaas::database::insert_many(
	username, dbaas::database::password::check_key(client_key), query_array,
	ordered);

	rep.content.append(reply.c_str(), reply.size());
}
