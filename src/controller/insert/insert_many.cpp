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

			// get array of documents for insert
			auto array =
			request_document.view()["query"].get_array().value;

			// document vector
			std::vector<bsoncxx::document::value> query_array;

			for (auto &doc : array) {
				query_array.push_back(bsoncxx::from_json(
				bsoncxx::to_json(doc.get_document())));
			}

			// get ordered bool from request document
			bool ordered =
			request_document.view()["ordered"].get_bool();

			// get reply from database
			auto reply = dbaas::database::insert_many(
			username,
			dbaas::database::password::check_key(client_key),
			query_array, ordered);

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
