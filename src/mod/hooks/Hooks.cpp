#include "Hooks.h"
#include "../commands/CommandManager.h"

#include <ll/api/memory/Hook.h>
#include <mc/certificates/identity/ActiveDirectoryIdentity.h>
#include <mc/client/commands/ClientCommands.h>
#include <mc/client/game/MinecraftGame.h>
#include <mc/scripting/ServerScriptManager.h>

namespace translator {

#ifdef LL_PLAT_C
LL_TYPE_STATIC_HOOK(
    RegisterClientCommands,
    ll::memory::HookPriority::Normal,
    ClientCommands,
    &ClientCommands::setupStandard,
    void,
    MinecraftCommands&                 minecraftCommands,
    IMinecraftGame&                    minecraftGame,
    std::shared_ptr<mce::TextureGroup> textureGroup,
    FileArchiver&                      archiver,
    bool                               isHost,
    const ActiveDirectoryIdentity*     adIdentity,
    bool                               scriptingEnabled,
    const Level&                       level
) {
    if (!isHost) {
        origin(minecraftCommands, minecraftGame, textureGroup, archiver, isHost, adIdentity, scriptingEnabled, level);

        CommandManager::registerCommands(true);
        return;
    }

    origin(minecraftCommands, minecraftGame, textureGroup, archiver, isHost, adIdentity, scriptingEnabled, level);
}

LL_TYPE_STATIC_HOOK(
    RegisterClientCommandsTestHook,
    ll::memory::HookPriority::Normal,
    ClientCommands,
    &ClientCommands::setupStartMenuScreen,
    void,
    MinecraftCommands& minecraftCommands,
    IMinecraftGame&    minecraftClient
) {
    if (!minecraftClient.isHostingLocalDedicatedServer()) {
        origin(minecraftCommands, minecraftClient);

        CommandManager::registerCommands(true);
        return;
    }

    origin(minecraftCommands, minecraftClient);
}

LL_TYPE_INSTANCE_HOOK(
    RegisterClientHostCommands,
    ll::memory::HookPriority::Normal,
    ServerScriptManager,
    &ServerScriptManager::$onServerThreadStarted,
    EventResult,
    ServerInstance& ins
) {
    auto result = origin(ins);

    CommandManager::registerCommands(false);
    return result;
}
#endif

void Hooks::setup() {
#ifdef LL_PLAT_C
    // RegisterClientCommands::hook();
    RegisterClientCommandsTestHook::hook();

    RegisterClientHostCommands::hook();
#endif
}

} // namespace translator