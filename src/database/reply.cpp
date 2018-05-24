#include "reply.h"

std::string dbaas::database::reply::error(std::string what)
{
	return "{\"isSuccessful\":false,\"Message\":\"" + what + "\"}";
}

std::string dbaas::database::reply::answer(std::string answer)
{
	return "{\"isSuccessful\":true,\"Response\":\"" + answer + "\"}";
}

std::string dbaas::database::reply::answer_done()
{
	return "{\"isSuccessful\":true}";
}

std::string dbaas::database::reply::missing_item_error(std::string item_name)
{
	return "{\"isSuccessful\":false,\"Message\":\"missing " + item_name + "\"}";
}

std::string dbaas::database::reply::wrong_item_type(std::string item_name)
{
	return "{\"isSuccessful\":false,\"Message\":\"wrong type " + item_name +
	   "\"}";
}
