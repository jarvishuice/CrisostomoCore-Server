#include "SwaggerController.hpp"
#include <sstream>
#include <ctime>

void SwaggerController::setupRoutes(crow::SimpleApp& app)
{
    // GET /swagger.json → Documentación OpenAPI en formato JSON
    CROW_ROUTE(app, "/swagger.json")
    ([this]() -> crow::response {
        std::cout << "Petición GET /swagger.json recibida\n";
        
        std::string openAPISpec = generateOpenAPISpec();
        
        crow::response resp{openAPISpec};
        resp.set_header("Content-Type", "application/json");
        return resp;
    });

    // GET /docs → Página HTML con Swagger UI
    CROW_ROUTE(app, "/docs")
    ([this]() -> crow::response {
        std::cout << "Petición GET /docs recibida\n";
        
        std::string htmlContent = R"(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Crisostomo API - Documentación</title>
    <link rel="stylesheet" type="text/css" href="https://unpkg.com/swagger-ui-dist@5.9.0/swagger-ui.css" />
    <style>
        html { box-sizing: border-box; overflow: -moz-scrollbars-vertical; overflow-y: scroll; }
        *, *:before, *:after { box-sizing: inherit; }
        body { margin:0; background: #fafafa; }
    </style>
</head>
<body>
    <div id="swagger-ui"></div>
    <script src="https://unpkg.com/swagger-ui-dist@5.9.0/swagger-ui-bundle.js"></script>
    <script src="https://unpkg.com/swagger-ui-dist@5.9.0/swagger-ui-standalone-preset.js"></script>
    <script>
        window.onload = function() {
            const ui = SwaggerUIBundle({
                url: '/swagger.json',
                dom_id: '#swagger-ui',
                deepLinking: true,
                presets: [
                    SwaggerUIBundle.presets.apis,
                    SwaggerUIStandalonePreset
                ],
                plugins: [
                    SwaggerUIBundle.plugins.DownloadUrl
                ],
                layout: "StandaloneLayout"
            });
        };
    </script>
</body>
</html>
        )";
        
        crow::response resp{htmlContent};
        resp.set_header("Content-Type", "text/html");
        return resp;
    });
}

