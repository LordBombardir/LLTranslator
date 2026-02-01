#pragma once

#include "LanguageCode.h"
#include "TranslationServer.h"

#include <string>

namespace translator::config {

struct Config {
    int               version             = 1;
    std::string       defaultLocaleCode   = "en_US";
    TranslationServer server              = TranslationServer::Google;
    LanguageCode      destinationLanguage = LanguageCode::en;
};

} // namespace translator