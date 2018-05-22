#include "update_one.h"

#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include "src/database/reply.h"

#include <iostream>
#include <vector>

void dbaas::core::update_one(http::server::reply &rep,
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

			// get filter document from request document
			bsoncxx::types::b_document filter =
			request_document.view()["filter"].get_document();

			// get query document of request
			bsoncxx::types::b_document query =
			request_document.view()["query"].get_document();

			// get collation of request
			// https://docs.mongodb.com/manual/reference/collation/
			bsoncxx::types::b_document collation =
			request_document.view()["collation"].get_document();

			// get write_concern document of request
			// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
			bsoncxx::types::b_document write_concern =
			request_document.view()["write_concern"].get_document();

			// get acknowledge_level from write_concern doc
			std::string acknowledge_level =
			write_concern.view()["acknowledge_level"]
				.get_utf8()
				.value.to_string();

			// get tag from write_concern doc
			std::string tag = write_concern.view()["tag"]
					  .get_utf8()
					  .value.to_string();

			// get journal from write_concern doc
			bool journal = write_concern.view()["journal"].get_bool();

			// get majority from write_concern doc
			int majority = write_concern.view()["majority"].get_int32();

			// get timeout from write_concern doc
			int timeout = write_concern.view()["timeout"].get_int32();

			// get nodes from write_concern doc
			int nodes = write_concern.view()["nodes"].get_int32();

			// get upsert from request document
			bool upsert = request_document.view()["upsert"].get_bool();

			// get bypass_document_validation from request document
			bool bypass_document_validation =
			request_document.view()["bypass_document_validation"]
				.get_bool();

			// get reply from database
			auto reply = dbaas::database::update_one(
			username,
			dbaas::database::password::check_key(client_key),
			filter, query, collation, acknowledge_level, tag,
			journal, majority, timeout, nodes, upsert,
			bypass_document_validation);

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
