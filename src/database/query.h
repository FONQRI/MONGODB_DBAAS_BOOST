#ifndef DATABASE_QUERY_H
#define DATABASE_QUERY_H
// mongo includes
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/model/insert_one.hpp>
#include <mongocxx/result/insert_one.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

namespace iotdb {
namespace database {

void insert_one(std::string username, std::string database_name,
		std::string insert_document);

std::string find_one(std::string username, std::string database_name,
			 std::string insert_document);

std::string find(std::string username, std::string database_name,
		 std::string insert_document);
}
}
#endif // DATABASE_QUERY_H
