#include <regex>
#include <fstream>

#include <json/json.h>

#include "error.hpp"

#include "json/regparser.hpp"

namespace parse {

    struct JsonRegParser final : IRegParser {
	private:
	    std::vector<util::Register> vec = {};

	public:
	    JsonRegParser(const std::string &fname) {
			std::ifstream istream{fname};
			try {
				Json::Value root;
				istream >> root;
				if (!root.isObject()) {
					std::cout << "Root is not object!" << std::endl;
				} else {
					if (!root.isMember("registers") || !root["registers"].isArray()) {
						std::cout << "Root is not include 'registers' array" << std::endl;
					} else {
						vec = parse_register_vec(root["registers"]);
					}
				}
			} catch (const Json::RuntimeError & e) {
				std::cout << e.what() << std::endl;
			}
		}
	
	public:
	    const std::vector<util::Register>& registers() const & noexcept override { return vec; }
	    void print() const {
	        for (const auto& reg : vec)
	            reg.dump();
	    }

	private:
		static std::vector<util::Register> parse_register_vec(const Json::Value& val) {
			std::vector<util::Register> vec = {};
			RegisterError err;
			for (int i = 0; i < val.size(); ++i) {
				auto r = parse_register(val[i], &err);
				if (r.has_value()) {
					vec.push_back(r.value());
				} else {
					std::cout << "Cannot parse " << i+1 << "'th register: ";
					switch(err) {
						case RegisterError::INVALID_NAME_TYPE:
							std::cout << "Not include 'name' string" << std::endl;
							break;
        				case RegisterError::INVALID_ADDRESS_TYPE:
							std::cout << "Unsupported 'address' value" << std::endl;
							break;
       					case RegisterError::INVALID_DESCRIPTION_TYPE:
							std::cout << "Not include 'description' string" << std::endl;
							break;
        				case RegisterError::INVALID_SIZE_TYPE:
							std::cout << "Not include 'size' uint" << std::endl;
							break;
        				case RegisterError::INVALID_MODE_TYPE:
							std::cout << "Not include 'mode' string" << std::endl;
							break;
        				case RegisterError::INVALID_MODE_VALUE:
							std::cout << "Unsupported 'mode' value" << std::endl;
							break;
        				case RegisterError::INVALID_OPTIONS_TYPE:
							std::cout << "Not include 'options' array" << std::endl;
							break;
					}
				}
			}
			return vec;
		}

		static std::optional<util::Register> parse_register(const Json::Value& val, RegisterError * const errp) {
			util::Register r;
			if (val.isObject()) {
				if (!val.isMember("name") || !val["name"].isString()) {
					*errp = RegisterError::INVALID_NAME_TYPE;
					return std::nullopt;
				}
				if (!val.isMember("address") || !val["address"].isString()) {
					*errp = RegisterError::INVALID_ADDRESS_TYPE;
					return std::nullopt;
				}
				if (!val.isMember("description") || !val["description"].isString()) {
					*errp = RegisterError::INVALID_DESCRIPTION_TYPE;
					return std::nullopt;
				}
				if (!val.isMember("size") || !val["size"].isUInt()) {
					*errp = RegisterError::INVALID_SIZE_TYPE;
					return std::nullopt;
				}
				if (!val.isMember("mode") || !val["mode"].isString()) {
					*errp = RegisterError::INVALID_MODE_TYPE;
					return std::nullopt;
				}
				if (!val.isMember("options") || !val["options"].isArray()) {
					*errp = RegisterError::INVALID_OPTIONS_TYPE;
					return std::nullopt;
				}
			}

			r.name = val["name"].asString();
			r.address = std::stoi(val["address"].asString(), nullptr, 16);
			r.description = val["description"].asString();
			r.size = val["size"].asUInt();
			if (val["mode"].asString() == "RO")
				r.mode = util::RO;
			else if (val["mode"].asString() == "WO")
				r.mode = util::WO;
			else if (val["mode"].asString() == "RW")
				r.mode = util::RW;
			else {
				*errp = RegisterError::INVALID_MODE_VALUE;
				return std::nullopt;
			}
			r.options = parse_option_vec(val["options"], r.name);
			return r;
		}

