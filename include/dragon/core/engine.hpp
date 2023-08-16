#pragma once

#include "config.hpp"
#include "result.hpp"

struct DgEngineCreateInfo {
    DgBool32 vulkanDebugEnabled = DG_FALSE;
    std::vector<const char*> vkExtensions;
    std::vector<const char*> vkLayers;
    std::string appName;
};

struct DgEngine {
    #ifndef DRAGON_NO_VULKAN
        VkInstance instance;
        #ifndef NDEBUG
            VkDebugUtilsMessengerEXT debugUtilsMessenger;
        #endif
    #endif
    std::vector<boost::any> submodules;
};

DGAPI DgResult dgInitEngine(DgEngine &engine, DgEngineCreateInfo &createInfo);
DGAPI void dgDestroyEngine(DgEngine &engine);