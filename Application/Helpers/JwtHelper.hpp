#ifndef JWT_HELPER_HPP
#define JWT_HELPER_HPP

#include <string>

class JwtHelper {
private:
    std::string secret;

public:
    explicit JwtHelper(const std::string& secretKey);

    // Genera un JWT con cod_usuario
    std::string generateToken(const std::string& codUsuario);

    // Valida el JWT y extrae cod_usuario si es válido
    bool validateToken(const std::string& token, std::string& codUsuarioOut);
};

#endif // JWT_HELPER_HPP
