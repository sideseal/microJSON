#include "JsonData.hpp"

/* *************************************************************************** *
 * Constructor & Destructor                                                    *
 * ****************************************************************************/

JsonData::JsonData(void) : _type(TYPE_NULL) {}

JsonData::JsonData(JsonData const& target)
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

JsonData&	JsonData::operator=(JsonData const& target)
{
	if (this != &target)
	{
		this->_type = target._type;
		this->_str = target._str;
		this->_arr = target._arr;
		this->_obj = target._obj;
	}
	else
	{
		// nothing to do
	}

	return *this;
}

JsonData::~JsonData(void) {}

/* *************************************************************************** *
 * Public Member Functions                                                     *
 * ****************************************************************************/
