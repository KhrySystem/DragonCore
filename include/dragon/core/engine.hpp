#pragma once

#include <vulkan/vulkan.hpp>
namespace Dragon {
    class Engine;
}
#include "submodule.hpp"
#include <VkBootstrap.h>
#include <vector>
#include <string>

namespace Dragon {
    /**
     * @ingroup Core
     * @brief Core engine create info. Required for engine initialization
     * 
     * @see Dragon::Engine::init(EngineCreateInfo &createInfo)
    */
    struct EngineCreateInfo
    {
        std::string appName = DRAGON_ENGINE_NAME; /**<Application name to pass to the Vulkan instance. Does not have to be equal to window names from the graphics engine*/
        /**
         * Application version made by VK_MAKE_API_VERSION(major, minor, revis, patch) macro.
        */
        uint32_t appVersion = 0; 
        bool requestValidationLayers = true; /**<set to true if validation layers should be added to the vulkan instance. Validation layers should NOT be added to a Release build in any way, shape, or form and so this should be set by a macro involving NDEBUG */

    };
    
    /**
     * @ingroup Core
     * @brief Core Engine class. Required to use any other functionality of
     * the engine. 
     * 
     * @details 
    */
    class Engine
    {
    private:

        std::vector<Submodule*> submodules; /**< The list of all currently active submodules attached to this engine's Vulkan Instance*/
    public:
        Instance instance; /**< Vulkan instance data. Parent of all other Vulkan objects. Do not do anything to this unless you know EXACTLY what you're doing.*/
        PhysicalDevice physicalDevice; /**< Vulkan PhysicalDevice data. Represents a GPU of some kind. Do not do anything to this unless you know EXACTLY what you're doing.*/
        Device device; /**< Vulkan Device data. This is the actually useful version of a PhysicalDevice.  Do not do anything to this unless you know EXACTLY what you're doing.*/

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

        void close();

        ~Engine();
    };
}