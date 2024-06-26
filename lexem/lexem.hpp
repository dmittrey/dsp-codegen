#pragma once

#include <string>

namespace lxm {

    struct Lexem {
    private:
        std::string internals;
    public:
        Lexem& Return() { internals += "return "; return *this; }
        Lexem& Ioctl() { internals += "ioctl"; return *this; }

        Lexem& Brace() { internals += '('; return *this; }
        Lexem& B_Brace() { internals += ')'; return *this; }

        Lexem& Concat(char* arg) { internals += arg; return *this; }
        Lexem& Concat(const std::string& arg) { internals += arg; return *this; }
        Lexem& Concat_With_Underscore(char* arg) { internals += '_' + std::string(arg) + '_'; return *this; }
        Lexem& Concat_With_Underscore(const std::string& arg) { internals += '_' + std::string(arg) + '_'; return *this; }

        Lexem& Whitespace() { internals += ' '; return *this; }
        Lexem& Word(char* arg) { internals += arg; return *this; }
        Lexem& Word(const std::string& arg) { internals += arg; return *this; }
        Lexem& Equal() { internals += '='; return *this; }

        Lexem& Args(std::initializer_list<char*> list) & {
            bool fst = true;
            for (const auto& elem : list) {
                if (!fst) internals += ", ";
                internals += elem;
                fst = false;
            }
            return *this;
        }
    public:
        operator std::string() const {
            return internals;
        }
    };

}; /* lexem */