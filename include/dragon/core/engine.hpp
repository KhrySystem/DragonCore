#pragma once

#include <vulkan/vulkan.hpp>
namespace Dragon {
    class Engine;
}
#include <VkBootstrap.h>
#include <vector>
#include <string>

#include "submodule.hpp"
#include "config.hpp"
/**
 * @brief Main namespace for everything related to Dragon
*/
namespace Dragon {
    /**
     * @ingroup Core
     * @brief Core engine create info. Required for engine initialization
     * 
     * @see Dragon::Engine::init(EngineCreateInfo &createInfo)
    */
    struct DGCOREAPI EngineCreateInfo
    {
        std::string appName = DRAGON_ENGINE_NAME; /**<Application name to pass to the Vulkan instance. Does not have to be equal to window names from the graphics engine*/
        uint32_t appVersion = 0; /**<Application version made by VK_MAKE_API_VERSION(major, minor, revis, patch) macro.*/
        bool requestValidationLayers = true; /**<set to true if validation layers should be added to the vulkan instance. Validation layers should NOT be added to a Release build in any way, shape, or form and so this should be set by a macro involving NDEBUG */
    };
    
    /**
     * @ingroup Core
     * @brief Core Engine class. Required to use any other functionality of
     * the engine. 
     * 
     * @details 
    */
    class DGCOREAPI Engine
    {
        private:
            std::vector<Submodule*> submodules; /**< The list of all currently active submodules attached to this engine's Vulkan Instance*/
            Instance instance; /**< Vulkan instance data. Parent of all other Vulkan objects. Do not do anything to this unless you know EXACTLY what you're doing.*/
            PhysicalDevice physicalDevice; /**< Vulkan PhysicalDevice data. Represents a GPU of some kind. Do not do anything to this unless you know EXACTLY what you're doing.*/
            Device device; /**< Vulkan Device data. This is the actually useful version of a PhysicalDevice.  Do not do anything to this unless you know EXACTLY what you're doing.*/
            VmaAllocator allocator; /**<Vulkan Memory Allocator object. Ensures we don't go above any buffer limitations.*/

            void instanceCreation(const char* appName, uint32_t appVersion, bool requestValidationLayers);
            void physicalDeviceSelection();
            void deviceCreation();
            void allocatorCreation();

            /**
             * Close function. Is internally called by the destructor.
            */
            void close();
        public:
            /**
             * @brief Returns the Vulkan Instance attached to this object
             * 
             * @returns Dragon::Instance
            */
            inline Instance getInstance() {return this->instance;}
            /**
             * @brief Returns the physical device from which all other GPU objects are created.
             * 
             * @returns Dragon::PhysicalDevice
            */
            inline PhysicalDevice getPhysicalDevice() {return this->physicalDevice;}
            /**
             * @brief Returns the logical GPU device derived from the physical device attached to this engine
             * 
             * @returns Dragon::Device
            */
            inline Device getDevice() {return this->device;}
            /**
             * @brief Returns the VmaAllocator derived from the VkDevice attached to this engine
             * 
             * @returns VmaAllocator
            */
           inline VmaAllocator getAllocator() {return this->allocator;}

            /**
             * Adds a submodule to this engine. Submodules may not be shared across engines.
             * Only one instance of each submodule should be added to each engine. Any class 
             * you pass into this must be dynamically casted into a Dragon::Submodule* 
             * by whichever method you see fit. Submodule should inherit from class Dragon::Submodule.
             * 
             * @param submodule A pointer to the submodule that is being added to this engine.
             * 
             * @throws std::string
            */
            bool addSubmodule(Submodule* submodule);

            /**
             * Fully initializes the engine. After this point, no more submodules should be added as that
             * could produce undefined errors since this function calls the setup for the submodules. 
             * 
             * @param createInfo an instance of Dragon::EngineCreateInfo containing information 
             * to pass to the Vulkan instance and submodules during initialization
             * 
             * @see Dragon::Submodule::beforeInstanceCreation(Dragon::Engine* parent)
             * @see Dragon::Submodule::adjustInstanceParams
             * @see
             * 
             * @throws std::string
            */
            void init(EngineCreateInfo &createInfo);

            /**
             * Update function. Runs the update functions for all other update functions in order. 
             * 
             * @throw std::string
            */
            void update();

            /**
             * Destructor. Engine Destruction always succeeds, however improper submodule code may cause warnings, errors, or memory leaks.
             * 
            */
            ~Engine();
    };
}