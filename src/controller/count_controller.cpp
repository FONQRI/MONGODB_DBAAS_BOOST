#include "count_controller.h"

#include "src/database/collectionmethods.h"
#include <iostream>
#include <vector>

dbaas::core::count_controller::count_controller(http::server::reply &rep,
						http::server::request request)
{
	// TODO [1] handle post and get request for all controllers
	// TODO [1] add header for add controllers
	// TODO [1] handle bad json content and add exeption in all controllers

	if (request.method == "POST") {
		http::server::header content_type;
		content_type.name = "Content-Type";
		content_type.value = "application/json;";

		http::server::header charset;
		charset.name = "charset";
		charset.value = "utf-8";

		rep.headers.push_back(content_type);
		rep.headers.push_back(charset);

		bsoncxx::document::value request_document =
		bsoncxx::from_json(request.content);

		std::string username = request_document.view()["username"]
					   .get_utf8()
					   .value.to_string();
		std::string client_key = request_document.view()["client_key"]
					 .get_utf8()
					 .value.to_string();

		size_t limit = request_document.view()["limit"].get_int32();
		size_t skip = request_document.view()["skip"].get_int32();

		bsoncxx::types::b_document query_document =
		request_document.view()["query"].get_document();

		std::string reply = dbaas::database::count(
		"userName", "dbname", query_document, limit, skip);
		rep.content.append(reply.c_str(), reply.size());
	}
	else {
		http::server::header content_type;
		content_type.name = "Content-Type";
		content_type.value = "application/json;";

		http::server::header charset;
		charset.name = "charset";
		charset.value = "utf-8";

		rep.headers.push_back(content_type);
		rep.headers.push_back(charset);

		std::string reply = "{\"test\":\"hello\"}";
		rep.content.append(reply.c_str(), reply.size());
	}
}
