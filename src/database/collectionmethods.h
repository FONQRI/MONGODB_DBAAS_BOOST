#ifndef DATABASE_QUERY_H
#define DATABASE_QUERY_H
// mongo includes
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/model/insert_one.hpp>
#include <mongocxx/options/count.hpp>
#include <mongocxx/result/insert_one.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

namespace iotdb {
namespace database {

/**
* @brief insert_one
* @link https://docs.mongodb.com/manual/reference/method/db.collection.insert/
* @param username
* @param database_name
* @param insert_document
*/
void insert_one(std::string username, std::string database_name,
		std::string insert_document);
/**
 * @brief find_one
 * @link https://docs.mongodb.com/manual/reference/method/db.collection.find/
 * @param username
 * @param database_name
 * @param insert_document
 * @return
 */
std::string find_one(std::string username, std::string database_name,
			 std::string insert_document);
/**
 * @brief find
 * @link https://docs.mongodb.com/manual/reference/method/db.collection.find/
 * @param username
 * @param database_name
 * @param insert_document
 * @return
 */
std::string find(std::string username, std::string database_name,
		 std::string insert_document);

/**
 * @brief count\
 * @link https://docs.mongodb.com/manual/reference/method/db.collection.count/
 * @param username
 * @param database_name
 * @param insert_document
 * @return
 */
std::string count(std::string username, std::string database_name,
		  std::string insert_document = "");
}
}
#endif // DATABASE_QUERY_H
