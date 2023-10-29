#pragma once

#include <string>

#include <vulkan/vulkan.hpp>

namespace Dragon {
    struct ResultError {
        std::string message;
        VkResult resultCode = VK_ERROR_UNKNOWN;
    };

    template<typename T> class Result {
        private:
            ResultError error;
            T value;
        public:
            Result(ResultError error);
            Result(T value);

            inline ResultError getError() {return this->error;}
            inline T getValue() {return this->value;}

            operator bool() const;
    };
}