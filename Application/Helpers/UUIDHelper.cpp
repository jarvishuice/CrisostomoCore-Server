#include "UUIDHelper.hpp"
#include <random>
#include <string>

// Generador de UUID v4 minimalista
std::string generateUuidV4() {
    static const char* hex = "0123456789abcdef";
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> disHex(0, 15);
    static std::uniform_int_distribution<> disVar(8, 11);

    std::string uuid;
    uuid.reserve(36);

    // 8 hex
    for (int i = 0; i < 8; ++i) uuid += hex[disHex(gen)];
    uuid += '-';

    // 4 hex
    for (int i = 0; i < 4; ++i) uuid += hex[disHex(gen)];
    uuid += '-';

    // 4 hex (versión 4)
    uuid += '4';
    for (int i = 0; i < 3; ++i) uuid += hex[disHex(gen)];
    uuid += '-';

    // 4 hex (variante RFC4122)
    uuid += hex[disVar(gen)];
    for (int i = 0; i < 3; ++i) uuid += hex[disHex(gen)];
    uuid += '-';

    // 12 hex
    for (int i = 0; i < 12; ++i) uuid += hex[disHex(gen)];

    return uuid;
}