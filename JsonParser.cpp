#include "JsonParser.hpp"

static void	_errorExit(std::string const& msg);
static void	_skipWhiteSpaces(std::string const& txt, std::string::iterator& it);

/* *************************************************************************** *
 * Constructor & Destructor                                                    *
 * ****************************************************************************/

JsonParser::JsonParser(void) {}

JsonParser::JsonParser(JsonParser const& target)
{
	if (this != &target)
	{
		*this = target;
	}
	else
	{
		// nothing to do
	}
}

JsonParser&	JsonParser::operator=(JsonParser const& target)
{
	if (this != &target)
	{
		this->_json = target._json;
	}
	else
	{
		// nothing to do
	}

	return *this;
}

JsonParser::~JsonParser(void) {}

/* *************************************************************************** *
 * Public Member Functions                                                     *
 * ****************************************************************************/

JsonData const&	JsonParser::getJson(void) const
{
	return this->_json;
}

JsonData&	JsonParser::parseJson(std::string const& filepath)
{
	std::string				text;
	std::string::iterator	start;

	readFile(filepath, text);
	start = text.begin();

	_skipWhiteSpaces(text, start);

	if (*start == '{')
	{
		this->_json = parseObject(text, start);
	}
	else if (*start == '[')
	{
		this->_json = parseArray(text, start);
	}
	else
	{
		_errorExit("Error: Invalid Json format");
	}

	start++;
	_skipWhiteSpaces(text, start);

	if (start != text.end())
	{
		_errorExit("Error: Failed to parse JSON file");
	}
	else
	{
		// parse Json successfully
	}

	return this->_json;
}

std::vector<JsonData>	JsonParser::findDataByKey
(JsonData const& jsonData, std::string const& key)
{
	std::vector<std::pair<std::string, JsonData> > const&
							jsonObject = jsonData._obj;
	std::vector<JsonData>	results;

	for (std::size_t i = 0; i < jsonObject.size(); ++i)
	{
		if (jsonObject[i].first == key)
		{
			results.push_back(jsonObject[i].second);
			continue;
		}

		if (jsonObject[i].second._type == TYPE_OBJECT
			&& !jsonObject[i].second._obj.empty())
		{
			std::vector<JsonData>	ret;

			ret = findDataByKey(jsonObject[i].second, key);
			results.insert(results.end(), ret.begin(), ret.end());
		}
		else if (jsonObject[i].second._type == TYPE_ARRAY
				&& !jsonObject[i].second._arr.empty())
		{
			for (std::size_t j = 0; j < jsonObject[i].second._arr.size(); ++j)
			{
				if (jsonObject[i].second._arr[j]._type == TYPE_OBJECT
					|| jsonObject[i].second._arr[j]._type == TYPE_ARRAY)
				{
					std::vector<JsonData>	ret;

					ret = findDataByKey(jsonObject[i].second._arr[j], key);
					results.insert(results.end(), ret.begin(), ret.end());
				}
			}
		}
	}

	return results;
}

/* *************************************************************************** *
 * Private Member Functions                                                    *
 * ****************************************************************************/

void	JsonParser::readFile
(std::string const& filepath, std::string& output)
{
	std::ifstream		file(filepath.c_str(), std::ios::in | std::ios::binary);
	std::ostringstream	ss;

	if (!file.is_open())
	{
		_errorExit("Error: Cannot open " + filepath);
	}
	else
	{
		// file OK
	}

	ss << file.rdbuf();

	if (file.fail())
	{
		file.close();
		_errorExit("Error: Failed to read a file");
	}
	else
	{
		file.close(); // read OK
	}

	output = ss.str();
}

JsonData	JsonParser::parseValue
(std::string const& text, std::string::iterator& it)
{
	JsonData	value;

	if (*it == '{')
	{
		value = parseObject(text, it);
	}
	else if (*it == '\"')
	{
		value = parseString(text, it);
	}
	else if (*it == '[')
	{
		value = parseArray(text, it);
	}
	else if (std::isalnum(*it) || *it == '.' || *it == '-' || *it == '+')
	{
		value = parsePrimitive(text, it);
	}
	else
	{
		_errorExit("Error: Invalid object value");
	}

	return value;
}

