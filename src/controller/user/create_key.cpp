// header
#include "create_key.h"

// internal
#include "src/database/password.h"
#include "src/database/reply.h"
#include "src/database/user_methods.h"

// boost
#include <boost/optional.hpp>

// mongocxx
#include <mongocxx/exception/exception.hpp>

// std
#include <algorithm>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

void dbaas::core::create_key(http::server::reply &rep,
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

			// get username of request
			std::string username{""};
			// get client key of request
			std::string password{""};
			for (auto &header : request.headers) {
				if (header.name == "username") {
					username = header.value;
				}
				else if (header.name == "password") {
					password = header.value;
				}
			}
			if (username.empty()) {
				std::string reply =
				dbaas::database::reply::missing_item_error(
					"username");
				rep.content.append(reply.c_str(), reply.size());
				return;
			}
			else if (password.empty()) {
				std::string reply =
				dbaas::database::reply::missing_item_error(
					"password");
				rep.content.append(reply.c_str(), reply.size());
				return;
			}

			// convert content to json
			bsoncxx::document::value request_document =
			bsoncxx::from_json(request.content);

			// name
			std::string name;
			try {
				name = request_document.view()["name"]
					   .get_utf8()
					   .value.to_string();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					std::string reply = dbaas::database::reply::
					missing_item_error("name");
					rep.content.append(reply.c_str(),
							   reply.size());
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"name");
					rep.content.append(reply.c_str(),
							   reply.size());
				}
				return;
			}

			// valid_request_per_day
			int valid_request_per_day;
			try {
				valid_request_per_day =
				request_document.view()["valid_request_per_day"]
					.get_int32();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					std::string reply = dbaas::database::reply::
					missing_item_error(
						"valid_request_per_day");
					rep.content.append(reply.c_str(),
							   reply.size());
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"valid_request_per_day");
					rep.content.append(reply.c_str(),
							   reply.size());
				}
				return;
			}

			// valid_read_size
			int valid_read_size;
			try {
				valid_read_size =
				request_document.view()["valid_read_size"]
					.get_int32();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					std::string reply = dbaas::database::reply::
					missing_item_error("valid_read_size");
					rep.content.append(reply.c_str(),
							   reply.size());
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"valid_read_size");
					rep.content.append(reply.c_str(),
							   reply.size());
				}
				return;
			}

			// valid_read_size
			int valid_write_size;
			try {
				valid_write_size =
				request_document.view()["valid_write_size"]
					.get_int32();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					std::string reply = dbaas::database::reply::
					missing_item_error("valid_write_size");
					rep.content.append(reply.c_str(),
							   reply.size());
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"valid_write_size");
					rep.content.append(reply.c_str(),
							   reply.size());
				}
				return;
			}

			// get access array of request
			bsoncxx::array::view array;
			std::vector<std::string> access;
			try {
				array = request_document.view()["access"]
					.get_array()
					.value;

				// document vector
				for (auto &doc : array) {
					access.push_back(
					doc.get_utf8().value.to_string());
				}
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					std::string reply = dbaas::database::reply::
					missing_item_error("access");
					rep.content.append(reply.c_str(),
							   reply.size());
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"access");
					rep.content.append(reply.c_str(),
							   reply.size());
				}
				return;
			}

			// get reply from database
			auto reply = dbaas::database::create_key(
			username, password, name, valid_request_per_day,
			valid_read_size, valid_write_size, access);

			// write reply
			rep.content.append(reply.c_str(), reply.size());
		}
		else {
			// if request isn't post method
			std::string reply =
			dbaas::database::reply::http_error("send post method");

			// write reply
			rep.content.append(reply.c_str(), reply.size());
		}
	}
	catch (std::exception &e) {

		// if execption happend in getting values or parsing json
		std::string reply =
		dbaas::database::reply::wrong_request_content_type(e.what());

		// write reply
		rep.content.append(reply.c_str(), reply.size());
	}
}
