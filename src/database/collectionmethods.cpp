#include "collectionmethods.h"
#include "password.h"
#include "reply.h"

#include <chrono>
#include <iostream>

#include <iterator>
// TODO [3] use costume uri (real server and backups)

std::string dbaas::database::delete_many(
	std::string username, std::string database_name,
	bsoncxx::types::b_document query_document,
	boost::optional<bsoncxx::types::b_document> collation,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create collection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::delete_options options =
		mongocxx::options::delete_options{};
		if (collation.is_initialized()) {
			options.collation(collation.get().view());
		}

		if (journal.is_initialized() || majority.is_initialized() ||
			timeout.is_initialized() || nodes.is_initialized() ||
			tag.is_initialized() ||
			acknowledge_level.is_initialized()) {

			// create write_concern
			// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
			mongocxx::write_concern write_concern =
			mongocxx::write_concern();

			if (journal.is_initialized()) {
				write_concern.journal(journal.get());
			}
			if (majority.is_initialized()) {

				write_concern.majority(
				std::chrono::milliseconds(majority.get()));
			}

			if (timeout.is_initialized()) {
				write_concern.timeout(
				std::chrono::milliseconds(timeout.get()));
			}

			if (nodes.is_initialized()) {
				write_concern.nodes(nodes.get());
				write_concern.tag(
				mongocxx::stdx::string_view(tag.get()));
			}

			if (acknowledge_level.is_initialized()) {
				if (acknowledge_level.get() ==
					"k_acknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_default") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_majority") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_majority);
				}
				else if (acknowledge_level.get() == "k_tag") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::k_tag);
				}
				else if (acknowledge_level.get() ==
					 "k_unacknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_unacknowledged);
				}
			}

			// add created write_concern to options
			options.write_concern(write_concern);
		}

		// create cursor bu qyery and options
		collection.delete_many({query_document}, options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string dbaas::database::delete_one(
	std::string username, std::string database_name,
	bsoncxx::types::b_document query_document,
	boost::optional<bsoncxx::types::b_document> collation,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create collection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::delete_options options =
		mongocxx::options::delete_options{};

		if (collation.is_initialized()) {
			options.collation(collation.get().view());
		}

		if (journal.is_initialized() || majority.is_initialized() ||
			timeout.is_initialized() || nodes.is_initialized() ||
			tag.is_initialized() ||
			acknowledge_level.is_initialized()) {

			// create write_concern
			// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
			mongocxx::write_concern write_concern =
			mongocxx::write_concern();

			if (journal.is_initialized()) {
				write_concern.journal(journal.get());
			}
			if (majority.is_initialized()) {

				write_concern.majority(
				std::chrono::milliseconds(majority.get()));
			}

			if (timeout.is_initialized()) {
				write_concern.timeout(
				std::chrono::milliseconds(timeout.get()));
			}

			if (nodes.is_initialized()) {
				write_concern.nodes(nodes.get());
				write_concern.tag(
				mongocxx::stdx::string_view(tag.get()));
			}

			if (acknowledge_level.is_initialized()) {
				if (acknowledge_level.get() ==
					"k_acknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_default") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_majority") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_majority);
				}
				else if (acknowledge_level.get() == "k_tag") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::k_tag);
				}
				else if (acknowledge_level.get() ==
					 "k_unacknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_unacknowledged);
				}
			}

			// add created write_concern to options
			options.write_concern(write_concern);
		}

		// create cursor bu qyery and options
		collection.delete_one({query_document}, options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string dbaas::database::find_one_and_delete(
	std::string username, std::string database_name,
	bsoncxx::types::b_document query_document,
	boost::optional<bsoncxx::types::b_document> projection_document,
	boost::optional<bsoncxx::types::b_document> sort_document,
	boost::optional<bsoncxx::types::b_document> collation,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes, boost::optional<int> max_time)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::find_one_and_delete options =
		mongocxx::options::find_one_and_delete{};

		if (projection_document.is_initialized()) {
			options.projection(projection_document.get().view());
		}

		if (sort_document.is_initialized()) {

			options.sort(sort_document.get().view());
		}

		if (collation.is_initialized()) {
			options.collation(collation.get().view());
		}

		if (journal.is_initialized() || majority.is_initialized() ||
			timeout.is_initialized() || nodes.is_initialized() ||
			tag.is_initialized() ||
			acknowledge_level.is_initialized()) {

			// create write_concern
			// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
			mongocxx::write_concern write_concern =
			mongocxx::write_concern();

			if (journal.is_initialized()) {
				write_concern.journal(journal.get());
			}
			if (majority.is_initialized()) {

				write_concern.majority(
				std::chrono::milliseconds(majority.get()));
			}

			if (timeout.is_initialized()) {
				write_concern.timeout(
				std::chrono::milliseconds(timeout.get()));
			}

			if (nodes.is_initialized()) {
				write_concern.nodes(nodes.get());
				write_concern.tag(
				mongocxx::stdx::string_view(tag.get()));
			}

			if (acknowledge_level.is_initialized()) {
				if (acknowledge_level.get() ==
					"k_acknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_default") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_majority") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_majority);
				}
				else if (acknowledge_level.get() == "k_tag") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::k_tag);
				}
				else if (acknowledge_level.get() ==
					 "k_unacknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_unacknowledged);
				}
			}

			// add created write_concern to options
			options.write_concern(write_concern);
		}

		// add max_time to options
		if (max_time.is_initialized()) {
			options.max_time(std::chrono::milliseconds(max_time.get()));
		}

		// create cursor bu qyery and options
		collection.find_one_and_delete({query_document}, options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string dbaas::database::find(
	std::string username, std::string database_name,
	bsoncxx::types::b_document query_document,
	boost::optional<bsoncxx::types::b_document> projection_document,
	boost::optional<bsoncxx::types::b_document> sort_document,
	boost::optional<bsoncxx::types::b_document> min_document,
	boost::optional<bsoncxx::types::b_document> max_document,
	boost::optional<size_t> limit_number_of_docs)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::find options = mongocxx::options::find{};
		if (projection_document.is_initialized()) {
			options.projection(projection_document.get().view());
		}

		if (sort_document.is_initialized()) {
			options.sort(sort_document.get().view());
		}

		if (min_document.is_initialized()) {
			options.min(min_document.get().view());
		}

		if (max_document.is_initialized()) {
			options.max(max_document.get().view());
		}

		// limit number of docs
		if (limit_number_of_docs.is_initialized()) {
			options.limit(limit_number_of_docs.get());
		}

		auto cursor = collection.find({query_document}, options);
		std::string reply{};

		reply.append("[");
		for (auto &&doc : cursor) {
			reply.append(bsoncxx::to_json(doc) + ",");
		}

		// remove final "," character if ther is any element
		if (reply.size() > 2) {
			reply.erase(reply.size() - 1, 1);
		}

		reply.append("]");

		// make reply json
		return dbaas::database::reply::answer(reply);
	}
	catch (std::exception &e) {
		// make error json
		return reply::error(e.what());
	}
}

