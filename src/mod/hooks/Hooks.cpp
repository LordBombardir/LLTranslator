#include "Hooks.h"
#include "../Main.h"
#include "../commands/CommandManager.h"

#include <ll/api/memory/Hook.h>
#include <mc/certificates/identity/ActiveDirectoryIdentity.h>
#include <mc/client/commands/ClientCommands.h>
#include <mc/client/game/MinecraftGame.h>
#include <mc/client/network/ClientNetworkHandler.h>
#include <mc/client/network/LegacyClientNetworkHandler.h>
#include <mc/platform/threading/Mutex.h>
#include <mc/scripting/ServerScriptManager.h>
#include <mc/world/actor/player/Player.h>
#include <mc/world/level/Level.h>

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

LL_TYPE_INSTANCE_HOOK(
    EnableModFirstTest,
    ll::memory::HookPriority::Normal,
    ClientNetworkHandler,
    &ClientNetworkHandler::$onSuccessfulLogin,
    void,
    const NetworkIdentifier& id
) {
    Main::getInstance().getSelf().getLogger().info("Client logged in, NetworkIdentifier: {}", id.toString());
    origin(id);
}

LL_TYPE_INSTANCE_HOOK(
    EnableModSecondTest,
    ll::memory::HookPriority::Normal,
    LegacyClientNetworkHandler,
    &LegacyClientNetworkHandler::onPlayerReady,
    void,
    Player& player
) {
    Main::getInstance().getSelf().getLogger().info(
        "Client player ready, Player name: {}",
        player.getRealName()
    );
    origin(player);
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
    RegisterClientCommands::hook();

    EnableModFirstTest::hook();
    EnableModSecondTest::hook();

    RegisterClientHostCommands::hook();
#endif
}

} // namespace translator