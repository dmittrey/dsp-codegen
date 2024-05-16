#pragma once

#include <iostream>
#include <fstream>
#include <regex>

#include <json/json.h>

#include "interface/iregparser.hpp"

using namespace Utility;

namespace Parser {

	//TODO Add parsing exceptions
    struct JsonRegParser final : IRegParser {
    private:
        std::vector<Register> vec = {};
    
    public:
        JsonRegParser(const std::string &fname) {
			std::ifstream istream{fname};
			Json::Value root;
			istream >> root;
			vec = parse_register_vec(root["registers"]);
		}
    
    public:
        const std::vector<Register>& registers() const & override { return vec; }
        void print() const {
            for (const auto& reg : vec)
                reg.dump();
        }

	private:
		static std::vector<Register> parse_register_vec(const Json::Value& val) {
			std::vector<Register> vec = {};
			for (int i = 0; i < val.size(); ++i) {
				vec.push_back(
					parse_register(val[i])
				);
			}
			return vec;
		}

		static Register parse_register(const Json::Value& val) {
			Register r;
			r.name = val["name"].asString();
			r.address = std::stoi(val["address"].asString(), nullptr, 16);
			r.description = val["description"].asString();
			r.size = val["size"].asUInt64();
			if (val["mode"].asString() == "RO")
				r.mode = RO;
			else if (val["mode"].asString() == "WO")
				r.mode = WO;
			else if (val["mode"].asString() == "RW")
				r.mode = RW;
			else
				std::cout << "Need exception!" << std::endl;
			r.options = parse_option_vec(val["options"]);
			return r;
		}

		static std::vector<Option> parse_option_vec(const Json::Value& val) {
			std::vector<Option> vec = {};
			for (int i = 0; i < val.size(); ++i) {
				vec.push_back(
					parse_option(val[i])
				);
			}
			return vec;
		}

		static Option parse_option(const Json::Value& val) {
			std::regex twos_compl_r("t(\\d+)q(\\d+)");
			std::regex sign_magn_r("sm(\\d+)q(\\d+)");
			std::regex signed_r("s(\\d+)q(\\d+)");
			std::regex unsigned_r("u(\\d+)q(\\d+)");

    		std::smatch result;

			Option o;

			std::string fmt_s = val["format"].asString();
			if (std::regex_search(fmt_s, result, twos_compl_r))
				o.format = FP_TWOS_COMPLEMENT;
			else if (std::regex_search(fmt_s, result, sign_magn_r))
				o.format = FP_SIGN_MAGNITUDE;
			else if (std::regex_search(fmt_s, result, signed_r))
				o.format = FP_SIGNED;
			else if (std::regex_search(fmt_s, result, unsigned_r))
				o.format = FP_UNSIGNED;
			else if (fmt_s == "u")
				o.format = HEX_UNSIGNED;
			else if (fmt_s == "s")
				o.format = HEX_SIGNED;
			else
				std::cout << "Need exception!" << std::endl;

			o.name = val["name"].asString();
			o.description = val["description"].asString();

			// TODO Add validation of no interact between ranges and max >= min
			o.bit_range.first = val["range"]["min"].asUInt();
			o.bit_range.second = val["range"]["max"].asUInt();
			return o;
		}
    };

} /* Parser */