#include "MainManager.h"
#include "../language/LanguageManager.h"
#include "../commands/CommandManager.h"

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

    // todo: add hooks::setupHooks
	return true;
}

bool MainManager::initModWhileEnabling(ll::mod::NativeMod& mod) {
    if (!CommandManager::registerCommands()) {
        mod.getLogger().error("Failed to register commands!");
        return false;
    }

    return true;
}

void MainManager::disableMod() {}

} // namespace translator