std::string dbaas::database::find_one(
	std::string username, std::string database_name,
	bsoncxx::types::b_document query_document,
	boost::optional<bsoncxx::types::b_document> projection_document,
	boost::optional<bsoncxx::types::b_document> sort_document,
	boost::optional<bsoncxx::types::b_document> min_document,
	boost::optional<bsoncxx::types::b_document> max_document)
{

	// create connection

	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::find options = mongocxx::options::find{};

		if (projection_document.is_initialized()) {
			options.projection(projection_document.get().view());
		}

		if (sort_document.is_initialized()) {
			options.sort(sort_document.get().view());
		}

		if (min_document.is_initialized()) {
			options.min(min_document.get().view());
		}

		if (max_document.is_initialized()) {
			options.max(max_document.get().view());
		}

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

std::string dbaas::database::count(std::string username,
				   std::string database_name,
				   bsoncxx::types::b_document query_document,
				   boost::optional<size_t> limit_number_of_docs,
				   boost::optional<size_t> skip_number_of_docs)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];

	try {

		// create option
		mongocxx::options::count options = mongocxx::options::count{};

		// limit number of docs
		if (limit_number_of_docs.is_initialized()) {
			options.limit(limit_number_of_docs.get());
		}

		// skip number of docs
		if (skip_number_of_docs.is_initialized()) {
			options.skip(skip_number_of_docs.get());
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

std::string dbaas::database::insert_many(
	std::string username, std::string database_name,
	std::vector<bsoncxx::document::value> insert_document_array,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes, boost::optional<bool> ordered,
	boost::optional<bool> bypass_document_validation)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	auto collection = connection[username][database_name];

	try {
		mongocxx::options::insert options;

		if (ordered.is_initialized()) {
			options.ordered(ordered.get());
		}

		if (journal.is_initialized() || majority.is_initialized() ||
			timeout.is_initialized() || nodes.is_initialized() ||
			tag.is_initialized() ||
			acknowledge_level.is_initialized()) {

			// create write_concern
			// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
			mongocxx::write_concern write_concern =
			mongocxx::write_concern();

			if (journal.is_initialized()) {
				write_concern.journal(journal.get());
			}
			if (majority.is_initialized()) {

				write_concern.majority(
				std::chrono::milliseconds(majority.get()));
			}

			if (timeout.is_initialized()) {
				write_concern.timeout(
				std::chrono::milliseconds(timeout.get()));
			}

			if (nodes.is_initialized()) {
				write_concern.nodes(nodes.get());
				write_concern.tag(
				mongocxx::stdx::string_view(tag.get()));
			}

			if (acknowledge_level.is_initialized()) {
				if (acknowledge_level.get() ==
					"k_acknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_default") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_majority") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_majority);
				}
				else if (acknowledge_level.get() == "k_tag") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::k_tag);
				}
				else if (acknowledge_level.get() ==
					 "k_unacknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_unacknowledged);
				}
			}

			// add created write_concern to options
			options.write_concern(write_concern);
		}

		// add bypass_document_validation to options
		if (bypass_document_validation.is_initialized()) {
			options.bypass_document_validation(
			bypass_document_validation.get());
		}
		collection.insert_many(insert_document_array, options);
		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {
		// make error json
		return reply::error(e.what());
	}
}

