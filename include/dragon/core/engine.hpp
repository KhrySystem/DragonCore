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
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugUtilsMessenger;
    std::vector<std::any> submodules;
};

DGAPI DgResult dgInitEngine(DgEngine &engine, DgEngineCreateInfo &createInfo);
DGAPI void dgDestroyEngine(DgEngine &engine);