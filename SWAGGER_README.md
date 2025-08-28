# 📚 Controlador Swagger para Crisostomo Core API

## 🎯 Descripción

El `SwaggerController` es un controlador especializado que genera automáticamente la documentación OpenAPI 3.0 (Swagger) para todos los endpoints de tu API REST. Proporciona una interfaz web interactiva y un archivo JSON estándar para integración con herramientas de desarrollo.

## 🚀 Características

- **📖 Documentación automática**: Genera documentación OpenAPI 3.0 completa
- **🌐 Interfaz web interactiva**: Swagger UI integrado para probar endpoints
- **📄 Esquemas detallados**: Modelos de datos completos con ejemplos
- **🏷️ Categorización**: Endpoints organizados por tags (Autenticación, Usuarios)
- **📱 Responsive**: Interfaz adaptada para diferentes dispositivos
- **🔒 Seguridad**: Documentación de esquemas de autenticación JWT

## 📋 Endpoints del Controlador

### 1. **GET /swagger.json**
- **Descripción**: Especificación OpenAPI en formato JSON
- **Tipo de respuesta**: `application/json`
- **Uso**: Para integración con herramientas de desarrollo, Postman, etc.

### 2. **GET /docs**
- **Descripción**: Interfaz web Swagger UI
- **Tipo de respuesta**: `text/html`
- **Uso**: Para desarrolladores y testing de la API

## 🏗️ Estructura de la Documentación

### 📚 Esquemas de Datos

#### **User Entity**
```json
{
  "cod": "string (opcional)",
  "firstname": "string (requerido)",
  "lastName": "string (requerido)",
  "middleName": "string (opcional)",
  "username": "string (requerido)",
  "password": "string (requerido, hash SHA256)",
  "email": "string (requerido, formato email)",
  "phone": "string (requerido)",
  "birthdate": "string (requerido, formato date)",
  "dateRegister": "string (opcional, formato date-time)",
  "dateUpdate": "string (opcional, formato date-time)"
}
```

#### **Login Request**
```json
{
  "username": "string (requerido)",
  "password": "string (requerido)"
}
```

#### **Login Response**
```json
{
  "token": "string (JWT token)"
}
```

### 🏷️ Tags de Endpoints

#### **🔐 Autenticación**
- `POST /auth/signup` - Registrar nuevo usuario
- `POST /auth/login` - Autenticar usuario
- `GET /auth/health` - Estado del servicio

#### **👥 Usuarios**
- `GET /users` - Lista de usuarios
- `GET /users/{cod}` - Usuario específico

## 🛠️ Instalación y Uso

### 1. **Compilar el proyecto**
```bash
cd build
cmake ..
make
```

### 2. **Ejecutar la aplicación**
```bash
./api_rest_app
```

### 3. **Acceder a la documentación**
- **Swagger UI**: http://localhost:8080/docs
- **OpenAPI JSON**: http://localhost:8080/swagger.json

## 🔧 Integración en tu Aplicación

### **Incluir el controlador**
```cpp
#include "Presentation/Controllers/SwaggerController.hpp"

// En tu función main:
SwaggerController swaggerController;
swaggerController.setupRoutes(app);
```

### **Orden de configuración**
```cpp
// 1. Configurar controladores de negocio
userController.setupRoutes(app);
authController.setupRoutes(app);

// 2. Configurar Swagger (debe ir al final)
swaggerController.setupRoutes(app);
```

## 📊 Beneficios

### **Para Desarrolladores**
- ✅ Documentación siempre actualizada
- ✅ Interfaz interactiva para testing
- ✅ Ejemplos de uso incluidos
- ✅ Esquemas de datos claros

### **Para Integración**
- ✅ Estándar OpenAPI 3.0
- ✅ Compatible con Postman, Insomnia
- ✅ Generación automática de clientes
- ✅ CI/CD friendly

### **Para Mantenimiento**
- ✅ Documentación centralizada
- ✅ Cambios automáticos al modificar endpoints
- ✅ Versionado de API
- ✅ Historial de cambios

## 🔍 Personalización

### **Modificar información de la API**
Edita el método `generateOpenAPISpec()` en `SwaggerController.cpp`:

```cpp
spec << R"({
  "openapi": "3.0.3",
  "info": {
    "title": "Tu Título Personalizado",
    "description": "Tu descripción personalizada",
    "version": "2.0.0",
    "contact": {
      "name": "Tu Equipo",
      "email": "tu@email.com"
    }
  }
```

### **Agregar nuevos endpoints**
1. Crea el método en el controlador correspondiente
2. Agrega la documentación en `generateAuthEndpoints()` o `generateUserEndpoints()`
3. Actualiza los esquemas si es necesario

## 🚨 Consideraciones

### **Seguridad**
- La documentación Swagger está disponible públicamente
- Considera proteger `/docs` en producción
- No expongas información sensible en ejemplos

### **Performance**
- La generación de OpenAPI es estática
- No impacta el rendimiento de los endpoints de negocio
- Swagger UI se carga desde CDN externo

### **Mantenimiento**
- Actualiza la documentación cuando modifiques endpoints
- Mantén ejemplos actualizados
- Revisa esquemas de respuesta

## 📞 Soporte

Si tienes problemas o sugerencias para mejorar el controlador Swagger:

1. Revisa los logs de la aplicación
2. Verifica que todos los controladores estén configurados
3. Confirma que el CMakeLists.txt incluya `SwaggerController.cpp`

## 🔮 Futuras Mejoras

- [ ] Autenticación en Swagger UI
- [ ] Ejemplos de código en múltiples lenguajes
- [ ] Validación de esquemas en tiempo real
- [ ] Métricas de uso de la API
- [ ] Exportación a PDF/HTML estático

---

**🎉 ¡Disfruta de tu API completamente documentada!**
