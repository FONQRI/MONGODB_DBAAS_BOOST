#include "collectionmethods.h"
#include "password.h"
#include "reply.h"
#include <iostream>
// TODO [3] use costume uri (real server and backups)
std::string dbaas::database::insert_one(std::string username,
					std::string database_name,
					std::string insert_document)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	auto collection = connection[username][database_name];

	try {

		bsoncxx::document::value document =
		bsoncxx::from_json(insert_document);

		collection.insert_one(document.view());
	}
	catch (std::exception &e) {
		// make error json
		return reply::error(e.what());
	}
	return dbaas::database::reply::answer_done();
}

std::string dbaas::database::insert_many(std::string username,
					 std::string database_name,
					 std::string insert_document)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	auto collection = connection[username][database_name];

	try {

		bsoncxx::document::value document =
		bsoncxx::from_json(insert_document);

		// BUG use a vector for arg in insert_many
		// TODO [1]uncomment below line
		// collection.insert_many(document.view());
	}
	catch (std::exception &e) {
		// make error json
		return reply::error(e.what());
	}
	return dbaas::database::reply::answer_done();
}

std::string dbaas::database::find_one(std::string username,
					  std::string database_name,
					  std::string query_document_json,
					  std::string projection_document_json,
					  std::string sort_document_json,
					  std::string min_document_json,
					  std::string max_document_json)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create query document from json
		bsoncxx::document::value document =
		bsoncxx::from_json(query_document_json);

		// create projection document from json
		bsoncxx::document::value projection_document =
		bsoncxx::from_json(projection_document_json);

		// create sort document from json
		bsoncxx::document::value sort_document =
		bsoncxx::from_json(sort_document_json);

		// create min document from json
		bsoncxx::document::value min_document =
		bsoncxx::from_json(min_document_json);

		// create max document from json
		bsoncxx::document::value max_document =
		bsoncxx::from_json(max_document_json);

		// create option
		mongocxx::options::find options = mongocxx::options::find{};
		options.projection(projection_document.view());
		options.sort(sort_document.view());
		options.min(min_document.view());
		options.max(max_document.view());

		// create cursor bu qyery and options
		auto cursor = collection.find_one({document}, options);

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

std::string dbaas::database::find(
	std::string username, std::string database_name,
	std::string query_document_json, std::string projection_document_json,
	std::string sort_document_json, std::string min_document_json,
	std::string max_document_json, size_t limit_number_of_docs)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {
		bsoncxx::document::value document =
		bsoncxx::from_json(query_document_json);

		// create projection document from json
		bsoncxx::document::value projection_document =
		bsoncxx::from_json(projection_document_json);

		// create sort document from json
		bsoncxx::document::value sort_document =
		bsoncxx::from_json(sort_document_json);

		// create min document from json
		bsoncxx::document::value min_document =
		bsoncxx::from_json(min_document_json);

		// create max document from json
		bsoncxx::document::value max_document =
		bsoncxx::from_json(max_document_json);

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

		auto cursor = collection.find({document}, options);
		std::string reply{};
		reply.append("{[");
		for (auto &&doc : cursor) {
			//			std::cout << bsoncxx::to_json(doc) <<
			// std::endl;
			reply.append(bsoncxx::to_json(doc) + ",");
		}
		reply.append("]}");

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
				   std::string query_document_json,
				   size_t limit_number_of_docs,
				   size_t skip_number_of_docs)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];

	try {
		bsoncxx::document::value document =
		bsoncxx::from_json(query_document_json);

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

		auto cursor = collection.count({document}, options);
		std::string reply{};

		// make reply json
		return dbaas::database::reply::answer(std::to_string(cursor));
	}
	catch (std::exception &e) {
		// make error json
		return reply::error(e.what());
	}
}
