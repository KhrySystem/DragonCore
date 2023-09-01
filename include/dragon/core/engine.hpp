#pragma once

#include "config.hpp"
#include "result.hpp"

struct DgSubmodule;

typedef struct DgEngineCreateInfo {
    DgBool32 vulkanDebugEnabled = DG_FALSE;
    std::vector<const char*> vkExtensions;
    std::vector<const char*> vkLayers;
    std::string appName;
} DgEngineCreateInfo;

typedef struct DgEngine {
    DgEngine(DgEngineCreateInfo &createInfo);
    VkInstance instance;
    VkDebugUtilsMessengerEXT debugUtilsMessenger;
    std::vector<DgSubmodule> submodules;
    std::vector<uint8_t> module_type;

    DgResult init();

    ~DgEngine();
} DgEngine;

typedef struct DgCreateInfo_T {
    DgEngine* pEngine;
}DgCreateInfo_T;


typedef struct DgSubmodule {
    uint16_t type;
    DgEngine* pEngine;

    DgSubmodule(DgCreateInfo_T &createInfo);
    virtual DgResult init();
    virtual DgResult update();
} DgSubmodule;
