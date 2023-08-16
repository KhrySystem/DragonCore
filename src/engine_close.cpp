#include <dragon/core.hpp>

DGAPI void dgDestroyEngine(DgEngine &engine) {
    #ifndef DRAGON_NO_VULKAN
        #ifndef NDEBUG
            dgDestroyDebugUtilsMessengerEXT(engine.instance, engine.debugUtilsMessenger, nullptr);
        #endif
        vkDestroyInstance(engine.instance, nullptr);
    #endif
}