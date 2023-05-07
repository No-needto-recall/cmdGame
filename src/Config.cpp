#include "config.h"

Config& Config::instance() {
    static Config instance;
    return instance;
}

const ConfigData& Config::getConfigData() const {
    return *_data;
}

Config::Config() {
    std::ifstream file("../conf/conf.json");
    if (file.is_open()) {
        nlohmann::json j;
        file >> j;
        _data = std::make_unique<ConfigData>();
        _data->from_json(j);
        file.close();
    }
    else {
        throw std::runtime_error("Failed to open config file");
    }
}