JsonData	JsonParser::parseArray
(std::string const& text, std::string::iterator& it)
{
	JsonData				jsonData;
	std::vector<JsonData>	jsonArray;

	if (it == text.end())
	{
		_errorExit("Error: EOF encountered before reading array");
	}
	else if (*it != '[')
	{
		_errorExit("Error: Array must start with an open square bracket");
	}
	else
	{
		it++;
	}

	_skipWhiteSpaces(text, it);

	if (it == text.end())
	{
		_errorExit("Error: EOF enconutered while reading array");
	}
	else if (*it == ']')
	{
		jsonData._type = TYPE_ARRAY;
		return jsonData;
	}
	else
	{
		// proceed (array has elements)
	}

	while (it != text.end() && *it != ']')
	{
		JsonData	element;

		element = parseValue(text, it);
		jsonArray.push_back(element);

		if (it == text.end())
		{
			_errorExit("Error: EOF encountered while reading array element");
		}
		else if (checkElementEnd(text, it) == false)
		{
			_errorExit("Error: Malformed array format");
		}
		else
		{
			it++;
		}

		_skipWhiteSpaces(text, it);

		if (*it == ',')
		{
			it++;
		}
		else
		{
			// nothing to do
		}

		_skipWhiteSpaces(text, it);
	}

	jsonData._type = TYPE_ARRAY;
	jsonData._arr = jsonArray;

	return jsonData;
}

JsonData	JsonParser::parseObject
(std::string const& text, std::string::iterator& it)
{
	JsonData										jsonData;
	std::vector<std::pair< std::string, JsonData> >	jsonObject;

	if (it == text.end())
	{
		_errorExit("Error: EOF encountered before reading object");
	}
	else if (*it != '{')
	{
		_errorExit("Error: Object must start with an open curly bracket");
	}
	else
	{
		it++;
	}

	_skipWhiteSpaces(text, it);

	if (it == text.end())
	{
		_errorExit("Error: EOF encountered while reading object");
	}
	else if (*it == '}')
	{
		jsonData._type = TYPE_OBJECT;
		return jsonData;
	}
	else
	{
		// proceed (object has key-value)
	}

	while (it != text.end() && *it != '}')
	{
		std::string	key;
		JsonData	value;

		if (it == text.end())
		{
			_errorExit("Error: EOF encountered before reading object key");
		}
		else if (*it == '\"')
		{
			key = parseStringKey(text, it);
			it++;
		}
		else
		{
			_errorExit("Error: Object key must starts with double quote");
		}

		_skipWhiteSpaces(text, it);

		if (it == text.end())
		{
			_errorExit("Error: EOF encountered while reading object key");
		}
		else if (*it != ':')
		{
			_errorExit("Error: Missing colon after key");
		}
		else
		{
			it++;
		}

		_skipWhiteSpaces(text, it);

		value = parseValue(text, it);
		jsonObject.push_back(std::make_pair(key, value));

		if (it == text.end())
		{
			_errorExit("Error: EOF encountered while reading object value");
		}
		else if (checkKeyValueEnd(text, it) == false)
		{
			// character is not included in end parts of object
			_errorExit("Error: Object key must starts with double quote");
		}
		else 
		{
			it++;
		}

		_skipWhiteSpaces(text, it);

		if (*it == ',')
		{
			it++;
		}
		else
		{
			// nothing to do
		}

		_skipWhiteSpaces(text, it);
	}

	jsonData._type = TYPE_OBJECT;
	jsonData._obj = jsonObject;

	return jsonData;
}

JsonData	JsonParser::parseString
(std::string const& text, std::string::iterator& it)
{
	JsonData	jsonData;

	jsonData._type = TYPE_STRING;
	jsonData._str = parseStringValue(text, it);

	return jsonData;
}

JsonData	JsonParser::parsePrimitive
(std::string const& text, std::string::iterator& it)
{
	JsonData	jsonData;

	jsonData._str = parsePrimitiveValue(text, it, jsonData._type);

	return jsonData;
}

bool	JsonParser::checkElementEnd
(std::string const& text, std::string::iterator& it)
{
	std::string::iterator	cur;
	bool					comma = false;

	cur = it + 1;
	while (cur != text.end() && (*cur == ',' || std::isspace(*cur)))
	{
		if (*cur == ',')
		{
			if (comma == false)
			{
				comma = true;
			}
			else
			{
				_errorExit("Error: Duplicate comma");
			}
		}
		else
		{
			// skipped
		}
		cur++;
	}

	if (cur == text.end())
	{
		_errorExit("Error: EOF encountered while checking array end");
	}
	else if (*cur == '\"')
	{
		if (comma == true)
		{
			return true;
		}
		else
		{
			_errorExit("Error: Missing comma before element");
		}
	}
	else if (*cur == '{')
	{
		if (comma == true)
		{
			return true;
		}
		else
		{
			_errorExit("Error: Missing comma before element");
		}
	}
	else if (*cur == '[')
	{
		if (comma == true)
		{
			return true;
		}
		else
		{
			_errorExit("Error: Missing comma before element");
		}
	}
	else if (std::isalnum(*cur) || *cur == '.' || *cur == '-' || *cur == '+')
	{
		if (comma == true)
		{
			return true;
		}
		else
		{
			_errorExit("Error: Missing comma before element");
		}
	}
	else if (*cur == ']')
	{
		if (comma == false)
		{
			return true;
		}
		else
		{
			_errorExit("Error: Found comma before end of array");
		}
	}
	else
	{
		// fallthrough to false
	}

	return false;
}