std::string SwaggerController::generateOpenAPISpec()
{
    std::ostringstream spec;
    
    // Inicio del documento OpenAPI
    spec << "{\n";
    spec << "  \"openapi\": \"3.0.3\",\n";
    spec << "  \"info\": {\n";
    spec << "    \"title\": \"Crisostomo Core API\",\n";
    spec << "    \"description\": \"API REST para el sistema Crisostomo Core con autenticación JWT y gestión de usuarios\",\n";
    spec << "    \"version\": \"1.0.0\",\n";
    spec << "    \"contact\": {\n";
    spec << "      \"name\": \"Crisostomo Core Team\",\n";
    spec << "      \"email\": \"support@crisostomo.com\"\n";
    spec << "    }\n";
    spec << "  },\n";
    spec << "  \"servers\": [\n";
    spec << "    {\n";
    spec << "      \"url\": \"http://localhost:2007\",\n";
    spec << "      \"description\": \"Servidor de desarrollo\"\n";
    spec << "    }\n";
    spec << "  ],\n";
    spec << "  \"paths\": {\n";
    
    // Agregar endpoints de autenticación
    spec << generateAuthEndpoints();
    
    // Agregar endpoints de usuarios
    spec << generateUserEndpoints();
    
    // Cerrar paths
    spec << "  },\n";
    
    // Components
    spec << "  \"components\": {\n";
    spec << "    \"schemas\": {\n";
    
    // User schema
    spec << "      \"User\": {\n";
    spec << "        \"type\": \"object\",\n";
    spec << "        \"properties\": {\n";
    spec << "          \"cod\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Código único del usuario\",\n";
    spec << "            \"example\": \"USR001\"\n";
    spec << "          },\n";
    spec << "          \"firstname\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Nombre del usuario\",\n";
    spec << "            \"example\": \"Juan\"\n";
    spec << "          },\n";
    spec << "          \"lastName\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Apellido del usuario\",\n";
    spec << "            \"example\": \"Pérez\"\n";
    spec << "          },\n";
    spec << "          \"middleName\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"nullable\": true,\n";
    spec << "            \"description\": \"Segundo nombre\",\n";
    spec << "            \"example\": \"Carlos\"\n";
    spec << "          },\n";
    spec << "          \"username\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Nombre de usuario para login\",\n";
    spec << "            \"example\": \"juan.perez\"\n";
    spec << "          },\n";
    spec << "          \"password\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Contraseña del usuario (hash SHA256)\",\n";
    spec << "            \"example\": \"5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8\"\n";
    spec << "          },\n";
    spec << "          \"email\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"format\": \"email\",\n";
    spec << "            \"description\": \"Correo electrónico del usuario\",\n";
    spec << "            \"example\": \"juan.perez@email.com\"\n";
    spec << "          },\n";
    spec << "          \"phone\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Número de teléfono\",\n";
    spec << "            \"example\": \"+1234567890\"\n";
    spec << "          },\n";
    spec << "          \"birthdate\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"format\": \"date\",\n";
    spec << "            \"description\": \"Fecha de nacimiento\",\n";
    spec << "            \"example\": \"1990-01-01\"\n";
    spec << "          },\n";
    spec << "          \"dateRegister\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"format\": \"date-time\",\n";
    spec << "            \"description\": \"Fecha de registro\",\n";
    spec << "            \"example\": \"2024-01-01T00:00:00Z\"\n";
    spec << "          },\n";
    spec << "          \"dateUpdate\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"format\": \"date-time\",\n";
    spec << "            \"description\": \"Fecha de última actualización\",\n";
    spec << "            \"example\": \"2024-01-01T00:00:00Z\"\n";
    spec << "          }\n";
    spec << "        },\n";
    spec << "        \"required\": [\"firstname\", \"lastName\", \"username\", \"password\", \"email\", \"phone\", \"birthdate\"]\n";
    spec << "      },\n";
    
    // LoginRequest schema
    spec << "      \"LoginRequest\": {\n";
    spec << "        \"type\": \"object\",\n";
    spec << "        \"properties\": {\n";
    spec << "          \"username\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Nombre de usuario\",\n";
    spec << "            \"example\": \"juan.perez\"\n";
    spec << "          },\n";
    spec << "          \"password\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Contraseña del usuario\",\n";
    spec << "            \"example\": \"miContraseña123\"\n";
    spec << "          }\n";
    spec << "        },\n";
    spec << "        \"required\": [\"username\", \"password\"]\n";
    spec << "      },\n";
    
    // LoginResponse schema
    spec << "      \"LoginResponse\": {\n";
    spec << "        \"type\": \"object\",\n";
    spec << "        \"properties\": {\n";
    spec << "          \"token\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Token JWT para autenticación\",\n";
    spec << "            \"example\": \"eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...\"\n";
    spec << "          }\n";
    spec << "        }\n";
    spec << "      },\n";
    
    // SignUpResponse schema
    spec << "      \"SignUpResponse\": {\n";
    spec << "        \"type\": \"object\",\n";
    spec << "        \"properties\": {\n";
    spec << "          \"message\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Mensaje de confirmación\",\n";
    spec << "            \"example\": \"User created successfully\"\n";
    spec << "          }\n";
    spec << "        }\n";
    spec << "      },\n";
    
    // UsersList schema
    spec << "      \"UsersList\": {\n";
    spec << "        \"type\": \"object\",\n";
    spec << "        \"properties\": {\n";
    spec << "          \"users\": {\n";
    spec << "            \"type\": \"array\",\n";
    spec << "            \"items\": {\n";
    spec << "              \"$ref\": \"#/components/schemas/User\"\n";
    spec << "            }\n";
    spec << "          }\n";
    spec << "        }\n";
    spec << "      },\n";
    
    // Error schema
    spec << "      \"Error\": {\n";
    spec << "        \"type\": \"object\",\n";
    spec << "        \"properties\": {\n";
    spec << "          \"error\": {\n";
    spec << "            \"type\": \"string\",\n";
    spec << "            \"description\": \"Descripción del error\",\n";
    spec << "            \"example\": \"Error interno del servidor\"\n";
    spec << "          }\n";
    spec << "        }\n";
    spec << "      }\n";
    spec << "    },\n";
    
    // Security schemes
    spec << "    \"securitySchemes\": {\n";
    spec << "      \"bearerAuth\": {\n";
    spec << "        \"type\": \"http\",\n";
    spec << "        \"scheme\": \"bearer\",\n";
    spec << "        \"bearerFormat\": \"JWT\",\n";
    spec << "        \"description\": \"Token JWT obtenido del endpoint de login\"\n";
    spec << "      }\n";
    spec << "    }\n";
    spec << "  },\n";
    
    // Tags
    spec << "  \"tags\": [\n";
    spec << "    {\n";
    spec << "      \"name\": \"Autenticación\",\n";
    spec << "      \"description\": \"Endpoints para registro y autenticación de usuarios\"\n";
    spec << "    },\n";
    spec << "    {\n";
    spec << "      \"name\": \"Usuarios\",\n";
    spec << "      \"description\": \"Gestión y consulta de usuarios del sistema\"\n";
    spec << "    }\n";
    spec << "  ]\n";
    spec << "}";
    
    return spec.str();
}

