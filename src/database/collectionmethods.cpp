#include "collectionmethods.h"

void iotdb::database::insert_one(std::string username,
				 std::string database_name,
				 std::string insert_document)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	auto collection = connection[username][database_name];
	bsoncxx::document::value document = bsoncxx::from_json(insert_document);

	// collection.insert_one(document.view());
	auto cursor = collection.find_one({});
	// std::cout << bsoncxx::to_json(cursor.value()) << std::endl;

	//	for (auto &&doc : cursor) {
	//		std::cout << bsoncxx::to_json(doc) << std::endl;
	//	}
}

std::string iotdb::database::find_one(std::string username,
					  std::string database_name,
					  std::string insert_document)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];
	bsoncxx::document::value document = bsoncxx::from_json(insert_document);
	auto cursor = collection.find_one({});

	return bsoncxx::to_json(cursor.value());
}

std::string iotdb::database::find(std::string username,
				  std::string database_name,
				  std::string insert_document)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];

	bsoncxx::document::value document = bsoncxx::from_json(insert_document);
	auto cursor = collection.find({document});
	std::string reply{};
	for (auto &&doc : cursor) {
		//			std::cout << bsoncxx::to_json(doc) << std::endl;
		reply.append(bsoncxx::to_json(doc));
	}
	return reply;
}

// TODO handle find
std::string iotdb::database::count(std::string username,
				   std::string database_name,
				   std::string insert_document)
{
	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// create xollection
	auto collection = connection[username][database_name];

	auto cursor = collection.count({});
	std::string reply{std::to_string(cursor)};

	return reply;
}
