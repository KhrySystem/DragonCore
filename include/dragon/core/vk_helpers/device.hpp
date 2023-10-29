#pragma once

#include <vulkan/vulkan.h>
#include "physical_device.hpp"
#include "queue.hpp"

namespace Dragon {
    class Device {
        private:
            PhysicalDevice physicalDevice;
            VkDevice device;


        public:
            operator VkDevice() const;

            Queue getQueue();

            void cleanup();
    };
}

