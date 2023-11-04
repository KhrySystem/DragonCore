#include <dragon/core.hpp>
namespace Dragon {
    Result<Instance> InstanceBuilder::build() {
        Instance instance;

        VkApplicationInfo appInfo{};
        appInfo.apiVersion = this->apiVersion;
        appInfo.applicationVersion = this->appVersion;
        appInfo.engineVersion = this->engineVersion;
        appInfo.pApplicationName = this->appName;
        appInfo.pEngineName = this->engineName;
        appInfo.pNext = nullptr;
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;

        VkInstanceCreateInfo createInfo{};
        createInfo.enabledExtensionCount = this->extensions.size();
        createInfo.ppEnabledExtensionNames = this->extensions.data();
        createInfo.flags = this->flags;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.pNext = nullptr;
        if(this->useValidation) {
            createInfo.ppEnabledLayerNames = this->layers.data();
            createInfo.enabledLayerCount = this->layers.size();
        } else {
            createInfo.ppEnabledLayerNames = nullptr;
            createInfo.enabledLayerCount = 0;
        }
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;

        VkResult res = vkCreateInstance(&createInfo, this->pAllocCallbacks, &instance.instance);

        if(res != VK_SUCCESS) {
            ResultError error;
            error.message = fmt::format("Could not create VkInstance! Resulting error code was {}", string_VkResult(res));
            error.message = res;
            return Result<Instance>(error);
        }
        return Result<Instance>(instance);
    }

    void InstanceBuilder::setAppName(const char* appName) {
        this->appName = appName;
    }

    void InstanceBuilder::setAppName(std::string appName) {
        this->appName = appName.c_str();
    }

    void InstanceBuilder::setEngineName(const char* engineName) {
        this->engineName = engineName;
    }

    void InstanceBuilder::setEngineName(std::string engineName) {
        this->engineName = engineName.c_str();
    }

    void InstanceBuilder::setAppVersion(uint32_t appVersion) {
        this->appVersion = appVersion;
    }

    void InstanceBuilder::setAppVersion(uint32_t major, uint32_t minor, uint32_t revision) {
        this->appVersion = VK_MAKE_API_VERSION(0, major, minor, revision);
    }

    void InstanceBuilder::setAppVersion(uint32_t tweak, uint32_t major, uint32_t minor, uint32_t revision) {
        this->appVersion = VK_MAKE_API_VERSION(tweak, major, minor, revision);
    }

    void InstanceBuilder::setEngineVersion(uint32_t engineVersion) {
        this->engineVersion = engineVersion;
    }

    void InstanceBuilder::setEngineVersion(uint32_t major, uint32_t minor, uint32_t revision) {
        this->engineVersion = VK_MAKE_API_VERSION(0, major, minor, revision);
    }

    void InstanceBuilder::setEngineVersion(uint32_t tweak, uint32_t major, uint32_t minor, uint32_t revision) {
        this->engineVersion = VK_MAKE_API_VERSION(tweak, major, minor, revision);
    }

    void InstanceBuilder::requireAPIVersion(uint32_t apiVersion) {
        this->apiVersion = apiVersion;
    }

    void InstanceBuilder::requireAPIVersion(uint32_t major, uint32_t minor, uint32_t revision) {
        this->apiVersion = VK_MAKE_API_VERSION(0, major, minor, revision);
    }

    void InstanceBuilder::requireAPIVersion(uint32_t tweak, uint32_t major, uint32_t minor, uint32_t revision) {
        this->apiVersion = VK_MAKE_API_VERSION(tweak, major, minor, revision);
    }

    void InstanceBuilder::requestValidationLayers() {
        this->useValidation = true;
    }

    void InstanceBuilder::useDefaultDebugMessenger() {

    }

    void InstanceBuilder::enableValidationLayer(const char* layerName) {
        for(auto alreadyAdded : this->layers) {
            if(strcmp(alreadyAdded, layerName) == 0) {
                return;
            }
        }
        this->layers.push_back(layerName);
    }

    void InstanceBuilder::enableValidationLayer(std::string layerName) {
        this->layers.push_back(layerName.c_str());
    }

    void InstanceBuilder::enableExtension(const char* extName) {
        for(auto alreadyAdded : this->extensions) {
            if(strcmp(alreadyAdded, extName) == 0) {
                return;
            }
        }
        this->extensions.push_back(extName);
    }

    void InstanceBuilder::enableExtension(std::string extName) {
        this->enableExtension(extName.c_str());
    }

    void InstanceBuilder::setAllocationCallbacks(VkAllocationCallbacks &allocCallbacks) {
        this->pAllocCallbacks = &allocCallbacks;
    }

    Instance::~Instance() {
        for(auto physicalDevice : this->physicalDevices) {
            delete physicalDevice;
        }
        vkDestroyInstance(this->instance, this->allocCallbacks);
    }
}