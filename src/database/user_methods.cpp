// header
#include "user_methods.h"

// std
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

#include "core/reply.h"

// mongocxx
#include <bsoncxx/builder/basic/array.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/stdx.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::sub_array;
using bsoncxx::builder::basic::make_document;

std::string dbaas::database::create_user(std::string username,
					 std::string password,
					 std::string primary_phone_number,
					 std::string primary_email,
					 optional_string_array phone_numbers,
					 optional_string_array emails)
{
	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// check if user dose not exist
	try {
		bsoncxx::builder::basic::document user_document{};
		// create new user
		user_document.append(kvp("username", username));
		user_document.append(kvp("password", password));
		user_document.append(
		kvp("primary_phone_number", primary_phone_number));
		user_document.append(kvp("primary_email", primary_email));

		if (phone_numbers.is_initialized()) {
			user_document.append(
			kvp("phone_numbers", [phone_numbers](sub_array child) {
				for (size_t i = 0; i < phone_numbers.get().size();
				 i++) {
				bsoncxx::stdx::string_view d =
					phone_numbers.get().at(i);
				child.append(d);
				}
			}));
		}

		if (emails.is_initialized()) {
			user_document.append(
			kvp("emails", [emails](sub_array child) {
				for (size_t i = 0; i < emails.get().size(); i++) {
				bsoncxx::stdx::string_view d =
					emails.get().at(i);
				child.append(d);
				}
			}));
		}

		// TODO p[4] add defult user key and fist user pyment as prize
		user_document.append(kvp("keys", [](sub_array child) {}));
		user_document.append(kvp("payments", [](sub_array child) {}));

		// get now time and date
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
		std::string signup_date_time = oss.str();

		user_document.append(kvp("signup_date_time", signup_date_time));

		collection.insert_one(user_document.view());
		// return seccess message
		return core::reply::answer_done();
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::user_creation_failed(e.what());
	}

	return reply;
}

std::string dbaas::database::update_user(
	std::string username, std::string password, optional_string update_username,
	optional_string update_password, optional_string primary_phone_number,
	optional_string primary_email, optional_string_array phone_numbers,
	optional_string_array emails)
{

	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// check if user dose not exist
	try {
		bsoncxx::builder::basic::document filter_document{};
		filter_document.append(kvp("username", username));
		filter_document.append(kvp("password", password));

		// create updated user
		bsoncxx::builder::basic::document user_document{};

		if (update_username.is_initialized()) {
			user_document.append(
			kvp("username", update_username.get()));
		}

		if (update_password.is_initialized()) {
			user_document.append(
			kvp("password", update_password.get()));
		}

		if (primary_phone_number.is_initialized()) {
			user_document.append(kvp("primary_phone_number",
						 primary_phone_number.get()));
		}

		if (primary_email.is_initialized()) {
			user_document.append(
			kvp("primary_email", primary_email.get()));
		}

		if (phone_numbers.is_initialized()) {
			user_document.append(
			kvp("phone_numbers", [phone_numbers](sub_array child) {
				for (size_t i = 0; i < phone_numbers.get().size();
				 i++) {
				bsoncxx::stdx::string_view d =
					phone_numbers.get().at(i);
				child.append(d);
				}
			}));
		}

		if (emails.is_initialized()) {
			user_document.append(
			kvp("emails", [emails](sub_array child) {
				for (size_t i = 0; i < emails.get().size(); i++) {
				bsoncxx::stdx::string_view d =
					emails.get().at(i);
				child.append(d);
				}
			}));
		}

		// get now time and date
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
		std::string update_date_time = oss.str();

		user_document.append(kvp("update_date_time", update_date_time));

		collection.update_one(filter_document.view(), user_document.view());
		// return seccess message
		return core::reply::answer_done();
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::user_creation_failed(e.what());
	}

	return reply;
}

std::string dbaas::database::get_user(std::string username,
					  std::string password)
{

	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// check if user dose not exist
	try {
		bsoncxx::builder::basic::document filter_document{};
		filter_document.append(kvp("username", username));
		filter_document.append(kvp("password", password));

		auto cursor = collection.find_one(filter_document.view());
		// return seccess message
		return core::reply::answer(bsoncxx::to_json(cursor.value()));
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::wrong_request_content_type(e.what());
	}

	return reply;
}

std::string dbaas::database::delete_user(std::string username,
					 std::string password)
{

	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// check if user dose not exist
	try {
		bsoncxx::builder::basic::document filter_document{};
		filter_document.append(kvp("username", username));
		filter_document.append(kvp("password", password));

		collection.delete_one(filter_document.view());
		// return seccess message
		return core::reply::answer_done();
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::wrong_request_content_type(e.what());
	}

	return reply;
}

std::string dbaas::database::create_key(
	std::string username, std::string password, std::string name,
	std::string database_name, int valid_requests_number, int valid_read_size,
	int valid_write_size, std::vector<std::string> access)
{
	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	//	// check if key dose not exist
	try {

		bsoncxx::builder::basic::document find_document{};

		find_document.append(kvp("username", username));
		find_document.append(kvp("password", password));
		find_document.append(kvp("keys.name", name));

		auto cursor = collection.find_one({find_document});

		// check if key name exist
		bsoncxx::to_json(cursor.value());
		return core::reply::duplicate_index("duplicate key.name");
	}
	catch (const std::exception &e) {
		// key name is unique
	}

	// if name is unique add key
	try {
		bsoncxx::builder::basic::document key_document{};

		// create new user
		key_document.append(kvp("name", name));
		key_document.append(kvp("database_name", database_name));
		key_document.append(kvp("request_per_day", 0));
		key_document.append(
		kvp("valid_requests_number", valid_requests_number));
		key_document.append(kvp("valid_read_size", valid_read_size));
		key_document.append(kvp("valid_write_size", valid_write_size));

		key_document.append(kvp("access_level", [access](sub_array child) {
		for (size_t i = 0; i < access.size(); i++) {
			bsoncxx::stdx::string_view d = access.at(i);
			child.append(d);
		}
		}));

		// get now time and date
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
		std::string create_date_time = oss.str();

		key_document.append(kvp("create_time", create_date_time));

		bsoncxx::builder::basic::document update_document{};

		update_document.append(
		kvp("$addToSet", make_document(kvp("keys", key_document))));

		bsoncxx::builder::basic::document filter_document{};

		filter_document.append(kvp("username", username));
		filter_document.append(kvp("password", password));

		// create cursor bu qyery and options
		collection.update_one({filter_document}, {update_document});

		// return seccess message
		return core::reply::answer_done();
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::user_creation_failed(e.what());
	}
}

std::string dbaas::database::update_key(
	std::string username, std::string password, std::string name,
	optional_string update_name, optional_string database_name,
	optional_int valid_requests_number, optional_int request_per_day,
	optional_int valid_read_size, optional_int valid_write_size,
	optional_string_array access)
{
	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// if name is unique add key
	try {

		bsoncxx::builder::basic::document find_document{};

		find_document.append(kvp("username", username));
		find_document.append(kvp("password", password));
		find_document.append(kvp("keys.name", name));

		bsoncxx::builder::basic::document key_document{};

		// get now time and date
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
		std::string update_date_time = oss.str();

		key_document.append(kvp("update_time", update_date_time));

		bsoncxx::builder::basic::document update_document{};

		//		update_document.append(
		//		kvp("$set", make_document(kvp("keys.$",
		// key_document))));

		// update user
		if (update_name.is_initialized()) {
			update_document.append(kvp(
			"$set",
			make_document(kvp("keys.$.name", update_name.get()))));
		}

		if (database_name.is_initialized()) {
			update_document.append(
			kvp("$set", make_document(kvp("keys.$.database_name",
							  database_name.get()))));
		}

		if (valid_requests_number.is_initialized()) {
			update_document.append(
			kvp("$set",
				make_document(kvp("keys.$.valid_requests_number",
						  valid_requests_number.get()))));
		}

		if (request_per_day.is_initialized()) {
			update_document.append(
			kvp("$set", make_document(kvp("keys.$.request_per_day",
							  request_per_day.get()))));
		}

		if (valid_read_size.is_initialized()) {
			update_document.append(
			kvp("$set", make_document(kvp("keys.$.valid_read_size",
							  valid_read_size.get()))));
		}

		if (valid_write_size.is_initialized()) {
			update_document.append(kvp(
			"$set", make_document(kvp("keys.$.valid_write_size",
						  valid_write_size.get()))));
		}

		// TODO P[0] update
		if (access.is_initialized()) {

			update_document.append(kvp(
			"$set",
			make_document(kvp(
				"keys.$.access_level", [access](sub_array child) {
				for (size_t i = 0; i < access.get().size();
					 i++) {
					bsoncxx::stdx::string_view d =
					access.get().at(i);
					child.append(d);
				}
				}))));

			//			key_document.append(
			//			kvp("access_level", ));
		}

		//		update_document.append(kvp(
		//		"$set", make_document(kvp("keys.$.name",
		// update_name.get()))));

		// create cursor bu qyery and options
		collection.update_one({find_document}, {update_document});

		// return seccess message
		return core::reply::answer_done();
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::user_creation_failed(e.what());
	}

	return reply;
}

std::string dbaas::database::get_user_key(std::string username,
					  std::string name)
{
	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// check if user dose not exist
	try {
		bsoncxx::builder::basic::document filter_document{};
		filter_document.append(kvp("username", username));
		filter_document.append(kvp("keys.name", name));

		auto cursor = collection.find_one(filter_document.view());

		// get query document of request
		bsoncxx::array::view array;
		std::string query_array{""};
		try {
			array = cursor->view()["keys"].get_array().value;

			// document vector
			for (auto &doc : array) {
				if (doc.get_document()
					.view()["name"]
					.get_utf8()
					.value.to_string() == name) {
					query_array =
					bsoncxx::to_json(doc.get_document());
				}
			}
		}
		catch (std::exception &e) {

			return core::reply::answer_not_found(e.what());
		}

		// return seccess message
		return core::reply::answer(query_array);
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::wrong_request_content_type(e.what());
	}

	return reply;
}

