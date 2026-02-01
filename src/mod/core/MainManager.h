#pragma once

#include <ll/api/mod/NativeMod.h>

namespace translator {

class MainManager final {
public:
    static bool initModWhileLoading(ll::mod::NativeMod& mod);
    static bool initModWhileEnabling(ll::mod::NativeMod& mod);

    static void disableMod();
};

} // namespace translator