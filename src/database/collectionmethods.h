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

namespace dbaas {
namespace database {

/**
 * @brief delete_many		: <a
 * href="https://docs.mongodb.com/manual/reference/method/db.collection.deleteMany/">delete_many
 * mongodb</a>
 * @param username				: username of database
 * @param database_name			: database name of user
 * @param query_document		: BSON query document
 * @param collation				: <a
 * href="https://docs.mongodb.com/manual/reference/collation/index.html" >
 * collation mongodb </a>
 * @param acknowledge_level		: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param tag					: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param journal				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param majority				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param timeout				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param nodes					: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @return reply document as json at this format
 * : "{"isSuccessful":true,"Response":"success"}"
 * or this one for errors
 * :"{"isSuccessful":false,"Message":" + what happened + "}"
 */
std::string delete_many(std::string username, std::string database_name,
			bsoncxx::types::b_document query_document,
			bsoncxx::types::b_document collation,
			std::string acknowledge_level, std::string tag,
			bool journal, int majority, int timeout, int nodes);

/**
 * @brief delete_one		: <a
 * href="https://docs.mongodb.com/manual/reference/method/db.collection.deleteOne/">delete_one
 * mongodb</a>
 * @param username				: username of database
 * @param database_name			: database name of user
 * @param query_document		: BSON query document
 * @param collation				: <a
 * href="https://docs.mongodb.com/manual/reference/collation/index.html" >
 * collation mongodb </a>
 * @param acknowledge_level		: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param tag					: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param journal				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param majority				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param timeout				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param nodes					: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @return reply document as json at this format
 * : "{"isSuccessful":true,"Response":"success"}"
 * or this one for errors
 * :"{"isSuccessful":false,"Message":" + what happened + "}"
 */
std::string delete_one(std::string username, std::string database_name,
			   bsoncxx::types::b_document query_document,
			   bsoncxx::types::b_document collation,
			   std::string acknowledge_level, std::string tag,
			   bool journal, int majority, int timeout, int nodes);

/**
 * @brief find_one_and_delete	: <a href =
 * "https://docs.mongodb.com/manual/reference/method/db.collection.findOneAndDelete/">
 * find_one_and_delete mongodb </a>
 * @param username				: username of database
 * @param database_name			: database name of user
 * @param query_document		: BSON query document
 * @param projection_document	: BSON <a
 * href="https://docs.mongodb.com/manual/reference/glossary/#term-projection">
 * projection </a> document
 * @param sort_document			: BSON document to sort e.g.
 * {"value_name"= 1} or {"value_name"= -1}
 * @param collation				: <a
 * href="https://docs.mongodb.com/manual/reference/collation/index.html" >
 * collation mongodb </a>
 * @param acknowledge_level		: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param tag					: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param journal				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param majority				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param timeout				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param nodes					: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param max_time				: The max amount of running time
 * (in
 * milliseconds).
 * @return reply document as json at this format
 * : "{"isSuccessful":true,"Response":"success"}"
 * or this one for errors
 * :"{"isSuccessful":false,"Message":" + what happened + "}"
 */
std::string find_one_and_delete(std::string username, std::string database_name,
				bsoncxx::types::b_document query_document,
				bsoncxx::types::b_document projection_document,
				bsoncxx::types::b_document sort_document,
				bsoncxx::types::b_document collation,
				std::string acknowledge_level, std::string tag,
				bool journal, int majority, int timeout,
				int nodes, int max_time);

/**
 * @brief find					: <a href =
 * "https://docs.mongodb.com/manual/reference/method/db.collection.find/"> find
 * mongodb</a>
 * @param username				: username of database
 * @param database_name			: database name of user
 * @param query_document		: BSON query document
 * @param projection_document	: BSON <a
 * href="https://docs.mongodb.com/manual/reference/glossary/#term-projection">
 * projection </a> document
 * @param sort_document			: BSON document to sort e.g.
 * {"value_name"= 1} or {"value_name"= -1}
 * @param min_document			: BSON document that specify maximum of
 * every value
 * @param max_document			: BSON document that specify minimum of
 * every value
 * @param limit_number_of_docs	: limitation number of returned document
 * @return reply document as json at this format
 * : "{"isSuccessful":true,"Response":" + answer json array of documents +"}"
 * or this one for errors
 * :"{"isSuccessful":false,"Message":" + what happened + "}"
 */
std::string find(std::string username, std::string database_name,
		 bsoncxx::types::b_document query_document,
		 bsoncxx::types::b_document projection_document,
		 bsoncxx::types::b_document sort_document,
		 bsoncxx::types::b_document min_document,
		 bsoncxx::types::b_document max_document,
		 size_t limit_number_of_docs = 0);

/**
 * @brief find_one				:<a
 * href="https://docs.mongodb.com/manual/reference/method/db.collection.findOne/">
 * find_one mongodb a vector of documents</a>
 * @param username				: username of database
 * @param database_name			: database name of user
 * @param query_document		: BSON query document
 * @param projection_document	: BSON <a
 * href="https://docs.mongodb.com/manual/reference/glossary/#term-projection">
 * projection </a> document
 * @param sort_document			: BSON document to sort e.g.
 * {"value_name"= 1} or {"value_name"= -1}
 * @param min_document			: BSON document that specify maximum of
 * every value
 * @param max_document			: BSON document that specify minimum of
 * every value
 * @return reply document as json at this format
 * : "{"isSuccessful":true,"Response\":"+ answer json document + "}"
 * or this one for errors
 * :"{"isSuccessful":false,"Message":" + what happened + "}"
 */
std::string find_one(std::string username, std::string database_name,
			 bsoncxx::types::b_document query_document,
			 bsoncxx::types::b_document projection_document,
			 bsoncxx::types::b_document sort_document,
			 bsoncxx::types::b_document min_document,
			 bsoncxx::types::b_document max_document);

/**
 * @brief count					: <a
 * href="https://docs.mongodb.com/manual/reference/method/db.collection.count/">
 * count mongodb </a>
 * @param username				: username of database
 * @param database_name			: database name of user
 * @param query_document		: BSON query document
 * @param limit_number_of_docs	: limitation number of returned document
 * @param skip_number_of_docs	: how many document to skip before start
 * @return reply document as json at this format
 * : "{"isSuccessful":true,"Response":" + number +"}"
 * or this one for errors
 * :"{"isSuccessful":false,"Message":" + what happened + "}"
 */
std::string count(std::string username, std::string database_name,
		  bsoncxx::types::b_document query_document,
		  size_t limit_number_of_docs = 0,
		  size_t skip_number_of_docs = 0);

/**
 * @brief insert_many	: <a
 * href="https://docs.mongodb.com/manual/reference/method/db.collection.insertMany/">
 * insert_many mongodb</a> insert a vector of documents
 * @param username				: username of database
 * @param database_name			: database name of user
 * @param insert_document_array	: a vector of documents
 * @param ordered				: bool of ordered
 * @return answer reply
 */
// TODO [0] add writeConcern and update comment
std::string
insert_many(std::string username, std::string database_name,
		std::vector<bsoncxx::document::value> insert_document_array,
		std::string acknowledge_level, std::string tag, bool journal,
		int majority, int timeout, int nodes, bool ordered,
		bool bypass_document_validation);

/**
* @brief insert_one			: <a
* href="https://docs.mongodb.com/manual/reference/method/db.collection.insertOne/">
* insert_one mongodb</a> document
* @param username			: username of database
* @param database_name		: database name of user
* @param insert_document	: BSON document to insert
* @return answer reply
*/
std::string insert_one(std::string username, std::string database_name,
			   bsoncxx::types::b_document insert_document,
			   std::string acknowledge_level, std::string tag,
			   bool journal, int majority, int timeout, int nodes,
			   bool ordered, bool bypass_document_validation);

/**
 * @brief find_one_and_replace	: <a
 * href="https://docs.mongodb.com/manual/reference/method/db.collection.findOneAndReplace/">
 * find_one_and_replace mongodb</a>
 * @param username				: username of database
 * @param database_name			: database name of user
 * @param filter_document		: filter document
 * @param replacement			: replacement document
 * @param projection_document	: BSON <a
 * href="https://docs.mongodb.com/manual/reference/glossary/#term-projection">
 * projection </a> document
 * @param sort_document			: BSON document to sort e.g.
 * {"value_name"= 1} or {"value_name"= -1}
 * @param collation				: <a
 * href="https://docs.mongodb.com/manual/reference/collation/index.html" >
 * collation mongodb </a>
 * @param acknowledge_level		: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param tag					: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param journal				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param majority				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param timeout				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param nodes					: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param max_time				: The max amount of running time
 * @param upsert				: Sets the upsert option.
 * @return reply document as json at this format
 * : "{"isSuccessful":true,"Response":"success"}"
 * or this one for errors
 * :"{"isSuccessful":false,"Message":" + what happened + "}"
 */
std::string find_one_and_replace(std::string username,
				 std::string database_name,
				 bsoncxx::types::b_document filter_document,
				 bsoncxx::types::b_document replacement,
				 bsoncxx::types::b_document projection_document,
				 bsoncxx::types::b_document sort_document,
				 bsoncxx::types::b_document collation,
				 std::string acknowledge_level, std::string tag,
				 bool journal, int majority, int timeout,
				 int nodes, int max_time, bool upsert,
				 bool bypass_document_validation);

/**
 * @brief find_one_and_update	: <a
 * href="https://docs.mongodb.com/manual/reference/method/db.collection.findOneAndUpdate/">
 * find_one_and_update mongodb</a>
 * @param username				: username of database
 * @param database_name			: database name of user
 * @param filter_document		: filter document
 * @param update_document		: BSON query document
 * @param projection_document	: BSON <a
 * href="https://docs.mongodb.com/manual/reference/glossary/#term-projection">
 * projection </a> document
 * @param sort_document			: BSON document to sort e.g.
 * {"value_name"= 1} or {"value_name"= -1}
 * @param collation						: <a
 * href="https://docs.mongodb.com/manual/reference/collation/index.html" >
 * collation mongodb </a>
 * @param acknowledge_level				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param tag							: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param journal						: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param majority						: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param timeout						: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param nodes							: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param max_time						: The max amount
 * of
 * running
 * time
 * @param upsert						: Sets the
 * upsert
 * option.
 * @return reply document as json at this format
 * : "{"isSuccessful":true,"Response":"success"}"
 * or this one for errors
 * :"{"isSuccessful":false,"Message":" + what happened + "}"
 */
std::string find_one_and_update(std::string username, std::string database_name,
				bsoncxx::types::b_document filter_document,
				bsoncxx::types::b_document update_document,
				bsoncxx::types::b_document projection_document,
				bsoncxx::types::b_document sort_document,
				bsoncxx::types::b_document collation,
				std::string acknowledge_level, std::string tag,
				bool journal, int majority, int timeout,
				int nodes, int max_time, bool upsert);

/**
 * @brief update_many					:<a
 * href="https://docs.mongodb.com/manual/reference/method/db.collection.updateMany/">update_many
 * mongodb</a>
 * @param username						: username of
 * database
 * @param database_name					: database name of user
 * @param filter_document				: filter document
 * @param update_document				: BSON query document
 * @param collation						: <a
 * href="https://docs.mongodb.com/manual/reference/collation/index.html" >
 * collation mongodb </a>
 * @param acknowledge_level				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param tag							: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param journal						: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param majority						: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param timeout						: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param nodes							: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param upsert						: Sets the
 * upsert
 * option.
 * @param bypass_document_validation	: Sets the bypass_document_validation
 * option.
 * If true, allows the write to opt-out of document level validation.
 * @return reply document as json at this format
 * : "{"isSuccessful":true,"Response":"success"}"
 * or this one for errors
 * :"{"isSuccessful":false,"Message":" + what happened + "}"
 */
std::string update_many(std::string username, std::string database_name,
			bsoncxx::types::b_document filter_document,
			bsoncxx::types::b_document update_document,
			bsoncxx::types::b_document collation,
			std::string acknowledge_level, std::string tag,
			bool journal, int majority, int timeout, int nodes,
			bool upsert, bool bypass_document_validation);

/**
 * @brief update_many					:<a
 * href="https://docs.mongodb.com/manual/reference/method/db.collection.updateMany/">update_many
 * mongodb</a>
 * @param username						: username of
 * database
 * @param database_name					: database name of user
 * @param filter_document				: filter document
 * @param update_document				: BSON query document
 * @param collation						: <a
 * href="https://docs.mongodb.com/manual/reference/collation/index.html" >
 * collation mongodb </a>
 * @param acknowledge_level				: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param tag							: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param journal						: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param majority						: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param timeout						: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param nodes							: a value for <a
 * href="https://docs.mongodb.com/manual/reference/write-concern/index.html">
 * write-concern mongodb</a>
 * @param upsert						: Sets the
 * upsert
 * option.
 * @param bypass_document_validation	: Sets the bypass_document_validation
 * option.
 * If true, allows the write to opt-out of document level validation.
 * @return reply document as json at this format
 * : "{"isSuccessful":true,"Response":"success"}"
 * or this one for errors
 * :"{"isSuccessful":false,"Message":" + what happened + "}"
 */
std::string update_one(std::string username, std::string database_name,
			   bsoncxx::types::b_document filter_document,
			   bsoncxx::types::b_document update_document,
			   bsoncxx::types::b_document collation,
			   std::string acknowledge_level, std::string tag,
			   bool journal, int majority, int timeout, int nodes,
			   bool upsert, bool bypass_document_validation);

} // dbaas
} // database

#endif // DATABASE_QUERY_H
