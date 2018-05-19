#include "find_controller.h"

#include "src/database/collectionmethods.h"
#include "src/database/password.h"

#include <iostream>
#include <vector>

dbaas::core::find_controller::find_controller(http::server::reply &rep,
						  http::server::request request)
{
	bsoncxx::document::value request_document =
	bsoncxx::from_json(request.content);

	std::string username =
	request_document.view()["username"].get_utf8().value.to_string();
	std::string client_key =
	request_document.view()["client_key"].get_utf8().value.to_string();

	bsoncxx::types::b_document query_document =
	request_document.view()["query"].get_document();

	bsoncxx::types::b_document projection_document =
	request_document.view()["projection"].get_document();

	bsoncxx::types::b_document sort_document =
	request_document.view()["sort"].get_document();

	bsoncxx::types::b_document min_document =
	request_document.view()["min"].get_document();

	bsoncxx::types::b_document max_document =
	request_document.view()["max"].get_document();

	size_t limit_number = request_document.view()["limit"].get_int32();

	// NOTE LOGS

	//	std::clog << "pro: " << bsoncxx::to_json(projection_document.value)
	//		  << std::endl;
	//	std::clog << "query: " << bsoncxx::to_json(query_document.value)
	//		  << std::endl;

	//	std::clog << "sort: " << bsoncxx::to_json(sort_document.value) <<
	//std::endl;

	//	std::clog << "min: " << bsoncxx::to_json(min_document.value) <<
	//std::endl;

	//	std::clog << "max: " << bsoncxx::to_json(max_document.value) <<
	//std::endl;

	//	std::clog << "username: " << username << std::endl;
	//	std::clog << "database name : "
	//		  << dbaas::database::password::check_key(client_key) <<
	//std::endl;

	auto reply = dbaas::database::find(
	username, dbaas::database::password::check_key(client_key),
	query_document, projection_document, sort_document, min_document,
	max_document, limit_number);
	rep.content.append(reply.c_str(), reply.size());
}
