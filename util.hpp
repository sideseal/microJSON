#ifndef __UTIL_H__
#define __UTIL_H__

#include "JsonParser.hpp"

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"
#define RESET "\033[0m"

#define COLOR CYAN

void	check_leaks(void);
void	printJsonArray(std::vector<JsonData> const& jsonArray, size_t depth);
void	printJsonObject(JsonData const& jsonData, size_t depth);
void	printJson(JsonData const& jsonData);

#endif	/* __UTIL_H__ */
