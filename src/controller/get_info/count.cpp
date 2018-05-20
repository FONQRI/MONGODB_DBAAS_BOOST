#include "count.h"

#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include "src/database/reply.h"

#include <iostream>
#include <vector>

void dbaas::core::count(http::server::reply &rep, http::server::request request)
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

			std::string username = request_document.view()["username"]
						   .get_utf8()
						   .value.to_string();
			std::string client_key =
			request_document.view()["client_key"]
				.get_utf8()
				.value.to_string();

			size_t limit = request_document.view()["limit"].get_int32();
			size_t skip = request_document.view()["skip"].get_int32();

			bsoncxx::types::b_document query_document =
			request_document.view()["query"].get_document();

			std::string reply = dbaas::database::count(
			username,
			dbaas::database::password::check_key(client_key),
			query_document, limit, skip);
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