std::string SwaggerController::generateAuthEndpoints()
{
    std::ostringstream endpoints;
    
    // /auth/signup
    endpoints << "    \"/auth/signup\": {\n";
    endpoints << "      \"post\": {\n";
    endpoints << "        \"tags\": [\"Autenticación\"],\n";
    endpoints << "        \"summary\": \"Registrar nuevo usuario\",\n";
    endpoints << "        \"description\": \"Crea un nuevo usuario en el sistema con los datos proporcionados\",\n";
    endpoints << "        \"operationId\": \"signupUser\",\n";
    endpoints << "        \"requestBody\": {\n";
    endpoints << "          \"required\": true,\n";
    endpoints << "          \"content\": {\n";
    endpoints << "            \"application/json\": {\n";
    endpoints << "              \"schema\": {\n";
    endpoints << "                \"$ref\": \"#/components/schemas/User\"\n";
    endpoints << "              },\n";
    endpoints << "              \"examples\": {\n";
    endpoints << "                \"nuevoUsuario\": {\n";
    endpoints << "                  \"summary\": \"Ejemplo de nuevo usuario\",\n";
    endpoints << "                  \"value\": {\n";
    endpoints << "                    \"firstname\": \"María\",\n";
    endpoints << "                    \"lastName\": \"García\",\n";
    endpoints << "                    \"username\": \"maria.garcia\",\n";
    endpoints << "                    \"password\": \"contraseña123\",\n";
    endpoints << "                    \"email\": \"maria.garcia@email.com\",\n";
    endpoints << "                    \"phone\": \"+1234567890\",\n";
    endpoints << "                    \"birthdate\": \"1995-05-15\"\n";
    endpoints << "                  }\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          }\n";
    endpoints << "        },\n";
    endpoints << "        \"responses\": {\n";
    endpoints << "          \"201\": {\n";
    endpoints << "            \"description\": \"Usuario creado exitosamente\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/SignUpResponse\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          },\n";
    endpoints << "          \"400\": {\n";
    endpoints << "            \"description\": \"Datos de entrada inválidos\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/Error\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          },\n";
    endpoints << "          \"500\": {\n";
    endpoints << "            \"description\": \"Error interno del servidor\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/Error\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          }\n";
    endpoints << "        }\n";
    endpoints << "      }\n";
    endpoints << "    },\n";
    
    // /auth/login
    endpoints << "    \"/auth/login\": {\n";
    endpoints << "      \"post\": {\n";
    endpoints << "        \"tags\": [\"Autenticación\"],\n";
    endpoints << "        \"summary\": \"Autenticar usuario\",\n";
    endpoints << "        \"description\": \"Autentica un usuario con sus credenciales y retorna un token JWT\",\n";
    endpoints << "        \"operationId\": \"loginUser\",\n";
    endpoints << "        \"requestBody\": {\n";
    endpoints << "          \"required\": true,\n";
    endpoints << "          \"content\": {\n";
    endpoints << "            \"application/json\": {\n";
    endpoints << "              \"schema\": {\n";
    endpoints << "                \"$ref\": \"#/components/schemas/LoginRequest\"\n";
    endpoints << "              },\n";
    endpoints << "              \"examples\": {\n";
    endpoints << "                \"credenciales\": {\n";
    endpoints << "                  \"summary\": \"Ejemplo de credenciales\",\n";
    endpoints << "                  \"value\": {\n";
    endpoints << "                    \"username\": \"juan.perez\",\n";
    endpoints << "                    \"password\": \"miContraseña123\"\n";
    endpoints << "                  }\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          }\n";
    endpoints << "        },\n";
    endpoints << "        \"responses\": {\n";
    endpoints << "          \"200\": {\n";
    endpoints << "            \"description\": \"Login exitoso\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/LoginResponse\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          },\n";
    endpoints << "          \"400\": {\n";
    endpoints << "            \"description\": \"Formato JSON inválido o campos faltantes\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/Error\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          },\n";
    endpoints << "          \"401\": {\n";
    endpoints << "            \"description\": \"Credenciales inválidas\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/Error\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          },\n";
    endpoints << "          \"500\": {\n";
    endpoints << "            \"description\": \"Error interno del servidor\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/Error\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          }\n";
    endpoints << "        }\n";
    endpoints << "      }\n";
    endpoints << "    },\n";
    
    // /auth/health
    endpoints << "    \"/auth/health\": {\n";
    endpoints << "      \"get\": {\n";
    endpoints << "        \"tags\": [\"Autenticación\"],\n";
    endpoints << "        \"summary\": \"Estado del servicio de autenticación\",\n";
    endpoints << "        \"description\": \"Verifica el estado del servicio de autenticación\",\n";
    endpoints << "        \"operationId\": \"authHealth\",\n";
    endpoints << "        \"responses\": {\n";
    endpoints << "          \"200\": {\n";
    endpoints << "            \"description\": \"Servicio funcionando correctamente\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"type\": \"object\",\n";
    endpoints << "                  \"properties\": {\n";
    endpoints << "                    \"status\": {\n";
    endpoints << "                      \"type\": \"string\",\n";
    endpoints << "                      \"example\": \"healthy\"\n";
    endpoints << "                    },\n";
    endpoints << "                    \"service\": {\n";
    endpoints << "                      \"type\": \"string\",\n";
    endpoints << "                      \"example\": \"authentication\"\n";
    endpoints << "                    },\n";
    endpoints << "                    \"timestamp\": {\n";
    endpoints << "                      \"type\": \"integer\",\n";
    endpoints << "                      \"example\": 1704067200\n";
    endpoints << "                    }\n";
    endpoints << "                  }\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          }\n";
    endpoints << "        }\n";
    endpoints << "      }\n";
    endpoints << "    }";
    
    return endpoints.str();
}

