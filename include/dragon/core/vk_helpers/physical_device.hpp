#pragma once

#include <vulkan/vulkan.h>

#include "instance.hpp"

namespace Dragon {
    class PhysicalDevice {
        private:
            Instance instance;
            VkPhysicalDevice physicalDevice;
        public:
            operator VkPhysicalDevice() const;
    };
}