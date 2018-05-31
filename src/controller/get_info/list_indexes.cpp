// header
#include "list_indexes.h"

// internal
#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include "src/database/reply.h"

// boost
#include <boost/optional.hpp>

// std
#include <iostream>
#include <vector>

void dbaas::core::list_indexes(http::server::reply &rep, http::server::request request)
{
  // add headers
  //	specifying content type as json
  http::server::header content_type;
  content_type.name = "Content-Type";
  content_type.value = "application/json;";

  //	specifying content charset as utf-8
  http::server::header charset;
  charset.name = "charset";
  charset.value = "utf-8";

  // putting headers into reply
  rep.headers.push_back(content_type);
  rep.headers.push_back(charset);

  try {
    // check if request is post
    if (request.method == "POST") {

      // get username of request
      std::string username{""};

      // get client key of request
      std::string client_key{""};
      for (auto &header : request.headers) {
        if (strcmp(header.name.c_str(), "username") ==
          0) {
          username = header.value;
        }
        else if (strcmp(header.name.c_str(),
            "client_key") == 0) {
          client_key = header.value;
        }
      }
      if (username.empty()) {
        std::string reply =
        dbaas::database::reply::missing_item_error(
          "username");
        rep.content.append(reply.c_str(), reply.size());
        return;
      }
      else if (client_key.empty()) {
        std::string reply =
        dbaas::database::reply::missing_item_error(
          "client_key");
        rep.content.append(reply.c_str(), reply.size());
        return;
      }

      // get reply from database
      std::string reply = dbaas::database::list_indexes(
      username,
      dbaas::database::password::check_key(client_key));

      // write reply
      rep.content.append(reply.c_str(), reply.size());
    }
    else {
      // if request isn't post method
      std::string reply =
      dbaas::database::reply::error("send post method");

      // write reply
      rep.content.append(reply.c_str(), reply.size());
    }
  }
  catch (std::exception &e) {

    // if execption happend in getting values or parsing json
    std::string reply = dbaas::database::reply::error(e.what());

    // write reply
    rep.content.append(reply.c_str(), reply.size());
  }
}
