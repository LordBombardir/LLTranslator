#include "CommandManager.h"
#include "types/translator/TranslatorCommand.h"
#include "mod/Main.h"

#include <ll/api/command/CommandHandle.h>
#include <ll/api/command/CommandRegistrar.h>
#include <ll/api/service/Bedrock.h>

namespace translator {

bool CommandManager::registerCommands() {
    optional_ref<CommandRegistry> commandRegistry = ll::service::getCommandRegistry();
    if (!commandRegistry) {
        return false;
    }

#ifndef LL_PLAT_C
    bool isClientSide = false;
#else
    bool isClientSide = true;
#endif

    Main::getInstance().getSelf().getLogger().info("Registering Translator command... isClientSide = {}", isClientSide);

    // clang-format off
    ll::command::CommandHandle& translatorCommand = ll::command::CommandRegistrar::getInstance(isClientSide).getOrCreateCommand(
        commands::TranslatorCommand::getName(),
        commands::TranslatorCommand::getDescription(),
        commands::TranslatorCommand::getRequirement(),
        commands::TranslatorCommand::getFlag()
    );
    // clang-format on

    for (const std::string& alias : commands::TranslatorCommand::getAliases()) {
        translatorCommand.alias(alias);
    }

    translatorCommand.overload().execute(&commands::TranslatorCommand::execute);
    return true;
}

} // namespace translator