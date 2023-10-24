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

- **Arrays and Objects:** Arrays and objects are managed using standard C++ vectors. This approach not only makes the code easy to understand but also eliminates the need for complex memory management.

## Advantages

1. **Easy-to-Understand Parsing Logic:** By associating each value with a type field, our parser promotes a more intuitive and comprehensible parsing logic about JSON, making it easier for users to work with JSON data.

2. **Simplified Memory Management:** This approach eliminates the need for intricate memory management, ensuring that developers can focus on their application logic without worrying about memory allocation and deallocation.

## Drawbacks

1. **Type Conversion for String Fields:** Since both string and primitive types are stored in the string field, users need to check the type field and then convert the string field to desired data type when working with primitive values. While this approach simplifies parsing, it requires additional type checks.