std::string dbaas::database::get_user_keys(std::string username,
					   std::string password)
{

	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// check if user dose not exist
	try {
		bsoncxx::builder::basic::document filter_document{};
		filter_document.append(kvp("username", username));
		filter_document.append(kvp("password", password));

		auto cursor = collection.find_one(filter_document.view());

		// get query document of request
		bsoncxx::array::view array;
		std::string query_array{""};
		try {
			array = cursor->view()["keys"].get_array().value;

			// document vector
			//			for (auto &doc : array) {
			//				if (doc.get_document()
			//					.view()["name"]
			//					.get_utf8()
			//					.value.to_string() ==
			// name)
			//{
			//					query_array =
			//					bsoncxx::to_json(doc.get_document());

			//				}
			//			}
		}
		catch (std::exception &e) {

			return core::reply::answer_not_found(e.what());
		}

		// return seccess message
		return core::reply::answer(bsoncxx::to_json(array));
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::wrong_request_content_type(e.what());
	}

	return reply;
}

std::string dbaas::database::delete_user_key(std::string username,
						 std::string password,
						 std::string name)
{

	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	try {

		bsoncxx::builder::basic::document update_document{};
		bsoncxx::builder::basic::document sub_update_document{};
		sub_update_document.append(kvp("name", name));
		update_document.append(
		kvp("$pull", make_document(kvp("keys", sub_update_document))));

		bsoncxx::builder::basic::document filter_document{};

		filter_document.append(kvp("username", username));
		filter_document.append(kvp("password", password));

		// create cursor bu qyery and options
		collection.update_one({filter_document}, {update_document});

		// return seccess message
		return core::reply::answer_done();
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::user_creation_failed(e.what());
	}

	return reply;
}

std::string dbaas::database::delete_user_keys(std::string username,
						  std::string password)
{

	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// delete keys
	try {

		bsoncxx::builder::basic::document update_document{};
		update_document.append(
		kvp("$unset", make_document(kvp("keys", ""))));

		bsoncxx::builder::basic::document filter_document{};
		filter_document.append(kvp("username", username));
		filter_document.append(kvp("password", password));

		// create cursor bu qyery and options
		collection.update_one({filter_document}, {update_document});

		// return seccess message
		return core::reply::answer_done();
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::user_creation_failed(e.what());
	}

	return reply;
}

std::string dbaas::database::create_payment(
	std::string username, std::string password, int main_value,
	optional_int discount_value, optional_string discount_type,
	int expiration_time, int request_numbers_per_day, int read_size,
	int write_size)
{

	// reply message
	std::string reply;

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// if name is unique add key
	try {
		bsoncxx::builder::basic::document key_document{};

		// create new user
		key_document.append(kvp("main_value", main_value));

		if (discount_value.is_initialized()) {
			key_document.append(
			kvp("discount_value", discount_value.get()));
		}

		if (discount_type.is_initialized()) {
			key_document.append(
			kvp("discount_type", discount_type.get()));
		}

		key_document.append(kvp("expiration_time", expiration_time));

		key_document.append(
		kvp("request_numbers_per_day", request_numbers_per_day));
		key_document.append(kvp("read_size", read_size));
		key_document.append(kvp("write_size", write_size));

		// get now time and date
		auto t = std::time(nullptr);
		auto tm = *std::localtime(&t);
		std::ostringstream oss;
		oss << std::put_time(&tm, "%d-%m-%Y %H-%M-%S");
		std::string create_date_time = oss.str();

		key_document.append(kvp("create_time", create_date_time));

		bsoncxx::builder::basic::document update_document{};

		update_document.append(
		kvp("$addToSet", make_document(kvp("payments", key_document))));

		bsoncxx::builder::basic::document filter_document{};

		filter_document.append(kvp("username", username));
		filter_document.append(kvp("password", password));

		// create cursor bu qyery and options
		collection.update_one({filter_document}, {update_document});

		// return seccess message
		return core::reply::answer_done();
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::user_creation_failed(e.what());
	}
}

std::string dbaas::database::get_payments(std::string username,
					  std::string password)
{

	// create connection
	mongocxx::client connection{mongocxx::uri{}};

	// database
	auto database = connection["server_admin"];

	// create collection
	auto collection = database["users"];

	// check if user dose not exist
	try {
		bsoncxx::builder::basic::document filter_document{};
		filter_document.append(kvp("username", username));
		filter_document.append(kvp("password", password));

		auto cursor = collection.find_one(filter_document.view());

		// get query document of request
		bsoncxx::array::view array;
		try {
			array = cursor->view()["payments"].get_array().value;
		}
		catch (std::exception &e) {

			return core::reply::answer_not_found(e.what());
		}

		// return seccess message
		return core::reply::answer(bsoncxx::to_json(array));
	}
	catch (const mongocxx::exception &e) {
		// create json from error
		return core::reply::wrong_request_content_type(e.what());
	}
}
