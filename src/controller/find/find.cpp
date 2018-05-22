#include "find.h"

#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include "src/database/reply.h"

#include <iostream>
#include <vector>

void dbaas::core::find(http::server::reply &rep, http::server::request request)
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

			// get projection document of request
			bsoncxx::types::b_document projection_document =
			request_document.view()["projection"].get_document();

			// get sort document of request
			bsoncxx::types::b_document sort_document =
			request_document.view()["sort"].get_document();

			// get min document from request document
			bsoncxx::types::b_document min_document =
			request_document.view()["min"].get_document();

			// get max document from request document
			bsoncxx::types::b_document max_document =
			request_document.view()["max"].get_document();

			// get limit from request document
			size_t limit_number =
			request_document.view()["limit"].get_int32();

			// get reply from database
			auto reply = dbaas::database::find(
			username,
			dbaas::database::password::check_key(client_key),
			query_document, projection_document, sort_document,
			min_document, max_document, limit_number);

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
