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
            const std::vector<std::string>& headers() const & override { return headers_; }
            Layout& add_model(IModel* model) override {
                models_.push_back(model);
                return *this;
            };
        };

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

    }; /* generic */
 
}; /* syntax */