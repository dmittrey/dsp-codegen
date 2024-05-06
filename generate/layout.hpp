#pragma once

#include <string>
#include <vector>

#include "model.hpp"

namespace Generate {

    struct Layout {
        virtual std::string name() = 0;
        virtual std::vector<Model> models() = 0;
        virtual void add_model(const Model& model) = 0;
        virtual ~Layout() {};
    };

    struct FileLayout : Layout {
        std::string name_;
        std::vector<Model> models_;

        std::string name() override {
            return name_;
        };

        std::vector<Model> models() override {
            return models_;
        };

        void add_model(const Model& model) override {
            models_.push_back(model);
        };
    };
};