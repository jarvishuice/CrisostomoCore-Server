#ifndef SHA256_HELPER_HPP
#define SHA256_HELPER_HPP

#include <string>

namespace Application::Helpers {

class Sha256Helper {
public:
    Sha256Helper() = default;
    ~Sha256Helper() = default;
    
    // Genera el hash SHA-256 en formato hexadecimal
    std::string hash(const std::string& input);
};

} // namespace Application::Helpers

#endif // SHA256_HELPER_HPP