bool	JsonParser::checkKeyValueEnd
(std::string const& text, std::string::iterator& it)
{
	std::string::iterator	cur;
	bool					comma = false;

	cur = it + 1;
	while (cur != text.end() && (*cur == ',' || std::isspace(*cur)))
	{
		if (*cur == ',')
		{
			if (comma == false)
			{
				comma = true;
			}
			else
			{
				_errorExit("Error: Duplicate comma");
			}
		}
		else
		{
			// skipped
		}
		cur++;
	}

	if (cur == text.end())
	{
		_errorExit("Error: EOF encountered while checking object end part");
	}
	else if (*cur == '\"')
	{
		if (comma == true)
		{
			return true;
		}
		else
		{
			_errorExit("Error: Missing comma before key");
		}
	}
	else if (*cur == '}')
	{
		if (comma == false)
		{
			return true;
		}
		else
		{
			_errorExit("Error: Found comma before end of object");
		}
	}
	else
	{
		// fallthrough to false
	}

	return false;
}

std::string	JsonParser::parsePrimitiveValue
(std::string const& text, std::string::iterator& it, jsonType& type)
{
	std::string	value;

	while (it != text.end()
			&& (std::isalnum(*it) || *it == '.' || *it == '-' || *it == '+'))
	{
		value += *it;
		it++;
	}

	if (it == text.end())
	{
		_errorExit("Error: EOF encountered while reading primitive");
	}
	else
	{
		it--;
	}

	type = getPrimitiveType(value);

	if (type == TYPE_ERROR)
	{
		_errorExit("Error: Invalid primitive");
	}
	else
	{
		// primitive has valid type
	}

	return value;
}

std::string	JsonParser::parseStringKey
(std::string const& text, std::string::iterator& it)
{
	std::string	key;

	key = getStringData(text, it);

	return key;
}

std::string	JsonParser::parseStringValue
(std::string const& text, std::string::iterator& it)
{
	std::string value;

	value = getStringData(text, it);

	return value;
}

std::string	JsonParser::getStringData
(std::string const& text, std::string::iterator& it)
{
	std::string	str;
	bool		escape = false;
	char		ch;

	it++;
	while (it != text.end())
	{
		ch = *it;
		if (ch == '\n')
		{
			_errorExit("Error: Malformed String Data type");
		}
		if (escape)
		{
			str += ch;
			escape = false;
		}
		else if (ch == '\\')
		{
			str += ch;
			escape = true;
		}
		else if (ch == '\"')
		{
			break;
		}
		else
		{
			str += ch;
		}
		it++;
	}

	return str;
}

jsonType	JsonParser::getPrimitiveType(std::string const& str)
{
	char*	endptr;

	static_cast<void>(strtol(str.c_str(), &endptr, 10));
	if (*endptr == '\0')
	{
		return TYPE_INTEGER;
	}
	else
	{
		// fallthrough
	}

	static_cast<void>(strtod(str.c_str(), &endptr));
	if (*endptr == '\0')
	{
		return TYPE_FLOAT;
	}
	else
	{
		// fallthrough
	}

	if (str == "true" || str == "false")
	{
		return TYPE_BOOLEAN;
	}
	else
	{
		// fallthrough
	}

	if (str == "null")
	{
		return TYPE_NULL;
	}
	else
	{
		// fallthrough
	}

	return TYPE_ERROR;
}

/* *************************************************************************** *
 * Helper Functions                                                            *
 * ****************************************************************************/

static void	_errorExit(std::string const& msg)
{
	std::cerr << msg << std::endl;
	std::exit(1);
}

static void	_skipWhiteSpaces
(std::string const& text, std::string::iterator& it)
{
	while (it != text.end() && std::isspace(*it))
		it++;
}
