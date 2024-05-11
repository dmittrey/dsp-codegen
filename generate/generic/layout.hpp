#pragma once

#include <memory>

#include "interface/ilayout.hpp"

namespace Generate {

    struct Layout : ILayout {
    protected:
        std::vector<std::string> headers_;
        std::vector<IModel*> models_; // Fix Migrate to unique ptr

    public:
        std::vector<IModel*> models() const override { return models_; };
        Layout& add_model(IModel* model) override {
            const auto& tmp = model->headers();
            headers_.insert(headers_.end(), tmp.begin(), tmp.end());

            models_.push_back(model);
            return *this;
        };
    };
 
}; /* Generate */