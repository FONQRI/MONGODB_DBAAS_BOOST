#include "insert_one.h"

#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include "src/database/reply.h"

#include <iostream>
#include <vector>

void dbaas::core::insert_one(http::server::reply &rep,
				 http::server::request request)
{
	// add headers
	//	specifying content type as json
	http::server::header content_type;
	content_type.name = "Content-Type";
	content_type.value = "application/json;";

	//	specifying content charset as utf-8
	http::server::header charset;
	charset.name = "charset";
	charset.value = "utf-8";

	// putting headers into reply
	rep.headers.push_back(content_type);
	rep.headers.push_back(charset);

	try {
		// check if request is post
		if (request.method == "POST") {

			// convert content to json
			bsoncxx::document::value request_document =
			bsoncxx::from_json(request.content);

			// get username of request
			std::string username = request_document.view()["username"]
						   .get_utf8()
						   .value.to_string();

			// get client key of request
			std::string client_key =
			request_document.view()["client_key"]
				.get_utf8()
				.value.to_string();

			// get query document of request
			bsoncxx::types::b_document query_document =
			request_document.view()["query"].get_document();

			// get reply from database
			auto reply = dbaas::database::insert_one(
			username,
			dbaas::database::password::check_key(client_key),
			query_document);

			// write reply
			rep.content.append(reply.c_str(), reply.size());
		}
		else {
			// if request isn't post method
			std::string reply =
			dbaas::database::reply::error("send post method");

			// write reply
			rep.content.append(reply.c_str(), reply.size());
		}
	}
	catch (std::exception &e) {

		// if execption happend in getting values or parsing json
		std::string reply = dbaas::database::reply::error(e.what());

		// write reply
		rep.content.append(reply.c_str(), reply.size());
	}
}
