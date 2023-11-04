#pragma once

#include <string>
#include <optional>

#include <vulkan/vulkan.hpp>

namespace Dragon {
    struct ResultError {
        std::string message;
        VkResult resultCode = VK_ERROR_UNKNOWN;
    };

    template<typename T> class Result {
        private:
            std::optional<ResultError> error;
            T value;
        public:
            inline Result(ResultError error) {this->error = error;}
            inline Result(T value) {this->value = value;}

            inline ResultError getError() {return this->error.value();}
            inline T getValue() {return this->value;}

            inline operator bool() const {return !this->error.has_value();}
    };
}