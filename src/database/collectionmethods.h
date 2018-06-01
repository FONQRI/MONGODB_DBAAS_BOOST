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

#include <boost/optional.hpp>

namespace dbaas {
namespace database {

typedef boost::optional<bool> optional_bool;
typedef boost::optional<bsoncxx::types::b_document> optional_ducument;
typedef boost::optional<std::string> optional_string;
typedef boost::optional<int> optional_int;
typedef boost::optional<size_t> optional_size;

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
			boost::optional<bsoncxx::types::b_document> collation,
			boost::optional<std::string> acknowledge_level,
			boost::optional<std::string> tag,
			boost::optional<bool> journal,
			boost::optional<int> majority,
			boost::optional<int> timeout,
			boost::optional<int> nodes);

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
			   boost::optional<bsoncxx::types::b_document> collation,
			   boost::optional<std::string> acknowledge_level,
			   boost::optional<std::string> tag,
			   boost::optional<bool> journal,
			   boost::optional<int> majority,
			   boost::optional<int> timeout,
			   boost::optional<int> nodes);

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
std::string find_one_and_delete(
	std::string username, std::string database_name,
	bsoncxx::types::b_document query_document,
	boost::optional<bsoncxx::types::b_document> projection_document,
	boost::optional<bsoncxx::types::b_document> sort_document,
	boost::optional<bsoncxx::types::b_document> collation,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes, boost::optional<int> max_time);

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
std::string
find(std::string username, std::string database_name,
	 bsoncxx::types::b_document query_document,
	 boost::optional<bsoncxx::types::b_document> projection_document,
	 boost::optional<bsoncxx::types::b_document> sort_document,
	 boost::optional<bsoncxx::types::b_document> min_document,
	 boost::optional<bsoncxx::types::b_document> max_document,
	 boost::optional<size_t> limit_number_of_docs = 0);

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
std::string
find_one(std::string username, std::string database_name,
	 bsoncxx::types::b_document query_document,
	 boost::optional<bsoncxx::types::b_document> projection_document,
	 boost::optional<bsoncxx::types::b_document> sort_document,
	 boost::optional<bsoncxx::types::b_document> min_document,
	 boost::optional<bsoncxx::types::b_document> max_document);

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
		  boost::optional<size_t> limit_number_of_docs = 0,
		  boost::optional<size_t> skip_number_of_docs = 0);

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
		boost::optional<std::string> acknowledge_level,
		boost::optional<std::string> tag, boost::optional<bool> journal,
		boost::optional<int> majority, boost::optional<int> timeout,
		boost::optional<int> nodes, boost::optional<bool> ordered,
		boost::optional<bool> bypass_document_validation);

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
			   boost::optional<std::string> acknowledge_level,
			   boost::optional<std::string> tag,
			   boost::optional<bool> journal,
			   boost::optional<int> majority,
			   boost::optional<int> timeout, boost::optional<int> nodes,
			   boost::optional<bool> ordered,
			   boost::optional<bool> bypass_document_validation);

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
std::string find_one_and_replace(
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
	boost::optional<bool> bypass_document_validation);

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
std::string find_one_and_update(
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
	boost::optional<bool> upsert);

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
std::string
update_many(std::string username, std::string database_name,
		bsoncxx::types::b_document filter_document,
		bsoncxx::types::b_document update_document,
		boost::optional<bsoncxx::types::b_document> collation,
		boost::optional<std::string> acknowledge_level,
		boost::optional<std::string> tag, boost::optional<bool> journal,
		boost::optional<int> majority, boost::optional<int> timeout,
		boost::optional<int> nodes, boost::optional<bool> upsert,
		boost::optional<bool> bypass_document_validation);

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
			   boost::optional<bsoncxx::types::b_document> collation,
			   boost::optional<std::string> acknowledge_level,
			   boost::optional<std::string> tag,
			   boost::optional<bool> journal,
			   boost::optional<int> majority,
			   boost::optional<int> timeout, boost::optional<int> nodes,
			   boost::optional<bool> upsert,
			   boost::optional<bool> bypass_document_validation);

/**
 * @brief drop			: drop a collection <a href=
 * "https://docs.mongodb.com/manual/reference/method/db.collection.drop/#db.collection.drop">
 * drop mongodb </a>
 * @param username		: username
 * @param database_name	: collection name
 * @return				: success or failure message
 */
std::string drop(std::string username, std::string database_name);

