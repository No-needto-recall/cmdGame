#include "config.h"

Config& Config::instance() {
    static Config instance;
    return instance;
}

const ConfigData& Config::getConfigData() const {
    return *_data;
}

// 移除UTF-8 BOM签名的函数
void remove_utf8_bom(std::string& str) {
    if (str.size() >= 3 && str[0] == '\xEF' && str[1] == '\xBB' && str[2] == '\xBF') {
        str.erase(0, 3);
    }
}

Config::Config() {
    std::ifstream file("../conf/conf.json",std::ios::in | std::ios::binary);
    if (file.is_open()) {

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

        // 移除UTF-8 BOM签名
        remove_utf8_bom(content);

        // 使用已移除BOM签名的字符串创建JSON对象
        nlohmann::json j = nlohmann::json::parse(content);


        _data = std::make_unique<ConfigData>();
        _data->from_json(j);
        file.close();
    }
    else {
        throw std::runtime_error("Failed to open config file");
    }
}