std::string SwaggerController::generateUserEndpoints()
{
    std::ostringstream endpoints;
    
    // /users
    endpoints << ",\n";
    endpoints << "    \"/users\": {\n";
    endpoints << "      \"get\": {\n";
    endpoints << "        \"tags\": [\"Usuarios\"],\n";
    endpoints << "        \"summary\": \"Obtener lista de usuarios\",\n";
    endpoints << "        \"description\": \"Retorna la lista completa de usuarios registrados en el sistema\",\n";
    endpoints << "        \"operationId\": \"getUsers\",\n";
    endpoints << "        \"responses\": {\n";
    endpoints << "          \"200\": {\n";
    endpoints << "            \"description\": \"Lista de usuarios obtenida exitosamente\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/UsersList\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          },\n";
    endpoints << "          \"500\": {\n";
    endpoints << "            \"description\": \"Error interno del servidor\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/Error\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          }\n";
    endpoints << "        }\n";
    endpoints << "      }\n";
    endpoints << "    },\n";
    
    // /users/{cod}
    endpoints << "    \"/users/{cod}\": {\n";
    endpoints << "      \"get\": {\n";
    endpoints << "        \"tags\": [\"Usuarios\"],\n";
    endpoints << "        \"summary\": \"Obtener usuario por código\",\n";
    endpoints << "        \"description\": \"Retorna la información de un usuario específico por su código\",\n";
    endpoints << "        \"operationId\": \"getUserByCode\",\n";
    endpoints << "        \"parameters\": [\n";
    endpoints << "          {\n";
    endpoints << "            \"name\": \"cod\",\n";
    endpoints << "            \"in\": \"path\",\n";
    endpoints << "            \"required\": true,\n";
    endpoints << "            \"description\": \"Código único del usuario\",\n";
    endpoints << "            \"schema\": {\n";
    endpoints << "              \"type\": \"string\"\n";
    endpoints << "            },\n";
    endpoints << "            \"example\": \"USR001\"\n";
    endpoints << "          }\n";
    endpoints << "        ],\n";
    endpoints << "        \"responses\": {\n";
    endpoints << "          \"200\": {\n";
    endpoints << "            \"description\": \"Usuario encontrado exitosamente\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/User\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          },\n";
    endpoints << "          \"404\": {\n";
    endpoints << "            \"description\": \"Usuario no encontrado\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/Error\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          },\n";
    endpoints << "          \"500\": {\n";
    endpoints << "            \"description\": \"Error interno del servidor\",\n";
    endpoints << "            \"content\": {\n";
    endpoints << "              \"application/json\": {\n";
    endpoints << "                \"schema\": {\n";
    endpoints << "                  \"$ref\": \"#/components/schemas/Error\"\n";
    endpoints << "                }\n";
    endpoints << "              }\n";
    endpoints << "            }\n";
    endpoints << "          }\n";
    endpoints << "        }\n";
    endpoints << "      }\n";
    endpoints << "    }";
    
    return endpoints.str();
}
