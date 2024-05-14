#pragma once

#include "interface/iregparser.hpp"
#include "interface/iserializer.hpp"

#include "register/register.hpp"

using Parser::Register;
using Parser::IRegParser;
using Generate::ISerializer;

namespace Agregate {

    struct Agregator {
    protected:
        const std::unique_ptr<IRegParser> parser_;
        const std::unique_ptr<ISerializer> serializer_;

    public:
        Agregator(std::unique_ptr<IRegParser> &parser, 
                    std::unique_ptr<ISerializer> &serializer) :
            parser_(std::move(parser)), serializer_(std::move(serializer)) {}
        
        virtual ~Agregator() {}

    public:
        virtual void process() const = 0;
    };

}; /* Agregate */