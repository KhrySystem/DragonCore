#pragma once

#include <vulkan/vulkan.h>

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
            inline VkDebugUtilsMessengerEXT getDebugMessenger() {return this->debugMessenger;}
            inline VkAllocationCallbacks* getAllocationCallbacks() {return this->allocCallbacks;}

            operator VkInstance() const;

            void cleanup();

            friend class InstanceBuilder;
    };
}