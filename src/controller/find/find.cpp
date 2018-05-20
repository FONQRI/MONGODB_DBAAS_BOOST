#include "find.h"

#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include "src/database/reply.h"

#include <iostream>
#include <vector>

void dbaas::core::find(http::server::reply &rep, http::server::request request)
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

			size_t limit_number =
			request_document.view()["limit"].get_int32();

			// NOTE LOGS

			//	std::clog << "pro: " <<
			// bsoncxx::to_json(projection_document.value)
			//		  << std::endl;
			//	std::clog << "query: " <<
			// bsoncxx::to_json(query_document.value)
			//		  << std::endl;

			//	std::clog << "sort: " <<
			// bsoncxx::to_json(sort_document.value) <<
			// std::endl;

			//	std::clog << "min: " <<
			// bsoncxx::to_json(min_document.value) <<
			// std::endl;

			//	std::clog << "max: " <<
			// bsoncxx::to_json(max_document.value) <<
			// std::endl;

			//	std::clog << "username: " << username << std::endl;
			//	std::clog << "database name : "
			//		  <<
			// dbaas::database::password::check_key(client_key)
			//<<
			// std::endl;

			auto reply = dbaas::database::find(
			username,
			dbaas::database::password::check_key(client_key),
			query_document, projection_document, sort_document,
			min_document, max_document, limit_number);
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
