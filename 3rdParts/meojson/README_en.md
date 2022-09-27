<div align="center">

# meojson

现代化的全平台 Json/Json5 解析/生成器，Header-only，并附带大量语法糖！

A modern all-platform Json/Json5 parser/serializer, which is header-only and contains lots of syntactic sugar!

</div>

[中文](./README.md)

## Usage

- Include the header file in your project, and enjoy it!

```cpp
#include "json.hpp"
```

- If you want to parse JSON5, please include `json5.hpp`

```cpp
#include "json5.hpp"
```

- meojson only depends on STL, but requires c++17 standard

## Sample

### Parsing

```cpp
/***
 * from sample/sample.cpp
***/
#include <iostream>
#include "json.hpp"

void parsing()
{
    std::string content = R"(
{
    "repo": "meojson",
    "author": {
        "MistEO": "https://github.com/MistEO",
        "ChingCdesu": "https://github.com/ChingCdesu"
    },
    "list": [
        1,
        2,
        3
    ],
    "str": "abc",
    "num": 3.1416,
    "A_obj": {
        "B_arr": [
            {
                "C_str": "you found me!"
            }
        ]
    }
}
    )";

    auto ret = json::parse(content);

    if (!ret) {
        std::cerr << "Parsing failed" << std::endl;
        return;
    }
    auto& value = ret.value(); // you can use rvalues if needed, like
                               // `auto value = std::move(ret).value();`
    // Output: meojson
    std::cout << value["repo"].as_string() << std::endl;

    /* Output:
        ChingCdesu's homepage: https://github.com/ChingCdesu
        MistEO's homepage: https://github.com/MistEO
    */
    for (auto&& [name, homepage] : value["author"].as_object()) {
        std::cout << name << "'s homepage: " << homepage.as_string() << std::endl;
    }

    // Output: abc
    std::string str = (std::string)value["str"];    // it is equivalent to `value["str"].as_string()`
    std::cout << str << std::endl;

    // Output: 3.141600
    double num = value["num"].as_double();          // similarly, you can use `(double)value["num"]`
    std::cout << num << std::endl;

    // Output: default_value
    std::string get = value.get("maybe_exists", "default_value");
    std::cout << get << std::endl;

    // Output: you found me!
    std::string nested_get = value.get("A_obj", "B_arr", 0, "C_str", "default_value");
    std::cout << nested_get << std::endl;

    // Output: 1, 2, 3
    // If the "list" is not an array or not exists, it will be a invalid optional;
    auto opt = value.find<json::array>("list");
    if (opt) {
        auto& arr = opt.value();
        for (auto&& elem : arr) {
            std::cout << elem.as_integer() << std::endl;
        }
    }
    // more examples, it will output 3.141600
    auto opt_n = value.find<double>("num");
    if (opt_n) {
        std::cout << opt_n.value() << std::endl;
    }
    // If you use the `find` without template argument, it will return a `std::optional<json::value>`
    auto opt_v = value.find("not_exists");
    std::cout << "Did we find the \"not_exists\"? " << opt_v.has_value() << std::endl;
}
```

### Parsing Json5

```cpp
/***
 * from sample/json5_parse.cpp
***/
#include <iostream>
#include "json5.hpp"

void parsing()
{
    std::string content = R"(
// It's a Json5 content
{
  名字: "MistEO",                  /* Key's quotes can be omitted */
  😊: '😄',                       // Emoji can be used as a key
  thanks: 'ありがとう',             /* Single quotes can also be used as strings */
  \u006Bey: ['value',],            // Normal characters and escapes can be mixed
  inf: +Infinity, nan: NaN,        // Numbers can start with '+'
  fractional: .3, integer: 42.,    // Allowed to start or end with decimal point
  byte_max: 0xff,                  // Supports hexadecimal number,
  light_speed: +3e8,               // and scientific notation
}
)";
    auto ret = json::parse5(content);
    if (!ret) {
        std::cerr << "Parsing failed" << std::endl;
        return;
    }
    auto& value = ret.value(); // you can use rvalues if needed, like
                               // `auto value = std::move(ret).value();`

    // Output: MistEO
    std::cout << value["名字"] << std::endl;
    // Output: value
    std::string str = (std::string)value["key"][0];
    std::cout << str << std::endl;
    
    // for more json::value usage, please refer to sample.cpp
}
```

### Serializing

```cpp
/***
 * from sample/sample.cpp
***/
#include <iostream>
#include "json.hpp"

void serializing()
{
    json::value root;
    root["hello"] = "meojson";
    root["Pi"] = 3.1416;

    root["arr"] = json::array{
        "a", "b", "c"
    };
    root["obj"] = json::object{
        {"obj_key1", "aaa"},
        {"obj_key2", 123},
        {"obj_key3", true}
    };
    root["obj"].object_emplace("key4", json::object{ { "key4 child", "lol" } });
    root["obj_another"]["child"]["grand"] = "i am grand";

    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    root["arr from vec"] = json::array(vec);
    root["arr from vec"].array_emplace(6);
    root["arr from vec"] += json::array{ 7, 8, 9, 10 };

    std::set<std::string> set = { "a", "bbb", "cc" };
    root["arr from set"] = json::array(set);

    std::map<std::string, int> map;
    map.emplace("key1", 1);
    map.emplace("key2", 2);
    root["obj from map"] = json::object(map);

    auto other = json::object{
        { "other_key", "lol" },
        { "obj", "Existing key will not be overwritten"}
    };
    // take union
    root |= other;

    std::cout << root.format(true) << std::endl;
}
```
