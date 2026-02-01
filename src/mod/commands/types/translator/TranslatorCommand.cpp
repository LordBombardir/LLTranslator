#include "TranslatorCommand.h"

#include <mc/server/ServerPlayer.h>

namespace translator::commands {

void TranslatorCommand::execute(const CommandOrigin& origin, CommandOutput& output) {
    if (origin.getEntity() == nullptr || !origin.getEntity()->isType(ActorType::Player)) {
        output.error(LanguageManager::getTranslate("commandExecutionOnlyForPlayer"));
        return;
    }

    output.success("Test command execution. Your name is {}", origin.getEntity()->getNameTag());
}

} // namespace translator::commands