/**
 * @brief create_index				: <a
 * href="https://docs.mongodb.com/manual/reference/method/db.collection.createIndex/">
 * create_index mongodb </a>
 * @param username				   	: username of database
 * @param database_name			   	: database name of user
 * @param index_document		   	: index_document
 * @param options_is_set		   	: true if options document is
 * set
 * from
 * user side in request
 * @param background			   	: background of options
 * @param unique				   	: unique of options
 * @param sparse				   	: sparse of options
 * @param version				   	: version of options
 * @param twod_sphere_version	   	: twod_sphere_version of options
 * @param twod_bits_precision	   	: twod_bits_precision of options
 * @param twod_location_max		   	: twod_location_max of options
 * @param twod_location_min		   	: twod_location_min of options
 * @param haystack_bucket_size	   	: haystack_bucket_size of options
 * @param expire_after			   	: expire_after of options
 * @param name					   	: name of options
 * @param default_language		   	: default_language of options
 * @param language_override		   	: language_override of options
 * @param collation				   	: collation of options
 * @param weights				   	: weights of options
 * @param partial_filter_expression	: partial_filter_expression of options
 * @param max_time				   	: max_time of
 * operation_options
 * @param acknowledge_level		   	: acknowledge_level of
 * write_concern
 * @param tag					   	: tag of write_concern
 * @param journal				   	: journal of
 * write_concern
 * @param majority				   	: majority of
 * write_concern
 * @param timeout				   	: timeout of
 * write_concern
 * @param nodes					   	: nodes of write_concern
 * @return							: success or
 * failure
 * message
 */
std::string create_index(
	std::string username, std::string database_name,
	bsoncxx::types::b_document index_document, bool options_is_set,
	boost::optional<bool> background, boost::optional<bool> unique,
	boost::optional<bool> sparse, boost::optional<std::int32_t> version,
	boost::optional<std::uint8_t> twod_sphere_version,
	boost::optional<std::uint8_t> twod_bits_precision,
	boost::optional<double> twod_location_max,
	boost::optional<double> twod_location_min,
	boost::optional<double> haystack_bucket_size,
	boost::optional<size_t> expire_after, boost::optional<std::string> name,
	boost::optional<std::string> default_language,
	boost::optional<std::string> language_override,
	boost::optional<bsoncxx::types::b_document> collation,
	boost::optional<bsoncxx::types::b_document> weights,
	boost::optional<bsoncxx::types::b_document> partial_filter_expression,
	boost::optional<size_t> max_time,
	boost::optional<std::string> acknowledge_level,
	boost::optional<std::string> tag, boost::optional<bool> journal,
	boost::optional<int> majority, boost::optional<int> timeout,
	boost::optional<int> nodes);
/**
 * @brief name			: return name of collection
 * @param username		: username of database
 * @param database_name	: database name of user
 * @return				: name of collection in json
 */
std::string name(std::string username, std::string database_name);

/**
 * @brief list_indexes	: return an array of indexes of specific collection
 * @param username		: username of database
 * @param database_name	: database name of user
 * @return 				: an array of indexes of collection
 */
std::string list_indexes(std::string username, std::string database_name);

std::string distinct(std::string username, std::string database_name,
			 std::string name_string,
			 bsoncxx::types::b_document filter_document,
			 boost::optional<bsoncxx::types::b_document> collation,
			 boost::optional<size_t> max_time);

std::string
aggregate(std::string username, std::string database_name,
	  optional_bool allow_disk_use, optional_bool use_cursor,
	  optional_bool bypass_document_validation, optional_size max_time,
	  optional_int batch_size, optional_ducument collation,
	  optional_string acknowledge_level, optional_string tag,
	  optional_bool journal, optional_int majority, optional_int timeout,
	  optional_int nodes, optional_ducument hint, optional_string hint_str,
	  optional_int limit, optional_int sample, optional_int skip,
	  optional_string out, optional_string count,
	  optional_ducument add_fields, optional_ducument bucket,
	  optional_ducument bucket_auto, optional_ducument coll_stats,
	  optional_ducument facet, optional_ducument geo_near,
	  optional_ducument graph_lookup, optional_ducument group,
	  optional_bool index_stats, optional_ducument lookup,
	  optional_ducument match, optional_ducument project,
	  optional_ducument redact, optional_ducument replace_root,
	  optional_ducument sort, optional_ducument sort_by_count,
	  optional_string sort_by_count_str, optional_ducument unwind,
	  optional_string unwind_str);
} // dbaas
} // database

#endif // DATABASE_QUERY_H
