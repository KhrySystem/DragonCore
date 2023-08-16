#include <dragon/core.hpp>
#ifndef DRAGON_NO_VULKAN
    #include "engine_vk_init.hpp"
#endif

void _safeAddToVector(std::vector<const char*> &vector, const char* value) {
    for(const char* v: vector) {
        if(strcmp(v, value) == 0) {
            return;
        }
    }
    vector.push_back(value);
}

DGAPI DgResult dgInitEngine(DgEngine &engine, DgEngineCreateInfo &createInfo) {
    DgResult r = DG_SUCCESS;

    #ifndef DRAGON_NO_VULKAN
        _safeAddToVector(createInfo.vkExtensions, VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
        #ifndef NDEBUG
        _safeAddToVector(createInfo.vkExtensions, VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
        _safeAddToVector(createInfo.vkLayers, "VK_LAYER_KHRONOS_validation");
        #endif
        r = _dgVkEngineInit(engine, createInfo.appName, createInfo.vkExtensions, createInfo.vkLayers);
        if(r != DG_SUCCESS) return r;
    #endif

    return r;
}