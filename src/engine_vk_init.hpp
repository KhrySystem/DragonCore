#pragma once

#include <dragon/core.hpp>

DgResult _dgVkEngineInit(
    DgEngine &engine, std::string appName, 
    std::vector<const char*> &vExtensions, std::vector<const char*> vLayers
) {
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
        printf("0x%x\n", r);
        return DG_VK_CREATE_INSTANCE_FAILED;
    }

    return DG_SUCCESS;
}

#ifndef NDEBUG
VKAPI_ATTR VkBool32 VKAPI_CALL _dgVulkanDebugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
    fprintf(stderr, "Vulkan Debug:\n\tSeverity: 0x%x\n\tMessage: %s\n", messageSeverity, pCallbackData->pMessage);
    return VK_FALSE;
}

DgResult _dgVulkanDebugInit(DgEngine &engine) {
    VkDebugUtilsMessengerCreateInfoEXT createInfo{};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
	createInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
	createInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
	createInfo.pfnUserCallback = _dgVulkanDebugCallback;
	createInfo.pUserData = nullptr;

    VkResult result = dgCreateDebugUtilsMessengerEXT(engine.instance, &createInfo, nullptr, &engine.debugUtilsMessenger);
	if (result == VK_SUCCESS) {
		return DG_SUCCESS;
	} else if(result == VK_ERROR_EXTENSION_NOT_PRESENT) {
        return DG_VK_EXTENSION_NOT_PRESENT;
    }
	return DG_VULKAN_DEBUG_UTILS_INSTANCE_CREATION_FAILED;
}
#endif

DgResult _dgVkGPUInit(DgEngine &engine) {
    return DG_SUCCESS;
}