		static std::vector<util::Option> parse_option_vec(const Json::Value& val, const std::string& reg_name) {
			std::vector<util::Option> vec = {};
			OptionError err;
			for (int i = 0; i < val.size(); ++i) {
				auto o = parse_option(val[i], &err);
				if (o.has_value()) {
					vec.push_back(o.value());
				} else {
					std::cout << "Cannot parse " << i+1 << "'th option in " << reg_name << ": ";
					switch(err) {
						case OptionError::INVALID_FORMAT_TYPE:
							std::cout << "Not include 'format' string" << std::endl;
							break;
        				case OptionError::INVALID_FORMAT_VALUE:
							std::cout << "Unsupported 'format' value" << std::endl;
							break;
       					case OptionError::INVALID_NAME_TYPE:
							std::cout << "Not include 'name' string" << std::endl;
							break;
        				case OptionError::INVALID_DESCRIPTION_TYPE:
							std::cout << "Not include 'description' string" << std::endl;
							break;
        				case OptionError::INVALID_BIT_RANGE_TYPE:
							std::cout << "Not include 'range' object" << std::endl;
							break;
        				case OptionError::INVALID_BIT_RANGE_VALUE:
							std::cout << "Unsupported bit range" << std::endl;
							break;
        				case OptionError::INVALID_BIT_RANGE_MIN_TYPE:
							std::cout << "Not include 'min' uint in 'range' object" << std::endl;
							break;
        				case OptionError::INVALID_BIT_RANGE_MAX_TYPE:
							std::cout << "Not include 'max' uint in 'range' object" << std::endl;
							break;
					}
				}
			}
			return vec;
		}

		static std::optional<util::Option> parse_option(const Json::Value& val, OptionError * const errp) {
			std::regex twos_compl_r("t(\\d+)q(\\d+)");
			std::regex sign_magn_r("sm(\\d+)q(\\d+)");
			std::regex signed_r("s(\\d+)q(\\d+)");
			std::regex unsigned_r("u(\\d+)q(\\d+)");

	    	std::smatch result;

			util::Option o;
			if (val.isObject()) {
				if (!val.isMember("format") || !val["format"].isString()) {
					*errp = OptionError::INVALID_FORMAT_TYPE;
					return std::nullopt;
				}
				if (!val.isMember("name") || !val["name"].isString()) {
					*errp = OptionError::INVALID_NAME_TYPE;
					return std::nullopt;
				}
				if (!val.isMember("description") || !val["description"].isString()) {
					*errp = OptionError::INVALID_DESCRIPTION_TYPE;
					return std::nullopt;
				}
				if (!val.isMember("range") || !val["range"].isObject()) {
					*errp = OptionError::INVALID_BIT_RANGE_TYPE;
					return std::nullopt;
				}
				if (!val["range"].isMember("min") || !val["range"]["min"].isUInt()) {
					*errp = OptionError::INVALID_BIT_RANGE_MIN_TYPE;
					return std::nullopt;
				}
				if (!val["range"].isMember("max") || !val["range"]["max"].isUInt()) {
					*errp = OptionError::INVALID_BIT_RANGE_MAX_TYPE;
					return std::nullopt;
				}
			}

			std::string fmt_s = val["format"].asString();
			if (std::regex_search(fmt_s, result, twos_compl_r))
				o.format = util::FP_TWOS_COMPLEMENT;
			else if (std::regex_search(fmt_s, result, sign_magn_r))
				o.format = util::FP_SIGN_MAGNITUDE;
			else if (std::regex_search(fmt_s, result, signed_r))
				o.format = util::FP_SIGNED;
			else if (std::regex_search(fmt_s, result, unsigned_r))
				o.format = util::FP_UNSIGNED;
			else if (fmt_s == "u")
				o.format = util::HEX_UNSIGNED;
			else if (fmt_s == "s")
				o.format = util::HEX_SIGNED;
			else {
				*errp = OptionError::INVALID_FORMAT_VALUE;
				return std::nullopt;
			}

			o.name = val["name"].asString();
			o.description = val["description"].asString();
			o.bit_range.first = val["range"]["min"].asUInt();
			o.bit_range.second = val["range"]["max"].asUInt();
			if (o.bit_range.first > o.bit_range.second) {
				*errp = OptionError::INVALID_BIT_RANGE_VALUE;
				return std::nullopt;
			}

			return o;
		}
	};

    std::unique_ptr<IRegParser> make_json_regparser(const std::string& fname) {
        return std::make_unique<JsonRegParser>(fname);
    }

}; /* parser */