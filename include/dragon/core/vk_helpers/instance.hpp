#pragma once

#include <vulkan/vulkan.h>

#include "../result.hpp"

namespace Dragon {
    class PhysicalDevice;
    class Instance;

    class DGCOREAPI InstanceBuilder {
        private:
            const char* appName = "";
            const char* engineName = "";
            uint32_t appVersion = 0;
            uint32_t engineVersion = 0;
            uint32_t apiVersion = 0;
            VkAllocationCallbacks* pAllocCallbacks;
            std::vector<const char*> extensions;
            std::vector<const char*> layers;
            bool useValidation;
            VkInstanceCreateFlags flags = 0;

        public:
            Result<Instance> build();

            void setAppName(const char* appName);
            void setAppName(std::string appName);
            void setEngineName(const char* engineName);
            void setEngineName(std::string engineName);
            void setAppVersion(uint32_t appVersion);
            void setAppVersion(uint32_t major, uint32_t minor, uint32_t revision);
            void setAppVersion(uint32_t tweak, uint32_t major, uint32_t minor, uint32_t revision);
            void setEngineVersion(uint32_t appVersion);
            void setEngineVersion(uint32_t major, uint32_t minor, uint32_t revision);
            void setEngineVersion(uint32_t tweak, uint32_t major, uint32_t minor, uint32_t revision);
            void requireAPIVersion(uint32_t appVersion);
            void requireAPIVersion(uint32_t major, uint32_t minor, uint32_t revision);
            void requireAPIVersion(uint32_t tweak, uint32_t major, uint32_t minor, uint32_t revision);
            void requestValidationLayers();
            void useDefaultDebugMessenger();
            void enableValidationLayer(const char* layerName);
            void enableValidationLayer(std::string layerName);
            void enableExtension(const char* extName);
            void enableExtension(std::string extName);
            void setAllocationCallbacks(VkAllocationCallbacks &allocCallbacks);
    };

    class DGCOREAPI Instance {
        private:
            VkInstance instance;
            VkDebugUtilsMessengerEXT debugMessenger;
            VkAllocationCallbacks* allocCallbacks;
            std::vector<PhysicalDevice*> physicalDevices;
        public:
            inline VkDebugUtilsMessengerEXT getDebugMessenger() {return this->debugMessenger;}
            inline VkAllocationCallbacks* getAllocationCallbacks() {return this->allocCallbacks;}

            inline operator VkInstance() const {return this->instance;}

            ~Instance();

            friend class InstanceBuilder;
            friend class PhysicalDevice;
    };
}