std::string dbaas::database::insert_one(
	std::string username, std::string database_name,
	bsoncxx::types::b_document insert_document,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes, boost::optional<bool> ordered,
	boost::optional<bool> bypass_document_validation)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	auto collection = connection[username][database_name];

	try {
		mongocxx::options::insert options;

		if (ordered.is_initialized()) {
			options.ordered(ordered.get());
		}

		if (journal.is_initialized() || majority.is_initialized() ||
			timeout.is_initialized() || nodes.is_initialized() ||
			tag.is_initialized() ||
			acknowledge_level.is_initialized()) {

			// create write_concern
			// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
			mongocxx::write_concern write_concern =
			mongocxx::write_concern();

			if (journal.is_initialized()) {
				write_concern.journal(journal.get());
			}
			if (majority.is_initialized()) {

				write_concern.majority(
				std::chrono::milliseconds(majority.get()));
			}

			if (timeout.is_initialized()) {
				write_concern.timeout(
				std::chrono::milliseconds(timeout.get()));
			}

			if (nodes.is_initialized()) {
				write_concern.nodes(nodes.get());
				write_concern.tag(
				mongocxx::stdx::string_view(tag.get()));
			}

			if (acknowledge_level.is_initialized()) {
				if (acknowledge_level.get() ==
					"k_acknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_default") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_majority") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_majority);
				}
				else if (acknowledge_level.get() == "k_tag") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::k_tag);
				}
				else if (acknowledge_level.get() ==
					 "k_unacknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_unacknowledged);
				}
			}

			// add created write_concern to options
			options.write_concern(write_concern);
		}

		// add bypass_document_validation to options
		if (bypass_document_validation.is_initialized()) {
			options.bypass_document_validation(
			bypass_document_validation.get());
		}

		collection.insert_one(insert_document.view(), options);
		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {
		// make error json
		return reply::error(e.what());
	}
}

