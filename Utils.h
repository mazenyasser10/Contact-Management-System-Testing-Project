#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <cctype>
#include <string>

class Utils {
public:
    static bool isValidName(const std::string& name) {
        for (size_t i = 0; i < name.size(); ++i) {
            const char c = name[i];
            if (c != ' ' && c != '\t' && c != '\r' && c != '\n')
                return true;
        }
        return false;
    }

    static bool isValidPhone(const std::string& phone) {
        if (phone.empty())
            return false;
        for (size_t i = 0; i < phone.size(); ++i) {
            if (!std::isdigit(static_cast<unsigned char>(phone[i])))
                return false;
        }
        return true;
    }

    static bool contains(const std::string& text, const std::string& keyword) {
        if (keyword.empty())
            return false;
        std::string lhs = toLower(text);
        std::string rhs = toLower(keyword);
        return lhs.find(rhs) != std::string::npos;
    }

private:
    static std::string toLower(const std::string& input) {
        std::string out = input;
        std::transform(out.begin(), out.end(), out.begin(), [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
        return out;
    }
};

#endif
