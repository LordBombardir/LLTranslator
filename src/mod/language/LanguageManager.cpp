#include "LanguageManager.h"
#include "../commands/types/translator/TranslatorCommand.h"

#include <filesystem>
#include <placeholder_api/Api.h>

namespace translator {

bool LanguageManager::init(ll::mod::NativeMod& mod) {
    i18n = std::make_unique<ll::i18n::I18n>();

    auto expected = i18n->load(mod.getDataDir() / "languages");
    if (!expected) {
        mod.getLogger().error("Failed to load translations: {}", expected.error().message());
        return false;
    }

    addTranslations(mod);
    return true;
}

std::string LanguageManager::getTranslate(std::string_view key, std::string_view localeCode) {
    return static_cast<std::string>(i18n->get(key, localeCode));
}

void LanguageManager::addTranslations(ll::mod::NativeMod& mod) {
    const auto& path = mod.getDataDir() / "languages";

    for (const auto& entry : std::filesystem::directory_iterator(path)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        const std::filesystem::path& file = entry.path();
        if (file.extension() != ".json") {
            continue;
        }

        const std::string localeCode = file.stem().string();
        if (localeCode == ConfigManager::getConfig().defaultLocaleCode) {
            continue;
        }

        placeholder::api::setPlaceholder(
            commands::TranslatorCommand::getName(),
            getTranslate("commandTranslatorDescription", localeCode),
            localeCode
        );
    }
}

} // namespace translator