std::string dbaas::database::find_one_and_replace(
	std::string username, std::string database_name,
	bsoncxx::types::b_document filter_document,
	bsoncxx::types::b_document replacement,
	boost::optional<bsoncxx::types::b_document> projection_document,
	boost::optional<bsoncxx::types::b_document> sort_document,
	boost::optional<bsoncxx::types::b_document> collation,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes, boost::optional<int> max_time,
	boost::optional<bool> upsert,
	boost::optional<bool> bypass_document_validation)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::find_one_and_replace options =
		mongocxx::options::find_one_and_replace{};

		if (projection_document.is_initialized()) {
			options.projection(projection_document.get().view());
		}

		if (sort_document.is_initialized()) {
			options.sort(sort_document.get().view());
		}

		if (collation.is_initialized()) {
			options.collation(collation.get().view());
		}

		if (upsert.is_initialized()) {
			options.upsert(upsert.get());
		}

		if (bypass_document_validation.is_initialized()) {
			options.bypass_document_validation(
			bypass_document_validation.get());
		}
		if (journal.is_initialized() || majority.is_initialized() ||
			timeout.is_initialized() || nodes.is_initialized() ||
			tag.is_initialized() ||
			acknowledge_level.is_initialized()) {

			// create write_concern
			// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
			mongocxx::write_concern write_concern =
			mongocxx::write_concern();

			if (journal.is_initialized()) {
				write_concern.journal(journal.get());
			}
			if (majority.is_initialized()) {

				write_concern.majority(
				std::chrono::milliseconds(majority.get()));
			}

			if (timeout.is_initialized()) {
				write_concern.timeout(
				std::chrono::milliseconds(timeout.get()));
			}

			if (nodes.is_initialized()) {
				write_concern.nodes(nodes.get());
				write_concern.tag(
				mongocxx::stdx::string_view(tag.get()));
			}

			if (acknowledge_level.is_initialized()) {
				if (acknowledge_level.get() ==
					"k_acknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_default") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_majority") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_majority);
				}
				else if (acknowledge_level.get() == "k_tag") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::k_tag);
				}
				else if (acknowledge_level.get() ==
					 "k_unacknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_unacknowledged);
				}
			}

			// add created write_concern to options
			options.write_concern(write_concern);
		}

		// add max_time to options
		options.max_time(std::chrono::milliseconds(max_time.get()));

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

std::string dbaas::database::find_one_and_update(
	std::string username, std::string database_name,
	bsoncxx::types::b_document filter_document,
	bsoncxx::types::b_document update_document,
	boost::optional<bsoncxx::types::b_document> projection_document,
	boost::optional<bsoncxx::types::b_document> sort_document,
	boost::optional<bsoncxx::types::b_document> collation,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes, boost::optional<int> max_time,
	boost::optional<bool> upsert)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::find_one_and_update options =
		mongocxx::options::find_one_and_update{};
		if (projection_document.is_initialized()) {
			options.projection(projection_document.get().view());
		}

		if (sort_document.is_initialized()) {
			options.sort(sort_document.get().view());
		}

		if (collation.is_initialized()) {
			options.collation(collation.get().view());
		}

		if (upsert.is_initialized()) {
			options.upsert(upsert.get());
		}

		if (journal.is_initialized() || majority.is_initialized() ||
			timeout.is_initialized() || nodes.is_initialized() ||
			tag.is_initialized() ||
			acknowledge_level.is_initialized()) {

			// create write_concern
			// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
			mongocxx::write_concern write_concern =
			mongocxx::write_concern();

			if (journal.is_initialized()) {
				write_concern.journal(journal.get());
			}
			if (majority.is_initialized()) {

				write_concern.majority(
				std::chrono::milliseconds(majority.get()));
			}

			if (timeout.is_initialized()) {
				write_concern.timeout(
				std::chrono::milliseconds(timeout.get()));
			}

			if (nodes.is_initialized()) {
				write_concern.nodes(nodes.get());
				write_concern.tag(
				mongocxx::stdx::string_view(tag.get()));
			}

			if (acknowledge_level.is_initialized()) {
				if (acknowledge_level.get() ==
					"k_acknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_default") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_majority") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_majority);
				}
				else if (acknowledge_level.get() == "k_tag") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::k_tag);
				}
				else if (acknowledge_level.get() ==
					 "k_unacknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_unacknowledged);
				}
			}

			// add created write_concern to options
			options.write_concern(write_concern);
		}

		// add max_time to options
		if (max_time.is_initialized()) {
			options.max_time(std::chrono::milliseconds(max_time.get()));
		}

		// create cursor bu qyery and options
		collection.find_one_and_update({update_document}, {filter_document},
					   options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string dbaas::database::update_many(
	std::string username, std::string database_name,
	bsoncxx::types::b_document filter_document,
	bsoncxx::types::b_document update_document,
	boost::optional<bsoncxx::types::b_document> collation,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes, boost::optional<bool> upsert,
	boost::optional<bool> bypass_document_validation)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::update options = mongocxx::options::update{};

		if (collation.is_initialized()) {
			options.collation(collation.get().view());
		}

		if (upsert.is_initialized()) {
			options.upsert(upsert.get());
		}

		if (bypass_document_validation.is_initialized()) {
			options.bypass_document_validation(
			bypass_document_validation.get());
		}

		if (journal.is_initialized() || majority.is_initialized() ||
			timeout.is_initialized() || nodes.is_initialized() ||
			tag.is_initialized() ||
			acknowledge_level.is_initialized()) {

			// create write_concern
			// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
			mongocxx::write_concern write_concern =
			mongocxx::write_concern();

			if (journal.is_initialized()) {
				write_concern.journal(journal.get());
			}
			if (majority.is_initialized()) {

				write_concern.majority(
				std::chrono::milliseconds(majority.get()));
			}

			if (timeout.is_initialized()) {
				write_concern.timeout(
				std::chrono::milliseconds(timeout.get()));
			}

			if (nodes.is_initialized()) {
				write_concern.nodes(nodes.get());
				write_concern.tag(
				mongocxx::stdx::string_view(tag.get()));
			}

			if (acknowledge_level.is_initialized()) {
				if (acknowledge_level.get() ==
					"k_acknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_default") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_majority") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_majority);
				}
				else if (acknowledge_level.get() == "k_tag") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::k_tag);
				}
				else if (acknowledge_level.get() ==
					 "k_unacknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_unacknowledged);
				}

				// add created write_concern to options
				options.write_concern(write_concern);
			}

			// add created write_concern to options
			options.write_concern(write_concern);
		}

		// create cursor bu qyery and options
		collection.update_many({filter_document}, {update_document},
				   options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}

