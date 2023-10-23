#include "JsonParser.hpp"
#include "util.hpp"

int	main(int argc, char *argv[])
{
	JsonParser	jsonParser;

	if (argc != 2)
	{
		std::cerr << "Please test with a file" << std::endl;
		return 1;
	}
	else
	{
		jsonParser.parseJson(argv[1]);
		printJson(jsonParser.getJson());
	}

	return 0;
}
