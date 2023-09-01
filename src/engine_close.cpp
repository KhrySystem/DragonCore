#include <dragon/core.hpp>

DGAPI DgEngine::~DgEngine() {
    if(this->debugUtilsMessenger != VK_NULL_HANDLE) {
        dgDestroyDebugUtilsMessengerEXT(this->instance, this->debugUtilsMessenger, nullptr);
    }

    if(this->instance != VK_NULL_HANDLE) {
        vkDestroyInstance(this->instance, nullptr);
    }
}