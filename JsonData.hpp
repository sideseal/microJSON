#ifndef __JSONDATA_HPP__
#define __JSONDATA_HPP__

#include <string>
#include <map>
#include <vector>

enum jsonType
{
	TYPE_INTEGER,
	TYPE_FLOAT,
	TYPE_STRING,
	TYPE_BOOLEAN,
	TYPE_ARRAY,
	TYPE_OBJECT,
	TYPE_NULL,
	TYPE_ERROR
};

class JsonData
{
	public:
		jsonType										_type;
		std::string										_str;
		std::vector<JsonData>							_arr;
		std::vector<std::pair<std::string, JsonData> >	_obj;

	public:
		JsonData(void);
		JsonData(JsonData const& target);
		JsonData&	operator=(JsonData const& target);
		~JsonData(void);
};

#endif	/* __JSONDATA_HPP__ */
