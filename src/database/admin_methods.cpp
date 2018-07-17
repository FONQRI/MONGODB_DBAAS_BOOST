// header
#include "admin_methods.h"

// std
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

// internal
#include "core/reply.h"

// mongocxx
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/stdx.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;
using bsoncxx::builder::basic::make_document;

std::string dbaas::database::admin::get_user(std::string username)
{

	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// check if user dose not exist
	try {
		bsoncxx::builder::basic::document filter_document{};
		filter_document.append(kvp("username", username));

		auto cursor = collection.find_one(filter_document.view());
		// return seccess message
		return core::reply::answer(bsoncxx::to_json(cursor.value()));
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::wrong_request_content_type(e.what());
	}

	return reply;
}

std::string dbaas::database::admin::increase_request_per_day(
	std::string username, std::string name, int request_per_day)
{
	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// if name is unique add key
	try {

		bsoncxx::builder::basic::document find_document{};

		find_document.append(kvp("username", username));
		find_document.append(kvp("keys.name", name));

		bsoncxx::builder::basic::document key_document{};

		bsoncxx::builder::basic::document update_document{};

		update_document.append(kvp(
		"$set",
		make_document(kvp("keys.$.request_per_day", request_per_day))));

		// create cursor bu qyery and options
		collection.update_one({find_document}, {update_document});

		// return seccess message
		return core::reply::answer_done();
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::user_creation_failed(e.what());
	}

	return reply;
}
