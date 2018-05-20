#include "find_one_and_replace.h"
#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include "src/database/reply.h"

void dbaas::core::find_one_and_replace(http::server::reply &rep,
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

			std::string username = request_document.view()["username"]
						   .get_utf8()
						   .value.to_string();
			std::string client_key =
			request_document.view()["client_key"]
				.get_utf8()
				.value.to_string();

			bsoncxx::types::b_document filter_document =
			request_document.view()["filter"].get_document();

			bsoncxx::types::b_document replacement_document =
			request_document.view()["replacement"].get_document();

			bsoncxx::types::b_document projection_document =
			request_document.view()["projection"].get_document();

			bsoncxx::types::b_document sort_document =
			request_document.view()["sort"].get_document();

			bsoncxx::types::b_document collation =
			request_document.view()["collation"].get_document();

			bsoncxx::types::b_document write_concern =
			request_document.view()["write_concern"].get_document();

			std::string acknowledge_level =
			write_concern.view()["acknowledge_level"]
				.get_utf8()
				.value.to_string();

			std::string tag = write_concern.view()["tag"]
					  .get_utf8()
					  .value.to_string();

			bool journal = write_concern.view()["journal"].get_bool();

			int majority = write_concern.view()["majority"].get_int32();

			int timeout = write_concern.view()["timeout"].get_int32();

			int nodes = write_concern.view()["nodes"].get_int32();

			bool upsert = request_document.view()["upsert"].get_bool();

			int max_time =
			request_document.view()["max_time"].get_int32();

			bool bypass_document_validation =
			request_document.view()["bypass_document_validation"]
				.get_bool();

			auto reply = dbaas::database::find_one_and_replace(
			username,
			dbaas::database::password::check_key(client_key),
			filter_document, replacement_document,
			projection_document, sort_document, collation,
			acknowledge_level, tag, journal, majority, timeout,
			nodes, max_time, upsert, bypass_document_validation);

			// answer
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
