#pragma once

#include <ll/api/mod/NativeMod.h>

namespace translator {

namespace config {
struct Config;
}

class ConfigManager final {
public:
    static bool init(ll::mod::NativeMod& mod);

    static const config::Config& getConfig();

private:
    static config::Config config;
};

} // namespace translator