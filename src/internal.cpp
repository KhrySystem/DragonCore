#include <dragon/core.hpp>

__DgTypes __dghints;

VkResult dgCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
    PFN_vkCreateDebugUtilsMessengerEXT func = (PFN_vkCreateDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr) {
        return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
    } else {
        #ifndef NDEBUG
        std::cout << "PFN_vkCreateDebugUtilsMessengerEXT (dgCreateDebugUtilsMessengerEXT) was a NULL function\n";
        #endif
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
}

void dgDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT) vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr) {
        func(instance, debugMessenger, pAllocator);
    } else {
        #ifndef NDEBUG
        std::cout << "PFN_vkDestroyDebugUtilsMessengerEXT (dgDestroyDebugUtilsMessengerEXT) was a NULL function\n";
        #endif
    }
}

void dgDestroyDevice(VkInstance instance, VkDevice device, const VkAllocationCallbacks* pAllocator) {
    PFN_vkDestroyDevice func = (PFN_vkDestroyDevice) vkGetInstanceProcAddr(instance, "vkDestroyDevice");
   if (func != nullptr) {
        func(device, pAllocator);
   } else {
        #ifndef NDEBUG
        std::cout << "PFN_vkDestroyDevice (dgDestroyDevice) was a NULL function\n";
        #endif
    }
}