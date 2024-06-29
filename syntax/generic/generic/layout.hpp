#pragma once

#include <memory>
#include <algorithm>

#include "ilayout.hpp"

namespace stx {

    namespace gen {

        struct Layout : ILayout {
        protected:
            std::vector<IModel*> models_;

        public:
            const std::vector<IModel*>& models() const override { return models_; };
            Layout& add_model(IModel* model) override {
                const auto& tmp = model->headers();
                headers_.insert(headers_.end(), tmp.begin(), tmp.end());

                std::sort(headers_.begin(), headers_.end());
                headers_.erase(std::unique(headers_.begin(), headers_.end()), headers_.end());

                models_.push_back(model);
                return *this;
            };
        };

    }; /* generic */
 
}; /* syntax */