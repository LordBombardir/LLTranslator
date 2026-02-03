#pragma once

namespace translator {

class CommandManager final {
public:
    static bool registerCommands(bool isClientSide);
};

} // namespace translator