#include "util.hpp"

std::string	convertType(jsonType type)
{
	switch (type)
	{
		case TYPE_INTEGER:
			return "TYPE_INTEGER";
		case TYPE_FLOAT:
			return "TYPE_FLOAT";
		case TYPE_STRING:
			return "TYPE_STRING";
		case TYPE_BOOLEAN:
			return "TYPE_BOOLEAN";
		case TYPE_ARRAY:
			return "TYPE_ARRAY";
		case TYPE_OBJECT:
			return "TYPE_OBJECT";
		case TYPE_NULL:
			return "TYPE_NULL";
		default:
			return "TYPE_ERROR";
	}
}

void	printJsonArray(std::vector<JsonData> const& jsonArray, size_t depth)
{
	for (size_t i = 0; i < jsonArray.size(); ++i)
	{
		for (size_t j = 0; j < depth + 1; ++j)
			std::cout << "    ";

		if (!jsonArray[i]._obj.empty())
		{
			std::cout << "{" << std::endl;
			printJsonObject(jsonArray[i], depth + 1);
			for (size_t j = 0; j < depth + 1; ++j)
				std::cout << "    ";
			std::cout << "}"
				<< COLOR
				<< " (" << convertType(jsonArray[i]._type) << ")"
				<< RESET;
		}
		else if (!jsonArray[i]._arr.empty())
		{
			std::cout << "[" << std::endl;
			printJsonArray(jsonArray[i]._arr, depth + 1);
			std::cout << "]"
				<< COLOR
				<< " (" << convertType(jsonArray[i]._type) << ")"
				<< RESET;
		}
		else
		{
			std::cout << jsonArray[i]._str
				<< COLOR
				<< " (" << convertType(jsonArray[i]._type) << ")"
				<< RESET;
		}

		if (i < jsonArray.size() - 1)
		{
			std::cout << ",";
		}
		else
		{
			// skipped
		}

		std::cout << std::endl;
	}

	for (size_t i = 0; i < depth; ++i)
		std::cout << "    ";
}

void	printJsonObject(JsonData const& jsonData, size_t depth)
{
	std::vector< std::pair<std::string, JsonData> > const& jsonObject
		= jsonData._obj;

	for (size_t i = 0; i < jsonObject.size(); ++i)
	{
		for (size_t j = 0; j < depth; ++j)
			std::cout << "    ";

		std::cout << jsonObject[i].first << ": ";

		if (!jsonObject[i].second._obj.empty())
		{
			std::cout << "{" << std::endl;
			printJsonObject(jsonObject[i].second, depth + 1);
			for (size_t j = 0; j < depth; ++j)
				std::cout << "    ";
			std::cout << "}"
				<< COLOR
				<< " (" << convertType(jsonObject[i].second._type) << ")"
				<< RESET;
		}
		else if (!jsonObject[i].second._arr.empty())
		{
			std::cout << "[" << std::endl;
			printJsonArray(jsonObject[i].second._arr, depth);
			std::cout << "]"
				<< COLOR
				" (" << convertType(jsonObject[i].second._type) << ")"
				<< RESET;
		}
		else
		{
			std::cout << jsonObject[i].second._str
				<< COLOR
				<< " (" << convertType(jsonObject[i].second._type) << ")"
				<< RESET;
		}

		std::cout << std::endl;
	}
}

void	printJson(JsonData const& jsonData)
{
	if (jsonData._obj.empty() && jsonData._arr.empty())
	{
		std::cout << "JSON is empty!" << std::endl;
		return ;
	}
	if (jsonData._type == TYPE_OBJECT)
	{
		std::cout << "{" << std::endl;
		printJsonObject(jsonData, 1);
		std::cout << "}" << std::endl;
	}
	else if (jsonData._type == TYPE_ARRAY)
	{
		std::cout << "[" << std::endl;
		printJsonArray(jsonData._arr, 0);
		std::cout << "]" << std::endl;
	}
	else
	{
		// unreachable
	}
}
