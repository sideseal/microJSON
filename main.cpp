#include "JsonParser.hpp"
#include "util.hpp"

int	main(int argc, char *argv[])
{
	JsonParser	jsonParser;

	if (argc < 2 || argc > 3)
	{
		std::cerr << "Usage: ./test FILE [STRING]\n" << std::endl;
		std::cerr << "This program is used to test microJSON.\n" << std::endl;
		std::cerr << "Arguments:" << std::endl;
		std::cerr <<
			"    FILE    : The input file." 
		<< std::endl;
		std::cerr <<
			"    STRING  : (Optional) The Key to search a value in an object.\n"
		<< std::endl;
		std::cerr << "Notes:" << std::endl;
		std::cerr <<
			"- This program is designed for testing microJSON."
		<< std::endl;
		std::cerr
			<< "- You must provide one to two arguments, ";
		std::cerr
			<< "where FILE is required, and STRING is optional."
		<< std::endl;

		return 1;
	}
	else
	{
		std::cout << MAGENTA
			<< "\n* Parsed JSON result\n"
		<< RESET << std::endl;

		jsonParser.parseJson(argv[1]);
		printJson(jsonParser.getJson());
	}

	if (argc == 3)
	{
		std::cout << MAGENTA
			<< "\n* Print all values found by Key\n"
		<< RESET << std::endl;

		JsonData				json = jsonParser.getJson();
		std::vector<JsonData>	arr = jsonParser.findDataByKey(json, argv[2]);
		std::size_t				size = arr.size();

		if (size == 0)
		{
			std::cout << "No matching value found." << std::endl;
		}
		else
		{
			std::cout << "[ ";
			for (std::size_t i = 0; i < size; ++i)
			{
				std::cout << arr[i]._str;

				if (i < size - 1)
				{
					std::cout << ", ";
				}
				else
				{
					// skip comma character
				}
			}
			std::cout << " ]" << std::endl;
		}
	}
	else
	{
		// skipped
	}

	return 0;
}
