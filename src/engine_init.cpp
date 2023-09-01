#include <dragon/core.hpp>
#include "engine_vk_init.hpp"

void _safeAddToVector(std::vector<const char*> &vector, const char* value) {
    for(const char* v: vector) {
        if(strcmp(v, value) == 0) {
            return;
        }
    }
    vector.push_back(value);
}

DGAPI DgEngine::DgEngine(DgEngineCreateInfo &createInfo) {
    _safeAddToVector(createInfo.vkExtensions, VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
    #ifndef NDEBUG
    _safeAddToVector(createInfo.vkExtensions, VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
    _safeAddToVector(createInfo.vkLayers, "VK_LAYER_KHRONOS_validation");
    #endif

    // App info. Contains info about the Engine, the user app, etc.
    VkApplicationInfo appInfo;

    // Use the version that matches the shaders
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pNext = nullptr; // pNext is required to be null based on VkError 0x48eb8c19

	appInfo.apiVersion = VK_API_VERSION_1_2;
	appInfo.applicationVersion = APP_VERSION;
	appInfo.pApplicationName = appName.c_str();
	appInfo.pEngineName = "Dragon Engine";
	appInfo.engineVersion = DRAGON_VERSION;

    // Instance Create Info. Used in the vkCreateInstance function
	VkInstanceCreateInfo createInfo;

	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pNext = nullptr;

	createInfo.enabledExtensionCount = vExtensions.size();
	createInfo.ppEnabledExtensionNames = vExtensions.data();

    #ifndef NDEBUG
		createInfo.enabledLayerCount = vLayers.size();
        createInfo.ppEnabledLayerNames = vLayers.data();
    #else
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
	#endif

    #if BOOST_OS_MACOS
        createInfo.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
    #endif

    createInfo.pApplicationInfo = &appInfo;

    VkResult r = vkCreateInstance(&createInfo, nullptr, &engine.instance);
    if(r != VK_SUCCESS) {
        
    }

    return DG_SUCCESS;;

}

DGAPI DgResult DgEngine::init() {
    for(DgSubmodule submodule : this->submodules) {
        submodule.init();
    }
}