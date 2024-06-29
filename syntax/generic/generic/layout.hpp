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
            const std::vector<IModel*>& models() const & override { return models_; };
            Layout& add_model(IModel* model) override {
                const auto& tmp_vec = model->headers();
                add_headers(tmp_vec);

                models_.push_back(model);
                return *this;
            };
        };

    }; /* generic */
 
}; /* syntax */