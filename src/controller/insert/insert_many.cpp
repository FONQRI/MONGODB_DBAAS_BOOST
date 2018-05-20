#include "insert_many.h"

#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include "src/database/reply.h"

#include <iostream>
#include <vector>

void dbaas::core::insert_many(http::server::reply &rep,
				  http::server::request request)
{
	// add headers
	http::server::header content_type;
	content_type.name = "Content-Type";
	content_type.value = "application/json;";

	http::server::header charset;
	charset.name = "charset";
	charset.value = "utf-8";

	rep.headers.push_back(content_type);
	rep.headers.push_back(charset);

	try {
		if (request.method == "POST") {
			bsoncxx::document::value request_document =
			bsoncxx::from_json(request.content);

			bool ordered =
			request_document.view()["ordered"].get_bool();
			std::string username = request_document.view()["username"]
						   .get_utf8()
						   .value.to_string();

			std::string client_key =
			request_document.view()["client_key"]
				.get_utf8()
				.value.to_string();

			auto array =
			request_document.view()["query"].get_array().value;
			std::vector<bsoncxx::document::value> query_array;
			for (auto &doc : array) {
				query_array.push_back(bsoncxx::from_json(
				bsoncxx::to_json(doc.get_document())));
			}

			auto reply = dbaas::database::insert_many(
			username,
			dbaas::database::password::check_key(client_key),
			query_array, ordered);

			rep.content.append(reply.c_str(), reply.size());
		}
		else {

			std::string reply =
			dbaas::database::reply::error("send post method");
			rep.content.append(reply.c_str(), reply.size());
		}
	}
	catch (std::exception &e) {
		std::string reply = dbaas::database::reply::error(e.what());
		rep.content.append(reply.c_str(), reply.size());
	}
}
