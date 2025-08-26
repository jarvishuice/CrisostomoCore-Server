#include "Sha256Helper.hpp"
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <stdexcept>

namespace Application::Helpers {

std::string Sha256Helper::hash(const std::string& input) {
    // Validar entrada
    if (input.empty()) {
        return "";
    }
    
    unsigned char hash[SHA256_DIGEST_LENGTH];
    
    // Calcular hash SHA256
    if (!SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash)) {
        throw std::runtime_error("Error al calcular hash SHA256");
    }

    std::ostringstream oss;
    for (size_t i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        // Usar unsigned int para evitar problemas con valores negativos
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(hash[i]);
    }

    return oss.str();
}

} // namespace Application::Helpers
