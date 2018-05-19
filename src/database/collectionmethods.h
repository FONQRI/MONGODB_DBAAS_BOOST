#ifndef DATABASE_QUERY_H
#define DATABASE_QUERY_H

// mongo includes
#include <bsoncxx/array/element.hpp>
#include <bsoncxx/array/value.hpp>
#include <bsoncxx/array/view.hpp>
#include <bsoncxx/array/view_or_value.hpp>
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

// TODO [0] change all strings to documnets
// TODO [1] fix insrt_many
namespace dbaas {
namespace database {

/**
* @brief insert_one
* @link
* https://docs.mongodb.com/manual/reference/method/db.collection.insertOne/
* @param username
* @param database_name
* @param insert_document
*/
std::string insert_one(std::string username, std::string database_name,
			   bsoncxx::types::b_document insert_document);

/**
* @brief insert
* @link https://docs.mongodb.com/manual/reference/method/db.collection.insert/
* @param username
* @param database_name
* @param insert_document
*/
std::string
insert_many(std::string username, std::string database_name,
		std::vector<bsoncxx::document::value> insert_document_array,
		bool ordered);
/**
 * @brief find_one find one answer
 * @link https://docs.mongodb.com/manual/reference/method/db.collection.find/
 * @param username
 * @param database_name
 * @param insert_document : query document
 * @return
 */
std::string find_one(std::string username, std::string database_name,
			 bsoncxx::types::b_document query_document,
			 bsoncxx::types::b_document projection_document,
			 bsoncxx::types::b_document sort_document,
			 bsoncxx::types::b_document min_document,
			 bsoncxx::types::b_document max_document);
/**
 * @brief find
 * @link https://docs.mongodb.com/manual/reference/method/db.collection.find/
 * @param username
 * @param database_name
 * @param insert_document
 * @return
 */
std::string find(std::string username, std::string database_name,
		 bsoncxx::types::b_document query_document,
		 bsoncxx::types::b_document projection_document,
		 bsoncxx::types::b_document sort_document,
		 bsoncxx::types::b_document min_document,
		 bsoncxx::types::b_document max_document,
		 size_t limit_number_of_docs = 0);

/**
 * @brief count\
 * @link https://docs.mongodb.com/manual/reference/method/db.collection.count/
 * @param username
 * @param database_name
 * @param insert_document
 * @return
 */
std::string count(std::string username, std::string database_name,
		  bsoncxx::types::b_document query_document,
		  size_t limit_number_of_docs = 0,
		  size_t skip_number_of_docs = 0);
}
}
#endif // DATABASE_QUERY_H
