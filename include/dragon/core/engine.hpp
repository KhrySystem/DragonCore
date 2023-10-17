#pragma once

#include <vulkan/vulkan.hpp>
namespace Dragon {
    class Engine;
}
#include "Submodule.hpp"
#include <VkBootstrap.h>
#include <exception>
#include <vector>
#include <string>

namespace Dragon {
    struct EngineCreateInfo
    {
        std::string appName;
        uint32_t appVersion = 0;
        bool requestValidationLayers = true;
    };
    

    class Engine
    {
    private:
        std::vector<Submodule*> submodules;
    public:
        Instance instance;
        PhysicalDevice physicalDevice;
        Device device;

        bool addSubmodule(Submodule* submodule);
        void init(EngineCreateInfo &createInfo);

        void update();

        void close();

        ~Engine();
    };
}