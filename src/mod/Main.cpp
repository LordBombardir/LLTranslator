#include "Main.h"
#include "core/MainManager.h"

#include <ll/api/mod/RegisterHelper.h>

namespace translator {

Main& Main::getInstance() {
    static Main instance;
    return instance;
}

bool Main::load() {
    getSelf().getLogger().info("The mod is loading...");

    if (!MainManager::initModWhileLoading(getSelf())) {
        getSelf().getLogger().error("Failed to initialize the mod during loading!");
        return false;
    }

    getSelf().getLogger().info("The mod has been successfully loaded!");
    return true;
}

bool Main::enable() {
    getSelf().getLogger().info("The mod is enabling...");

    if (!MainManager::initModWhileEnabling(getSelf())) {
        getSelf().getLogger().error("Failed to initialize the mod during enabling!");
        return false;
    }

    getSelf().getLogger().info("The mod has been successfully enabled!");

    getSelf().getLogger().info("Author: vk.com/lordbomba. Exclusively for uinqwe.ru");
    return true;
}

bool Main::disable() {
    getSelf().getLogger().info("The mod is disabling...");

    MainManager::disableMod();

    getSelf().getLogger().info("The mod has been successfully disabled.");
    return true;
}

} // namespace translator

LL_REGISTER_MOD(translator::Main, translator::Main::getInstance());
