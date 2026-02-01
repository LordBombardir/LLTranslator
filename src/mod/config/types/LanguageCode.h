#pragma once

namespace translator::config {

enum class LanguageCode : unsigned short {
    ru = 0x00, // Russian
    en = 0x01, // English
    zh = 0x02, // Chinese
    de = 0x03, // German
    fr = 0x04, // French
    be = 0x05, // Belarusian
    hy = 0x06, // Armenian
    ka = 0x07, // Georgian
    es = 0x08, // Spanish
    it = 0x09, // Italian
    pt = 0x0A, // Portuguese
    // More languages can be added here

    Undefined = 0xFF // Undefined
};

}