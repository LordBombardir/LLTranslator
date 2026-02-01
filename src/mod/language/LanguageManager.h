#pragma once

#include "../config/ConfigManager.h"
#include "../config/types/Config.h"

#include <ll/api/i18n/I18n.h>
#include <ll/api/mod/NativeMod.h>
#include <memory>
#include <string>

namespace translator {

class LanguageManager final {
public:
    static bool init(ll::mod::NativeMod& mod);

    static std::string
    getTranslate(std::string_view key, std::string_view localeCode = ConfigManager::getConfig().defaultLocaleCode);

private:
    static std::unique_ptr<ll::i18n::I18n> i18n;

    static void addTranslations(ll::mod::NativeMod& mod);
};

} // namespace translator