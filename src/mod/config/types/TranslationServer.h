#pragma once

namespace translator::config {

enum class TranslationServer : unsigned short {
    Google = 0x00, // translate.googleapis.com
    // More servers can be added here

    Undefined = 0xFF, // Undefined
};

}