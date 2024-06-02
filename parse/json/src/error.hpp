#pragma once

namespace Parse {

    enum class OptionError {
        INVALID_FORMAT_TYPE,
        INVALID_FORMAT_VALUE,
        INVALID_NAME_TYPE,
        INVALID_DESCRIPTION_TYPE,
        INVALID_BIT_RANGE_TYPE,
        INVALID_BIT_RANGE_VALUE,
        INVALID_BIT_RANGE_MIN_TYPE,
        INVALID_BIT_RANGE_MAX_TYPE,
    };

    enum class RegisterError {
        INVALID_NAME_TYPE,
        INVALID_ADDRESS_TYPE,
        INVALID_DESCRIPTION_TYPE,
        INVALID_SIZE_TYPE,
        INVALID_MODE_TYPE,
        INVALID_MODE_VALUE,
        INVALID_OPTIONS_TYPE,
    };

}; /* Parser */