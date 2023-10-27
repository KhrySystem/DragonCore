#pragma once

#include <vulkan/vulkan.hpp>

namespace Dragon {
    class Instance;
}

#include "instance_builder.hpp"

namespace Dragon {
    class Instance {
        private:
            VkInstance instance;
            VkDebugUtilsMessengerEXT debugMessenger;
            VkAllocationCallbacks* allocCallbacks;
        public:
            inline VkInstance getInstance() {return this->instance;}
            inline VkDebugUtilsMessengerEXT getDebugMessenger() {return this->debugMessenger;}
            inline VkAllocationCallbacks* getAllocationCallbacks() {return this->allocCallbacks;}

            operator VkInstance() const;

            friend class InstanceBuilder;
            friend class PhysicalDeviceSelector;
    };
}