#pragma once

#include "mod/language/LanguageManager.h"

#include <mc/server/commands/Command.h>
#include <mc/server/commands/CommandFlag.h>
#include <mc/server/commands/CommandOrigin.h>
#include <mc/server/commands/CommandOutput.h>
#include <mc/server/commands/CommandPermissionLevel.h>

namespace translator::commands {

class TranslatorCommand final {
public:
    static std::string getName() { return "translator"; };
    static std::string getDescription() { return LanguageManager::getTranslate("commandTranslatorDescription"); };
    static CommandPermissionLevel getRequirement() { return CommandPermissionLevel::Any; };
    static CommandFlag            getFlag() { return CommandFlagValue::NotCheat; };

    static std::vector<std::string> getAliases() { return {"tr"}; };

    static void execute(const CommandOrigin& origin, CommandOutput& output);
};

} // namespace translator::commands