#pragma once

#include <memory>
#include <algorithm>

#include "ilayout.hpp"

namespace Syntax {

    struct Layout : ILayout {
    protected:
        std::vector<std::string> headers_;
        std::vector<IModel*> models_;

    protected:
        /* Return const layout to prevent post-prepare modifications(breaks invariant) */
        virtual const Layout& prepare() {
            for (const auto& model : models_) {
                const auto& tmp = model->headers();
                headers_.insert(headers_.end(), tmp.begin(), tmp.end());
            }

            std::sort(headers_.begin(), headers_.end());
            headers_.erase(std::unique(headers_.begin(), headers_.end()), headers_.end());
            return *this;
        }

    public:
        std::vector<IModel*> models() const override { return models_; };
        Layout& add_model(IModel* model) override {
            models_.push_back(model);
            return *this;
        };
    };
 
}; /* Syntax */