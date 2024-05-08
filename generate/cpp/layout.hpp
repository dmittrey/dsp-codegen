#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "interface/ilayout.hpp"

namespace Generate {

    struct CppLayout : ILayout {
        std::vector<std::string> headers_;
        std::vector<IModel*> models_;

        std::vector<IModel*> models() override {
            return models_;
        };

        void add_model(IModel* model) override {
            auto tmp = model->headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());
            models_.push_back(model);
        };

        std::string render() const override {
            std::string res;
            res += std::string("// Headers\n");
            for (auto header : headers_)
                res += "#include <" + header + '>' + '\n';

            res += std::string("// Models\n");
            for (auto model : models_)
                res += model->code();
            
            return res;
        };
    };
};