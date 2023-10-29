#pragma once

#include <string>

#include "instance.hpp"
#include "result.hpp"

namespace Dragon {
    class InstanceBuilder {
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
            VkInstanceCreateFlags flags;
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
}