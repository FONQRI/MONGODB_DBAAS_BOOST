#include "password.h"

// internal
#include "src/core/reply.h"
#include "src/database/admin_methods.h"
#include "src/database/user_methods.h"

// std
#include <algorithm>
#include <iostream>

bool dbaas::database::password::m_check_key(std::string username,
						std::string request_key_name,
						std::string &reply,
						std::string function_name)
{

	// get user from database
	bsoncxx::document::value user_reply_document =
	bsoncxx::from_json(dbaas::database::admin::get_user(username));

	if (!user_reply_document.view()["isSuccessful"].get_bool()) {
		// user not found
		reply = core::reply::user_does_not_exist(username);
		return false;
	}

	//	std::clog << bsoncxx::to_json(user_reply_document) << std::endl;
	bsoncxx::types::b_document user_document =
	user_reply_document.view()["Response"].get_document();

	// get query document of request
	try {
		bsoncxx::array::view keys_array;

		keys_array = user_document.view()["keys"].get_array().value;

		auto key = std::find_if(keys_array.begin(), keys_array.end(),
					[&request_key_name](auto &key) {
					return key.get_document()
						   .view()["name"]
						   .get_utf8()
						   .value.to_string() ==
						   request_key_name;
					});

		// check if key found
		if (key == keys_array.end()) {

			// key not found
			reply = core::reply::client_key_not_found(request_key_name);
			return false;
		}

		// check if user has access to this function
		auto key_document = key->get_document().view();

		bsoncxx::array::view access_array;

		access_array = key_document["access_level"].get_array().value;

		auto has_access = std::find_if(
		access_array.begin(), access_array.end(),
		[&function_name](auto &access) {
			return access.get_utf8().value.to_string() == function_name;
		});

		// check if key has access
		if (has_access == access_array.end()) {

			// key does not have access to function
			reply = core::reply::key_does_not_have_access_to_function(
			function_name);
			return false;
		}

		// TODO P[0] check limitation and update request_per day
		if (key_document["request_per_day"].get_int32() >=
			key_document["valid_request_per_day"].get_int32()) {

			// limit request number per day
			reply = core::reply::key_does_not_have_access_to_request();
			return false;
		}
		else {
			// update request_per_day + 1

			dbaas::database::admin::increase_request_per_day(
			username,
			key_document["name"].get_utf8().value.to_string(),
			key_document["request_per_day"].get_int32() + 1);
		}
		reply = key_document["database_name"].get_utf8().value.to_string();
	}
	catch (std::exception &e) {

		reply = core::reply::client_key_not_found(request_key_name);
		return false;
	}

	if (reply != "") {
		return true;
	}
	else {

		reply = core::reply::client_key_not_found(request_key_name);
		return false;
	}

	return false;
}
