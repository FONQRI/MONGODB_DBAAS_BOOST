// header
#include "aggregate.h"

// internal
#include "src/database/collectionmethods.h"
#include "src/database/password.h"
#include "src/database/reply.h"

// boost
#include <boost/optional.hpp>

// std
#include <iostream>
#include <vector>

typedef boost::optional<bool> optional_bool;
typedef boost::optional<bsoncxx::types::b_document> optional_ducument;
typedef boost::optional<std::string> optional_string;
typedef boost::optional<int> optional_int;
typedef boost::optional<size_t> optional_size;

void dbaas::core::aggregate(http::server::reply &rep,
				http::server::request request)
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

			// convert content to json
			bsoncxx::document::value request_document =
			bsoncxx::from_json(request.content);

			// get options document of request
			optional_ducument options;

			try {
				options = request_document.view()["options"]
					  .get_document();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					// element is optional
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"options");
					rep.content.append(reply.c_str(),
							   reply.size());
					return;
				}
			}

			// get allow_disk_use from options document
			optional_bool allow_disk_use;

			// get use_cursor from options document
			optional_bool use_cursor;

			// get bypass_document_validation from options
			// document
			optional_bool bypass_document_validation;

			// get max_time from options document
			optional_size max_time;

			// get batch_size from options document
			optional_int batch_size;

			// get collation options of request
			optional_ducument collation;

			// get acknowledge_level from  write_concern document
			optional_string acknowledge_level;

			// get tag from  write_concern document
			optional_string tag;

			// get journal from  write_concern document
			optional_bool journal;

			// get majority from  write_concern document
			optional_int majority;

			// get timeout from  write_concern document
			optional_int timeout;

			// get nodes from  write_concern document
			optional_int nodes;

			// get hint document of options document
			optional_ducument hint;

			// get hint_str string of  options document
			optional_string hint_str;

			// pipeline ***********************************

			// get limit from request pipeline
			optional_int limit;

			// get sample from request pipeline
			optional_int sample;

			// get skip from request pipeline
			optional_int skip;

			// get out document of pipeline
			optional_string out;

			// get count document of pipeline
			optional_string count;

			// get add_fields document of pipeline
			optional_ducument add_fields;

			// get bucket document of pipeline
			optional_ducument bucket;

			// get bucket_auto document of pipeline
			optional_ducument bucket_auto;

			// get coll_stats document of pipeline
			optional_ducument coll_stats;

			// get facet document of pipeline
			optional_ducument facet;

			// get geo_near document of pipeline
			optional_ducument geo_near;

			// get graph_lookup document of pipeline
			optional_ducument graph_lookup;

			// get group document of pipeline
			optional_ducument group;

			// get index_stats document of pipeline
			optional_bool index_stats;

			// get lookup document of pipeline
			optional_ducument lookup;

			// get match document of pipeline
			optional_ducument match;

			// get project document of pipeline
			optional_ducument project;

			// get redact document of pipeline
			optional_ducument redact;

			// get replace_root document of pipeline
			optional_ducument replace_root;

			// get sort document of pipeline
			optional_ducument sort;

			// get sort_by_count document of pipeline
			optional_ducument sort_by_count;

			// get sort_by_count_str string of pipeline
			optional_string sort_by_count_str;

			// get unwind document of pipeline
			optional_ducument unwind;

			// get unwind_str string of pipeline
			optional_string unwind_str;

			if (options.is_initialized()) {

				// get allow_disk_use from options document
				try {
					allow_disk_use =
					options.get()
						.view()["allow_disk_use"]
						.get_bool();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"allow_disk_use");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get use_cursor from options document
				try {
					use_cursor = options.get()
							 .view()["use_cursor"]
							 .get_bool();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"use_cursor");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get bypass_document_validation from options
				// document
				try {
					bypass_document_validation =
					options.get()
						.view()
						["bypass_document_validation"]
						.get_bool();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"bypass_document_"
							"validation");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get max_time from options document
				try {
					std::int32_t max_time_temp =
					options.get()
						.view()["max_time"]
						.get_int32();

					if (max_time_temp >= 0) {
						max_time = max_time_temp;
					}
					else {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"max_time is unsigned");
						rep.content.append(reply.c_str(),
								   reply.size());
					}
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("max_time");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get batch_size from options document
				try {
					batch_size = options.get()
							 .view()["batch_size"]
							 .get_int32();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"batch_size");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get collation options of request
				try {
					collation = options.get()
							.view()["collation"]
							.get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"collation");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get write_concern document of request
				optional_ducument write_concern;

				try {
					write_concern = options.get()
							.view()["write_concern"]
							.get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"write_concern");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}
				if (write_concern.is_initialized()) {

					// get acknowledge_level from
					// write_concern document
					try {
						acknowledge_level =
						write_concern.get()
							.view()["acknowledge_level"]
							.get_utf8()
							.value.to_string();
					}
					catch (std::exception &e) {

						// if element doesn't exist in
						// request document
						if (strcmp(e.what(),
							   "unset "
							   "document::"
							   "element") == 0) {
							// element is optional
						} // check if element type is
						  // wrong
						else if (
							strcmp(e.what(),
							   "expected element "
							   "type k_document") ==
							0) {
							std::string reply =
							dbaas::database::reply::
								wrong_item_type(
								"acknowledge_"
								"level");
							rep.content.append(
							reply.c_str(),
							reply.size());
							return;
						}
					}

					// get tag from  write_concern document
					try {
						tag = write_concern.get()
							  .view()["tag"]
							  .get_utf8()
							  .value.to_string();
					}
					catch (std::exception &e) {

						// if element doesn't exist in
						// request document
						if (strcmp(e.what(),
							   "unset "
							   "document::"
							   "element") == 0) {
							// element is optional
						} // check if element type is
						  // wrong
						else if (
							strcmp(e.what(),
							   "expected element "
							   "type k_document") ==
							0) {
							std::string reply =
							dbaas::database::reply::
								wrong_item_type(
								"tag");
							rep.content.append(
							reply.c_str(),
							reply.size());
							return;
						}
					}

					// get journal from  write_concern
					// document
					try {
						journal = write_concern.get()
							  .view()["journal"]
							  .get_bool();
					}
					catch (std::exception &e) {

						// if element doesn't exist in
						// request document
						if (strcmp(e.what(),
							   "unset "
							   "document::"
							   "element") == 0) {
							// element is optional
						} // check if element type is
						  // wrong
						else if (
							strcmp(e.what(),
							   "expected element "
							   "type k_document") ==
							0) {
							std::string reply =
							dbaas::database::reply::
								wrong_item_type(
								"journal");
							rep.content.append(
							reply.c_str(),
							reply.size());
							return;
						}
					}

					// get majority from  write_concern
					// document
					try {
						majority = write_concern.get()
							   .view()["majority"]
							   .get_int32();
					}
					catch (std::exception &e) {

						// if element doesn't exist in
						// request document
						if (strcmp(e.what(),
							   "unset "
							   "document::"
							   "element") == 0) {
							// element is optional
						} // check if element type is
						  // wrong
						else if (
							strcmp(e.what(),
							   "expected element "
							   "type k_document") ==
							0) {
							std::string reply =
							dbaas::database::reply::
								wrong_item_type(
								"majority");
							rep.content.append(
							reply.c_str(),
							reply.size());
							return;
						}
					}

					// get timeout from  write_concern
					// document
					try {
						timeout = write_concern.get()
							  .view()["timeout"]
							  .get_int32();
					}
					catch (std::exception &e) {

						// if element doesn't exist in
						// request document
						if (strcmp(e.what(),
							   "unset "
							   "document::"
							   "element") == 0) {
							// element is optional
						} // check if element type is
						  // wrong
						else if (
							strcmp(e.what(),
							   "expected element "
							   "type k_document") ==
							0) {
							std::string reply =
							dbaas::database::reply::
								wrong_item_type(
								"timeout");
							rep.content.append(
							reply.c_str(),
							reply.size());
							return;
						}
					}

					// get nodes from  write_concern
					// document
					try {
						nodes = write_concern.get()
							.view()["nodes"]
							.get_int32();
					}
					catch (std::exception &e) {

						// if element doesn't exist in
						// request document
						if (strcmp(e.what(),
							   "unset "
							   "document::"
							   "element") == 0) {
							// element is optional
						} // check if element type is
						  // wrong
						else if (
							strcmp(e.what(),
							   "expected element "
							   "type k_document") ==
							0) {
							std::string reply =
							dbaas::database::reply::
								wrong_item_type(
								"nodes");
							rep.content.append(
							reply.c_str(),
							reply.size());
							return;
						}
					}
				}

				// get hint document of options document
				try {
					hint = options.get()
						   .view()["hint"]
						   .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("hint");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get hint_str document of request

				try {
					hint_str = options.get()
						   .view()["hint_str"]
						   .get_utf8()
						   .value.to_string();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("hint_str");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}
			}

			// get pipeline document of request
			optional_ducument pipeline;

			try {
				pipeline = request_document.view()["pipeline"]
					   .get_document();
			}
			catch (std::exception &e) {

				// if element doesn't exist in request document
				if (strcmp(e.what(),
					   "unset document::element") == 0) {
					// element is optional
				} // check if element type is wrong
				else if (strcmp(e.what(),
						"expected element "
						"type k_document") == 0) {
					std::string reply =
					dbaas::database::reply::wrong_item_type(
						"pipeline");
					rep.content.append(reply.c_str(),
							   reply.size());
					return;
				}
			}

			if (pipeline.is_initialized()) {

				// get limit from request pipeline
				try {
					limit = pipeline.get()
						.view()["limit"]
						.get_int32();
				}
				catch (std::exception &e) {

					// if element doesn't exist in
					// request document
					if (strcmp(e.what(), "unset "
								 "document::"
								 "element") == 0) {
						// element is optional
					} // check if element type is
					  // wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("limit");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get sample from request pipeline
				try {
					sample = pipeline.get()
						 .view()["sample"]
						 .get_int32();
				}
				catch (std::exception &e) {

					// if element doesn't exist in
					// request document
					if (strcmp(e.what(), "unset "
								 "document::"
								 "element") == 0) {
						// element is optional
					} // check if element type is
					  // wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("sample");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get skip from request pipeline
				try {
					skip = pipeline.get()
						   .view()["skip"]
						   .get_int32();
				}
				catch (std::exception &e) {

					// if element doesn't exist in
					// request document
					if (strcmp(e.what(), "unset "
								 "document::"
								 "element") == 0) {
						// element is optional
					} // check if element type is
					  // wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("skip");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get out document of pipeline
				try {
					out = pipeline.get()
						  .view()["out"]
						  .get_utf8()
						  .value.to_string();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("out");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get count document of pipeline
				try {
					count = pipeline.get()
						.view()["count"]
						.get_utf8()
						.value.to_string();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("count");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get add_fields document of pipeline
				try {
					add_fields = pipeline.get()
							 .view()["add_fields"]
							 .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"add_fields");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get bucket document of pipeline
				try {
					bucket = pipeline.get()
						 .view()["bucket"]
						 .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("bucket");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get bucket_auto document of pipeline
				try {
					bucket_auto = pipeline.get()
							  .view()["bucket_auto"]
							  .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"bucket_auto");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get coll_stats document of pipeline
				try {
					coll_stats = pipeline.get()
							 .view()["coll_stats"]
							 .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"coll_stats");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get facet document of pipeline
				try {
					facet = pipeline.get()
						.view()["facet"]
						.get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("facet");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get geo_near document of pipeline
				try {
					geo_near = pipeline.get()
						   .view()["geo_near"]
						   .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("geo_near");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get graph_lookup document of pipeline
				try {
					graph_lookup = pipeline.get()
							   .view()["graph_lookup"]
							   .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"graph_lookup");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get group document of pipeline
				try {
					group = pipeline.get()
						.view()["group"]
						.get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("group");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get index_stats document of pipeline
				try {
					index_stats = pipeline.get()
							  .view()["index_stats"]
							  .get_bool();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"index_stats");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get lookup document of pipeline
				try {
					lookup = pipeline.get()
						 .view()["lookup"]
						 .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("lookup");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get match document of pipeline
				try {
					match = pipeline.get()
						.view()["match"]
						.get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("match");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get project document of pipeline
				try {
					project = pipeline.get()
						  .view()["project"]
						  .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("project");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get redact document of pipeline
				try {
					redact = pipeline.get()
						 .view()["redact"]
						 .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("redact");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get replace_root document of pipeline
				try {
					replace_root = pipeline.get()
							   .view()["replace_root"]
							   .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"replace_root");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get sort document of pipeline
				try {
					sort = pipeline.get()
						   .view()["sort"]
						   .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("sort");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get sort_by_count document of pipeline
				try {
					sort_by_count = pipeline.get()
							.view()["sort_by_count"]
							.get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"sort_by_count");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get sort_by_count_str string of pipeline
				try {
					sort_by_count_str =
					pipeline.get()
						.view()["sort_by_count_str"]
						.get_utf8()
						.value.to_string();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"sort_by_count_str");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get unwind document of pipeline
				try {
					unwind = pipeline.get()
						 .view()["unwind"]
						 .get_document();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type("unwind");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}

				// get unwind_str string of pipeline
				try {
					unwind_str = pipeline.get()
							 .view()["unwind_str"]
							 .get_utf8()
							 .value.to_string();
				}
				catch (std::exception &e) {

					// if element doesn't exist in request
					// document
					if (strcmp(e.what(),
						   "unset document::element") ==
						0) {
						// element is optional
					} // check if element type is wrong
					else if (strcmp(e.what(),
							"expected element "
							"type k_document") ==
						 0) {
						std::string reply =
						dbaas::database::reply::
							wrong_item_type(
							"unwind_str");
						rep.content.append(reply.c_str(),
								   reply.size());
						return;
					}
				}
			}

			// get reply from database
			auto reply = dbaas::database::aggregate(
			username,
			dbaas::database::password::check_key(client_key),
			allow_disk_use, use_cursor, bypass_document_validation,
			max_time, batch_size, collation, acknowledge_level, tag,
			journal, majority, timeout, nodes, hint, hint_str,
			limit, sample, skip, out, count, add_fields, bucket,
			bucket_auto, coll_stats, facet, geo_near, graph_lookup,
			group, index_stats, lookup, match, project, redact,
			replace_root, sort, sort_by_count, sort_by_count_str,
			unwind, unwind_str);

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