std::string dbaas::database::update_one(
	std::string username, std::string database_name,
	bsoncxx::types::b_document filter_document,
	bsoncxx::types::b_document update_document,
	boost::optional<bsoncxx::types::b_document> collation,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes, boost::optional<bool> upsert,
	boost::optional<bool> bypass_document_validation)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	try {

		// create option
		mongocxx::options::update options = mongocxx::options::update{};

		if (collation.is_initialized()) {
			options.collation(collation.get().view());
		}

		if (upsert.is_initialized()) {
			options.upsert(upsert.get());
		}

		if (bypass_document_validation.is_initialized()) {
			options.bypass_document_validation(
			bypass_document_validation.get());
		}

		if (journal.is_initialized() || majority.is_initialized() ||
			timeout.is_initialized() || nodes.is_initialized() ||
			tag.is_initialized() ||
			acknowledge_level.is_initialized()) {

			// create write_concern
			// https://docs.mongodb.com/manual/reference/glossary/#term-write-concern
			mongocxx::write_concern write_concern =
			mongocxx::write_concern();

			if (journal.is_initialized()) {
				write_concern.journal(journal.get());
			}
			if (majority.is_initialized()) {

				write_concern.majority(
				std::chrono::milliseconds(majority.get()));
			}

			if (timeout.is_initialized()) {
				write_concern.timeout(
				std::chrono::milliseconds(timeout.get()));
			}

			if (nodes.is_initialized()) {
				write_concern.nodes(nodes.get());
				write_concern.tag(
				mongocxx::stdx::string_view(tag.get()));
			}

			if (acknowledge_level.is_initialized()) {
				if (acknowledge_level.get() ==
					"k_acknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_default") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_acknowledged);
				}
				else if (acknowledge_level.get() ==
					 "k_majority") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_majority);
				}
				else if (acknowledge_level.get() == "k_tag") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::k_tag);
				}
				else if (acknowledge_level.get() ==
					 "k_unacknowledged") {
					write_concern.acknowledge_level(
					mongocxx::write_concern::level::
						k_unacknowledged);
				}

				// add created write_concern to options
				options.write_concern(write_concern);
			}

			// add created write_concern to options
			options.write_concern(write_concern);
		}

		// create cursor bu qyery and options
		collection.update_one({filter_document}, {update_document},
				  options);

		return dbaas::database::reply::answer_done();
	}
	catch (std::exception &e) {

		// create json from error
		return reply::error(e.what());
	}
}
