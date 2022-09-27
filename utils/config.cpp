#include "config.h"

Config::Config(const std::string& filename) : _filename(filename) {
    auto ret = _open_and_parse_file();
    if (ret == OPEN_STATE::SUCCEEDED) {
        _is_valid = true;
    } else {
        std::cout << "Open File Failed Err Code: " << (int)ret << std::endl;
        _is_valid = false;
    }
}

Config::OPEN_STATE Config::_open_and_parse_file() {
    // open file
    std::ifstream file;
    file.open(_filename, std::ios::in);
    if (!file.is_open()) {
        return OPEN_STATE::OPEN_FAILED;
    }

    // parse file
    std::stringstream content_sstream;
    content_sstream << file.rdbuf();
    std::string content_str(std::move(content_sstream.str()));

    auto parse_ret = json::parse(content_str);
    if (!parse_ret) {
        return OPEN_STATE::PARSE_FAILED;
    }
    _value = std::move(parse_ret).value();

    // close file
    file.close();
    return OPEN_STATE::SUCCEEDED;
}

ConfigManager *ConfigManager::getUniqueInstance()
{
    static ConfigManager instance;
    return &instance;
}

int ConfigManager::addConfigFile(const std::string &key, const std::string &filename)
{
    Config::ptr config(new Config(filename));
    if (config->isValid()) {
        if (!_map_key_config.insert(std::make_pair(key, config)).second) {
            // insert failed, means there exists the same key
            return (int)ADD_RES::INSERT_ERR;
        }
        return _map_key_config.size();
    } else {
        return (int)ADD_RES::FILE_ERR;
    }
}

void ConfigManager::deleteConfig(const std::string &key)
{
    auto it = _map_key_config.find(key);
    if (it != _map_key_config.end()) {
        _map_key_config.erase(key);
    }
}