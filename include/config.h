#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include "config_data.h"

class Config {
public:
    static Config& instance();

    const ConfigData& getConfigData() const;

private:
    Config();

    Config(const Config&) = delete;
    Config& operator=(const Config&) = delete;

    std::unique_ptr<ConfigData> _data;
};


#define CONFIG_DATA Config::instance().getConfigData()

