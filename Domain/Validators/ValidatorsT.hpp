#include <regex>
#include <string>
#include <stdexcept>
namespace Domain::Validators{
class Validator {
public:
    static void validate_email(const std::string& email) {
        const std::regex pattern(R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
        if (!std::regex_match(email, pattern)) {
            throw std::invalid_argument("Invalid email format");
        }
    }

    static void validate_phone(const std::string& phone) {
        const std::regex pattern(R"(^\+?[0-9]{7,15}$)");
        if (!std::regex_match(phone, pattern)) {
            throw std::invalid_argument("Invalid phone number format");
        }
    }
};}