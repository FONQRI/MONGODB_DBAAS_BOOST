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
