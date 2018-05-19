#include "collectionmethods.h"
#include "password.h"
#include "reply.h"
#include <iostream>
// TODO [3] use costume uri (real server and backups)
std::string
dbaas::database::insert_one(std::string username, std::string database_name,
				bsoncxx::types::b_document insert_document)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	auto collection = connection[username][database_name];

	try {

		collection.insert_one(insert_document.view());
		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {
		// make error json
		return reply::error(e.what());
	}
}

std::string dbaas::database::insert_many(
	std::string username, std::string database_name,
	std::vector<bsoncxx::document::value> insert_document_array, bool ordered)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	auto collection = connection[username][database_name];

	try {
		mongocxx::options::insert options;

		options.ordered(ordered);
		collection.insert_many(insert_document_array, options);
		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {
		// make error json
		return reply::error(e.what());
	}
}

std::string
dbaas::database::find_one(std::string username, std::string database_name,
			  bsoncxx::types::b_document query_document,
			  bsoncxx::types::b_document projection_document,
			  bsoncxx::types::b_document sort_document,
			  bsoncxx::types::b_document min_document,
			  bsoncxx::types::b_document max_document)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::find options = mongocxx::options::find{};
		options.projection(projection_document.view());
		options.sort(sort_document.view());
		options.min(min_document.view());
		options.max(max_document.view());

		// create cursor bu qyery and options
		auto cursor = collection.find_one({query_document}, options);

		// create json string from response
		std::string reply = bsoncxx::to_json(cursor.value());

		// make reply json
		return dbaas::database::reply::answer(reply);
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string
dbaas::database::find(std::string username, std::string database_name,
			  bsoncxx::types::b_document query_document,
			  bsoncxx::types::b_document projection_document,
			  bsoncxx::types::b_document sort_document,
			  bsoncxx::types::b_document min_document,
			  bsoncxx::types::b_document max_document,
			  size_t limit_number_of_docs)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::find options = mongocxx::options::find{};
		options.projection(projection_document.view());
		options.sort(sort_document.view());
		options.min(min_document.view());
		options.max(max_document.view());

		// limit number of docs
		if (limit_number_of_docs != 0) {
			options.limit(limit_number_of_docs);
		}

		auto cursor = collection.find({query_document}, options);
		std::string reply{};
		reply.append("[");
		for (auto &&doc : cursor) {
			reply.append(bsoncxx::to_json(doc) + ",");
		}

		// remove final "," character
		reply.erase(reply.size() - 1, 1);

		reply.append("]");

		// make reply json
		return dbaas::database::reply::answer(reply);
	}
	catch (std::exception &e) {
		// make error json
		return reply::error(e.what());
	}
}

std::string dbaas::database::count(std::string username,
				   std::string database_name,
				   bsoncxx::types::b_document query_document,
				   size_t limit_number_of_docs,
				   size_t skip_number_of_docs)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];

	try {

		// create option
		mongocxx::options::count options = mongocxx::options::count{};

		// limit number of docs
		if (limit_number_of_docs != 0) {
			options.limit(limit_number_of_docs);
		}

		// skip number of docs
		if (skip_number_of_docs != 0) {
			options.skip(skip_number_of_docs);
		}

		auto cursor = collection.count({query_document}, options);
		std::string reply{};

		// make reply json
		return dbaas::database::reply::answer(std::to_string(cursor));
	}
	catch (std::exception &e) {
		// make error json
		return reply::error(e.what());
	}
}
