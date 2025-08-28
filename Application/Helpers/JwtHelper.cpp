#include "JwtHelper.hpp"
#include <jwt.h>
#include <stdexcept>
#include <cstring>
#include <ctime>
#include <iostream>
#include "../../Infrastructure/Providers/Logs.hpp"

JwtHelper::JwtHelper(const std::string& secretKey) : secret(secretKey) {}

std::string JwtHelper::generateToken(const std::string& codUsuario) {
    auto &log = Logger::instance();
    jwt_t* jwt = nullptr;
    if (jwt_new(&jwt) != 0) {
        throw std::runtime_error("Error al crear el JWT");
    }

    jwt_add_grant(jwt, "cod_usuario", codUsuario.c_str());
    // Establecer algoritmo y clave secreta correctamente
    log.debug(" decret value "+secret);
    jwt_set_alg(jwt, JWT_ALG_HS256,
        reinterpret_cast<const unsigned char*>(secret.c_str()),
        secret.size());
    time_t now = time(nullptr);
    time_t exp = now +  5;//3600; // 3600 segundos = 1 hora
    jwt_add_grant_int(jwt,"exp",exp);
    char* encoded = jwt_encode_str(jwt);
    std::string token(encoded);

    jwt_free(jwt);
    free(encoded);

    return token;
}

bool JwtHelper::validateToken(const std::string& token, std::string& codUsuarioOut) {
    jwt_t* jwt = nullptr;
    if (jwt_decode(&jwt, token.c_str(), reinterpret_cast<const unsigned char*>(secret.c_str()), secret.size()) != 0) {
        return false; // Token inválido o firma incorrecta
    }

    const char* cod = jwt_get_grant(jwt, "cod_usuario");
    if (!cod) {
        jwt_free(jwt);
        return false; // No contiene cod_usuario
    }

    codUsuarioOut = std::string(cod);
    jwt_free(jwt);
    return true;
}
