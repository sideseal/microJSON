# microJSON

Simple C++98 JSON parser.

This parser offers a simple and intuitive way to work with JSON data.

## Key Implementation Details

Below code is a portion of JsonData class that stores the data types of JSON:

```c
class JsonData
{
public:
    jsonType                                       _type;
    std::string                                    _str;
    std::vector<JsonData>                          _arr;
    std::vector<std::pair<std::string, JsonData> > _obj;
    // ...
}
```

- **Type Filed:** I've made parsing straightforward by associating each value with a type field(`_type`). This approach simplifies value identification and handling.

- **String and Primitive Values:** String and primitive type values are uniformly stored in a string field(`_str`). This design choice reduces complexity in handling various data types.

- **Arrays and Objects:** Arrays and objects are managed using standard C++ vectors(`_arr`, `_obj`). This approach not only makes the code easy to understand but also eliminates the need for complex memory management.

## Advantages

1. **Easy-to-Understand Parsing Logic:** By associating each value with a type field, our parser promotes a more intuitive and comprehensible parsing logic about JSON, making it easier for users to work with JSON data.

2. **Simplified Memory Management:** This approach eliminates the need for intricate memory management, ensuring that developers can focus on their application logic without worrying about memory allocation and deallocation.

## Drawbacks

1. **Type Conversion for String Fields:** Since both string and primitive types are stored in the string field, users need to check the type field and then convert the string field to desired data type when working with primitive values. While this approach simplifies parsing, it requires additional type checks.

microJSON is easily understandable, but it does have some limitations. It's important to note that it may not cover all edge cases of JSON data. However, I believe it works well in most cases.

## How to Use

You can incorporate the JsonParser functions into your project to parse and work with JSON data. Here's how to use them:

```c
JsonData const&         getJson(void) const;
JsonData&               parseJson(std::string const& filepath);
std::vector<JsonData>   findDataByKey(JsonData const& jsonData, std::string const& key);
```

- **getJson:** This function returns the currently parsed JSON data, which is stored in a JsonData object(`_json`). You can insert this data into your application by calling `getJson()`.

- **parseJson:** To parse a JSON file and store the result in the `_json` member variable, use the `parseJson` function with the file path as an argument. It also returns the parsed JsonData object, which you can access for further processing.

- **findDataByKey:** If you need to retrieve specific JSON objects by a key string, the `findDataByKey` function takes a JsonData object and a key string as parameters and returns a vector of matching values.

With these functions, you can easily work with JSON data in your application. Simply insert the necessary code into your project to use them as needed. Make sure you need to use C++98-compatible compiler to build project with microJSON.

If you find that the `util.cpp` and `util.hpp` files are not needed for your application, you can safely exclude these files from your build process. `JsonParser` and `JsonData` are not depend on `util.cpp` and `util.hpp`.

## Testing

You can easily test this JSON parser to ensure it works as expected. Follow these steps to run tests:

1. **Clone the Repository:** Begin by cloning the repository to your local machine using the following command:

```shell
git clone <repository_url>
```

2. **Build the Project:** Use your C++98-compatible compiler to build the project. You can also utilize the provided Makefile for a convenient build process by running:

```shell
make
```

3. **Run the Tests:** To verify the functionality of the JSON parser, you can use the generated executable in the following format:

```shell
./test FILE [STRING]
```

- **FILE (Required):** Specify the JSON file that you want to parse.

- **STRING (Optional):** If you want to test the `findDataByKey` function, provide a key as a string. This key will be used to search for specific JSON objects in the parsed data.

By running these tests with the provided executable, you can verify that the JSON parser is working correctly and is suitable for your application. If you encounter any issues or have suggestions for improvements, please don't hesitate to provide feedback!

## Copyright

This code is released with no copyright restrictions. You are free to use it without any limitations.

## Special Thanks

Thank you [Hyeonjan](https://profile.intra.42.fr/users/hyeonjan) for guiding me towards a more refined code and for your continued interest. You're truly the best! :smile:
