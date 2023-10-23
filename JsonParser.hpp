#ifndef __JSONPARSER_HPP__
#define __JSONPARSER_HPP__

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

#include "JsonData.hpp"

class JsonParser
{
	private:
		JsonData	_json;

	public:
		JsonParser(void);
		JsonParser(JsonParser const& target);
		JsonParser&				operator=(
									JsonParser const& target
								);
		~JsonParser(void);

	public:
		JsonData const&			getJson(void) const;
		JsonData&				parseJson(
									std::string const& filepath
								);
		std::vector<JsonData>	findDataByKey(
									JsonData const& jsonData,
									std::string const& key
								);
	private:
		void					readFile(
									std::string const& filepath,
									std::string& output
								);
		JsonData				parseValue(
									std::string const& text,
									std::string::iterator& it
								);
		JsonData				parseArray(
									std::string const& text,
									std::string::iterator& it
								);
		JsonData				parseObject(
									std::string const& text,
									std::string::iterator& it
								);
		JsonData				parseString(
									std::string const& text,
									std::string::iterator& it
								);
		JsonData				parsePrimitive(
									std::string const& text,
									std::string::iterator& it
								);
		bool					checkElementEnd(
									std::string const& text,
									std::string::iterator& it
								);
		bool					checkKeyValueEnd(
									std::string const& text,
									std::string::iterator& it
								);
		std::string				parsePrimitiveValue(
									std::string const& text,
									std::string::iterator& it,
									jsonType& type
								);
		std::string				parseStringKey(
									std::string const& text,
									std::string::iterator& it
								);
		std::string				parseStringValue(
									std::string const& text,
									std::string::iterator& it
								);
		std::string				getStringData(
									std::string const& text,
									std::string::iterator& it
								);
		jsonType				getPrimitiveType(
									std::string const& str
								);
};

#endif	/* __JSONPARSER_HPP__ */
