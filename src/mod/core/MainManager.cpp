#include "MainManager.h"
#include "../commands/CommandManager.h"
#include "../hooks/Hooks.h"
#include "../language/LanguageManager.h"

namespace translator {

bool MainManager::initModWhileLoading(ll::mod::NativeMod& mod) {
    if (!ConfigManager::init(mod)) {
        mod.getLogger().error("Failed to init ConfigManager!");
        return false;
    }

    if (!LanguageManager::init(mod)) {
        mod.getLogger().error("Failed to init LanguageManager!");
        return false;
    }

    Hooks::setup();
    return true;
}

bool MainManager::initModWhileEnabling([[maybe_unused]] ll::mod::NativeMod& mod) {
#ifdef LL_PLAT_S
    if (!CommandManager::registerCommands(false)) {
        mod.getLogger().error("Failed to register commands!");
        return false;
    }
#endif

    return true;
}

void MainManager::disableMod() {}

} // namespace translator