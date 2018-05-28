// header
#include "find.h"

// internal
#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include "src/database/reply.h"

// boost
#include <boost/optional.hpp>

// std
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

			// get username of request
			std::string username{""};
			// get client key of request
			std::string client_key{""};
			for (auto &header : request.headers) {
				if (strcmp(header.name.c_str(), "username") ==
					0) {
					username = header.value;
				}
				else if (strcmp(header.name.c_str(),
						"client_key") == 0) {
					client_key = header.value;
				}
			}
			if (username.empty()) {
				std::string reply =
				dbaas::database::reply::missing_item_error(
					"username");
				rep.content.append(reply.c_str(), reply.size());
				return;
			}
			else if (client_key.empty()) {
				std::string reply =
				dbaas::database::reply::missing_item_error(
					"client_key");
				rep.content.append(reply.c_str(), reply.size());
				return;
			}

			// convert content to json
			bsoncxx::document::value request_document =
			bsoncxx::from_json(request.content);

			// get query document of request
			bsoncxx::types::b_document query;

			try {
				query =
				request_document.view()["query"].get_document();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					std::string reply = dbaas::database::reply::
					missing_item_error("query");
					rep.content.append(reply.c_str(),
							   reply.size());
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"query");
					rep.content.append(reply.c_str(),
							   reply.size());
				}
				return;
			}

			// get projection document of request
			boost::optional<bsoncxx::types::b_document> projection;

			try {
				projection = request_document.view()["projection"]
						 .get_document();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					// element is optional
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"projection");
					rep.content.append(reply.c_str(),
							   reply.size());
					return;
				}
			}

			// get sort document of request
			boost::optional<bsoncxx::types::b_document> sort;

			try {
				sort =
				request_document.view()["sort"].get_document();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					// element is optional
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"sort");
					rep.content.append(reply.c_str(),
							   reply.size());
					return;
				}
			}

			// get min document from request document
			boost::optional<bsoncxx::types::b_document> min;

			try {
				min = request_document.view()["min"].get_document();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					// element is optional
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"min");
					rep.content.append(reply.c_str(),
							   reply.size());
					return;
				}
			}

			// get max document from request document
			boost::optional<bsoncxx::types::b_document> max;

			try {
				max = request_document.view()["max"].get_document();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					// element is optional
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"max");
					rep.content.append(reply.c_str(),
							   reply.size());
					return;
				}
			}

			// get limit from request document
			boost::optional<size_t> limit_number;

			try {
				limit_number =
				request_document.view()["limit_number"]
					.get_int32();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					// element is optional
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"limit_number");
					rep.content.append(reply.c_str(),
							   reply.size());
					return;
				}
			}

			// get reply from database
			auto reply = dbaas::database::find(
			username,
			dbaas::database::password::check_key(client_key), query,
			projection, sort, min, max, limit_number);

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
