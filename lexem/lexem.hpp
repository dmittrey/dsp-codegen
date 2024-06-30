#pragma once

#include <string>

struct Lexem {
private:
    std::string internals;

    enum State {
        INVALID = 0,
        NEED_WS = 1,
        NEED_BRACE = 2,
        NO_WS = 3,
        MAX = 4
    };

    State state = INVALID;
public:
    Lexem& Return() { internals += "return"; state = State::NEED_WS; return *this; }
    Lexem& Ioctl() { if (state == NEED_WS) internals += ' '; internals += "ioctl"; state = State::NEED_BRACE; return *this; }

    Lexem& Concat(char* arg) { if (state == NEED_WS) internals += ' '; internals += arg; state = NEED_WS; return *this; }
    Lexem& Concat(const std::string& arg) { if (state == NEED_WS) internals += ' '; internals += arg; state = NEED_WS; return *this; }

    Lexem& Braces(const std::string& arg) { if (state == NEED_WS) internals += ' '; internals += '('; internals += arg; internals += ')'; state = NO_WS; return *this; }

    Lexem& Equal() { if (state == NEED_WS) internals += ' '; internals += '='; state = NEED_WS; return *this; }

    Lexem& Star() { if (state == NEED_WS) internals += ' '; internals += '*'; return *this; }

    Lexem& Mul() { internals += ' '; internals += '*'; state = NEED_WS; return *this; }
    Lexem& Div() { internals += ' '; internals += '/'; state = NEED_WS; return *this; }

    Lexem& LShift(int shift) { internals += ' '; internals += "<< " + std::to_string(shift); state = NEED_WS; return *this; }

    Lexem& LogOr() { internals += ' '; internals += '|'; state = NEED_WS; return *this; }
    Lexem& LogMul() { internals += ' '; internals += '&'; state = NEED_WS; return *this; }
    Lexem& LogInv() { internals += ' '; internals += '~'; state = NEED_WS; return *this; }

    Lexem& CondIfElse(const std::string &cond, const std::string &if_body, const std::string &else_body) {
        internals += ' '; internals += cond + " ? " + if_body + " : " + else_body; state = NEED_WS; return *this;
    }

    Lexem& Args(std::initializer_list<char*> list) & {
        bool fst = true;
        internals += '(';
        for (const auto& elem : list) {
            if (!fst) internals += ", ";
            internals += elem;
            fst = false;
        }
        internals += ')';
        return *this;
    }
    Lexem& Args(std::initializer_list<std::string> list) & {
        bool fst = true;
        internals += '(';
        for (const auto& elem : list) {
            if (!fst) internals += ", ";
            internals += elem;
            fst = false;
        }
        internals += ')';
        return *this;
    }
public:
    operator std::string() const {
        return internals;
    }
};