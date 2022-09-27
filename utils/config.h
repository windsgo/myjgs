#pragma once

#include "json.hpp"
#include <string>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>

// namespace utils
// {

    // manage a couple of `Config`s in one class
    // use key : string <--> config : Config
    // to organize config list
    class ConfigManager;

    // manage a single config file
    // a wrapper of meojson
    // offer API for reading config items
    class Config;

// }

class Config
{
    typedef std::shared_ptr<Config> ptr;
    friend class ConfigManager;

private:
    Config(const std::string &filename);
    Config(const Config &) = delete;
    Config(Config &&) = delete;

    enum class OPEN_STATE{
        SUCCEEDED       = 0,
        OPEN_FAILED     = -1,
        PARSE_FAILED    = -2
    };
    // open and parse file , then close file
    OPEN_STATE _open_and_parse_file();

    std::string _filename{};
    bool _is_valid{false};
    json::value _value;

public:
    inline bool isValid() { return _is_valid; }
    inline auto getRootValue() -> decltype(_value) {return _value;}
    inline json::value at(const std::string& key) {return _value.at(key);}
};

class ConfigManager
{
private:
    ConfigManager() {}
    ConfigManager(const ConfigManager &) = delete;
    ConfigManager(ConfigManager &&) = delete;

    std::unordered_map<std::string, Config::ptr> _map_key_config{};

public: // staic api for getting singleton ConfigManager
    static ConfigManager *getUniqueInstance();

public: // non-static api can be called after getting ConfigManager
    enum class ADD_RES {
        SUCCEEDED   = 0,
        FILE_ERR    = -1,
        INSERT_ERR  = -2
    };
    // if file cannot be opened or parsed return -1 
    // if exists the same key return -2
    // else return number of added config files
    int addConfigFile(const std::string &key, const std::string &filename);
    inline Config::ptr getConfig(const std::string &key) {
        return _map_key_config.at(key);
    }
    void deleteConfig(const std::string &key);
};
