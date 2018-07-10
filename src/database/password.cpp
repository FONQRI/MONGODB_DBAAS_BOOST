#include "password.h"
#include "src/database/reply.h"

#include <iostream>

bool dbaas::database::password::m_check_key(std::string key, std::string &reply,
						std::string function_name)
{
	std::clog << function_name << std::endl;
	reply = "dbname";

	if (reply != "") {
		return true;
	}
	else {
		reply = dbaas::database::reply::client_key_not_found(key);
		return false;
	}

	return false;
}
