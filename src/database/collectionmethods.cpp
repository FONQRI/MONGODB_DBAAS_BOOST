#include "collectionmethods.h"
#include "password.h"
#include "reply.h"

#include <chrono>
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

std::string dbaas::database::find_one_and_delete(
	std::string username, std::string database_name,
	bsoncxx::types::b_document query_document,
	bsoncxx::types::b_document projection_document,
	bsoncxx::types::b_document sort_document,
	bsoncxx::types::b_document collation, std::string acknowledge_level,
	std::string tag, bool journal, int majority, int timeout, int nodes,
	int max_time)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::find_one_and_delete options =
		mongocxx::options::find_one_and_delete{};
		options.projection(projection_document.view());
		options.sort(sort_document.view());
		options.collation(collation.view());

		// create write_concern
		// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
		mongocxx::write_concern write_concern = mongocxx::write_concern();

		write_concern.journal(journal);
		write_concern.majority(std::chrono::milliseconds(majority));
		write_concern.timeout(std::chrono::milliseconds(timeout));
		write_concern.nodes(nodes);
		write_concern.tag(mongocxx::stdx::string_view(tag));

		if (acknowledge_level == "k_acknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_default") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_majority") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_majority);
		}
		else if (acknowledge_level == "k_tag") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_tag);
		}
		else if (acknowledge_level == "k_unacknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_unacknowledged);
		}

		// add created write_concern to options
		options.write_concern(write_concern);

		// add max_time to options
		options.max_time(std::chrono::milliseconds(max_time));

		// create cursor bu qyery and options
		collection.find_one_and_delete({query_document}, options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string
dbaas::database::delete_many(std::string username, std::string database_name,
				 bsoncxx::types::b_document query_document,
				 bsoncxx::types::b_document collation,
				 std::string acknowledge_level, std::string tag,
				 bool journal, int majority, int timeout, int nodes)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create collection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::delete_options options =
		mongocxx::options::delete_options{};

		options.collation(collation.view());

		// create write_concern
		// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
		mongocxx::write_concern write_concern = mongocxx::write_concern();

		write_concern.journal(journal);
		write_concern.majority(std::chrono::milliseconds(majority));
		write_concern.timeout(std::chrono::milliseconds(timeout));
		write_concern.nodes(nodes);
		write_concern.tag(mongocxx::stdx::string_view(tag));

		if (acknowledge_level == "k_acknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_default") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_majority") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_majority);
		}
		else if (acknowledge_level == "k_tag") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_tag);
		}
		else if (acknowledge_level == "k_unacknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_unacknowledged);
		}

		// add created write_concern to options
		options.write_concern(write_concern);

		// create cursor bu qyery and options
		collection.delete_many({query_document}, options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string
dbaas::database::delete_one(std::string username, std::string database_name,
				bsoncxx::types::b_document query_document,
				bsoncxx::types::b_document collation,
				std::string acknowledge_level, std::string tag,
				bool journal, int majority, int timeout, int nodes)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create collection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::delete_options options =
		mongocxx::options::delete_options{};

		options.collation(collation.view());

		// create write_concern

		// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
		mongocxx::write_concern write_concern = mongocxx::write_concern();

		write_concern.journal(journal);
		write_concern.majority(std::chrono::milliseconds(majority));
		write_concern.timeout(std::chrono::milliseconds(timeout));
		write_concern.nodes(nodes);
		write_concern.tag(mongocxx::stdx::string_view(tag));

		if (acknowledge_level == "k_acknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_default") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_majority") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_majority);
		}
		else if (acknowledge_level == "k_tag") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_tag);
		}
		else if (acknowledge_level == "k_unacknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_unacknowledged);
		}

		// add created write_concern to options
		options.write_concern(write_concern);

		// create cursor bu qyery and options
		collection.delete_one({query_document}, options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string dbaas::database::find_one_and_update(
	std::string username, std::string database_name,
	bsoncxx::types::b_document filter_document,
	bsoncxx::types::b_document query_document,
	bsoncxx::types::b_document projection_document,
	bsoncxx::types::b_document sort_document,
	bsoncxx::types::b_document collation, std::string acknowledge_level,
	std::string tag, bool journal, int majority, int timeout, int nodes,
	int max_time, bool upsert)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::find_one_and_update options =
		mongocxx::options::find_one_and_update{};
		options.projection(projection_document.view());
		options.sort(sort_document.view());
		options.collation(collation.view());
		options.upsert(upsert);

		// create write_concern
		// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
		mongocxx::write_concern write_concern = mongocxx::write_concern();

		write_concern.journal(journal);
		write_concern.majority(std::chrono::milliseconds(majority));
		write_concern.timeout(std::chrono::milliseconds(timeout));
		write_concern.nodes(nodes);
		write_concern.tag(mongocxx::stdx::string_view(tag));

		if (acknowledge_level == "k_acknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_default") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_majority") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_majority);
		}
		else if (acknowledge_level == "k_tag") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_tag);
		}
		else if (acknowledge_level == "k_unacknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_unacknowledged);
		}

		// add created write_concern to options
		options.write_concern(write_concern);

		// add max_time to options
		options.max_time(std::chrono::milliseconds(max_time));

		// create cursor bu qyery and options
		collection.find_one_and_update({query_document}, {filter_document},
					   options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string dbaas::database::find_one_and_replace(
	std::string username, std::string database_name,
	bsoncxx::types::b_document filter_document,
	bsoncxx::types::b_document replacement,
	bsoncxx::types::b_document projection_document,
	bsoncxx::types::b_document sort_document,
	bsoncxx::types::b_document collation, std::string acknowledge_level,
	std::string tag, bool journal, int majority, int timeout, int nodes,
	int max_time, bool upsert, bool bypass_document_validation)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::find_one_and_replace options =
		mongocxx::options::find_one_and_replace{};
		options.projection(projection_document.view());
		options.sort(sort_document.view());
		options.collation(collation.view());
		options.upsert(upsert);
		options.bypass_document_validation(bypass_document_validation);

		// create write_concern
		// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
		mongocxx::write_concern write_concern = mongocxx::write_concern();

		write_concern.journal(journal);
		write_concern.majority(std::chrono::milliseconds(majority));
		write_concern.timeout(std::chrono::milliseconds(timeout));
		write_concern.nodes(nodes);
		write_concern.tag(mongocxx::stdx::string_view(tag));

		if (acknowledge_level == "k_acknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_default") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_majority") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_majority);
		}
		else if (acknowledge_level == "k_tag") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_tag);
		}
		else if (acknowledge_level == "k_unacknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_unacknowledged);
		}

		// add created write_concern to options
		options.write_concern(write_concern);

		// add max_time to options
		options.max_time(std::chrono::milliseconds(max_time));

		// create cursor bu qyery and options
		collection.find_one_and_replace({filter_document}, {replacement},
						options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string
dbaas::database::update_many(std::string username, std::string database_name,
				 bsoncxx::types::b_document filter_document,
				 bsoncxx::types::b_document query_document,
				 bsoncxx::types::b_document collation,
				 std::string acknowledge_level, std::string tag,
				 bool journal, int majority, int timeout, int nodes,
				 bool upsert, bool bypass_document_validation)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::update options = mongocxx::options::update{};
		options.collation(collation.view());
		options.upsert(upsert);
		options.bypass_document_validation(bypass_document_validation);

		// create write_concern
		// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
		mongocxx::write_concern write_concern = mongocxx::write_concern();

		write_concern.journal(journal);
		write_concern.majority(std::chrono::milliseconds(majority));
		write_concern.timeout(std::chrono::milliseconds(timeout));
		write_concern.nodes(nodes);
		write_concern.tag(mongocxx::stdx::string_view(tag));

		if (acknowledge_level == "k_acknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_default") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_majority") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_majority);
		}
		else if (acknowledge_level == "k_tag") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_tag);
		}
		else if (acknowledge_level == "k_unacknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_unacknowledged);
		}

		// add created write_concern to options
		options.write_concern(write_concern);

		// create cursor bu qyery and options
		collection.update_many({filter_document}, {query_document},
				   options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string
dbaas::database::update_one(std::string username, std::string database_name,
				bsoncxx::types::b_document filter_document,
				bsoncxx::types::b_document query_document,
				bsoncxx::types::b_document collation,
				std::string acknowledge_level, std::string tag,
				bool journal, int majority, int timeout, int nodes,
				bool upsert, bool bypass_document_validation)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::update options = mongocxx::options::update{};
		options.collation(collation.view());
		options.upsert(upsert);
		options.bypass_document_validation(bypass_document_validation);

		// create write_concern
		// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
		mongocxx::write_concern write_concern = mongocxx::write_concern();

		write_concern.journal(journal);
		write_concern.majority(std::chrono::milliseconds(majority));
		write_concern.timeout(std::chrono::milliseconds(timeout));
		write_concern.nodes(nodes);
		write_concern.tag(mongocxx::stdx::string_view(tag));

		if (acknowledge_level == "k_acknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_default") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_acknowledged);
		}
		else if (acknowledge_level == "k_majority") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_majority);
		}
		else if (acknowledge_level == "k_tag") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_tag);
		}
		else if (acknowledge_level == "k_unacknowledged") {
			write_concern.acknowledge_level(
			mongocxx::write_concern::level::k_unacknowledged);
		}

		// add created write_concern to options
		options.write_concern(write_concern);

		// create cursor bu qyery and options
		collection.update_one({filter_document}, {query_document}, options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}
