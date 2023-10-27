// Based on VkBootstrap, but extended for MacOS

#pragma once

#include <string>

#include "instance.hpp"

namespace Dragon {
    class InstanceBuilder {
        private:
            const char* appName;
            const char* engineName;
            uint32_t appVersion;
            uint32_t engineVersion;
            uint32_t minimumInstanceVersion;
        public:

            InstanceBuilder &setAppName(const char* appName);
            InstanceBuilder &setAppName(std::string appName);
            InstanceBuilder &setEngineName(const char* engineName);
            InstanceBuilder &setEngineName(std::string engineName);
            InstanceBuilder &setAppVersion(uint32_t appVersion);
            InstanceBuilder &setAppVersion(uint32_t major, uint32_t minor, uint32_t revision);
            InstanceBuilder &setAppVersion(uint32_t tweak, uint32_t major, uint32_t minor, uint32_t revision);
            InstanceBuilder &setEngineVersion(uint32_t appVersion);
            InstanceBuilder &setEngineVersion(uint32_t major, uint32_t minor, uint32_t revision);
            InstanceBuilder &setEngineVersion(uint32_t tweak, uint32_t major, uint32_t minor, uint32_t revision);
            InstanceBuilder &requireAPIVersion(uint32_t appVersion);
            InstanceBuilder &requireAPIVersion(uint32_t major, uint32_t minor, uint32_t revision);
            InstanceBuilder &requireAPIVersion(uint32_t tweak, uint32_t major, uint32_t minor, uint32_t revision);
            InstanceBuilder &setMinimumInstanceVersion(uint32_t appVersion);
            InstanceBuilder &setMinimumInstanceVersion(uint32_t major, uint32_t minor, uint32_t revision);
            InstanceBuilder &setMinimumInstanceVersion(uint32_t tweak, uint32_t major, uint32_t minor, uint32_t revision);
            
    };
}