#pragma once

#include <VkBootstrap.h>
#include "engine.hpp"

#include "aliases.hpp"

namespace Dragon
{
    /**
     * @ingroup Core
     * 
     * @brief Submodule Parent class. All valid submodules should inherit from this class.
     * 
     * @see Dragon::Engine::addSubmodule()
    */
    class Submodule
    {
        public:
            /**
             * @brief Called when the submodule is added to the core engine via the addSubmodule call.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to.
             * 
             * @see Dragon::Engine::addSubmodule()
             * 
             * @throws std::string
            */
            virtual void onAddition(Engine* parent) {}

            /**
             * @brief Called before the VkInstance is populated. May include optional
             * configuration pertaining to access of other submodules. No 
             * logic from engine being improperly initialized should happen 
             * in this function.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to.
             * 
             * @throws std::string
            */
            virtual void beforeInstanceCreation(Engine* parent) {}
            /**
             * @brief Called during initialization in chain with all the other 
             * submodules. No logic from engine being improperly initialized 
             * should happen in this function.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to.
             * @param previous the InstanceBuilder after coming out of the previously chained submodule
             * 
             * @throws std::string
             * 
             * @returns The InstanceBuilder after being adjusted by this submodule's needs
            */
            virtual InstanceBuilder adjustInstanceParams(Engine* parent, InstanceBuilder &previous) {return previous;}
            /**
             * @brief Called after VkInstance creation. No logic from engine being 
             * improperly initialized should happen in this function.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to.
             * 
             * @throws std::string
            */
            virtual void afterInstanceCreation(Engine* parent) {}

            /**
             * @brief Called after final Dragon::Submodule::afterInstanceCreation() calls, but before the PhysicalDevice is selected.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to.
             * 
             * @throws std::string
            */
            virtual void beforePhysicalDeviceSelection(Engine* parent) {}
            /**
             * @brief Called during initialization in chain with all the other 
             * submodules. No logic from engine being improperly initialized 
             * should happen in this function.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to.
             * @param previous the PhysicalDeviceSelector after coming out of the previously chained submodule
             * 
             * @throws std::string
             * 
             * @returns The PhysicalDeviceSelector after being adjusted by this submodule's needs
            */
            virtual Dragon::PhysicalDeviceSelector adjustPhysicalDeviceParams(Engine* parent, PhysicalDeviceSelector &previous) {return previous;}
            /**
             * @brief Called after Physical Device selection. No logic from engine being 
             * improperly initialized should happen in this function.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to
             * 
             * @throws std::string
            */
            virtual void afterPhysicalDeviceSelection(Engine* parent) {}

            /**
             * @brief Called after final Dragon::Submodule::afterPhysicalDeviceSelection() calls, but before the VkDevice is created from the VkPhysicalDevice instance.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to.
             * 
             * @throws std::string
            */
            virtual void beforeDeviceCreation(Engine* parent) {}
            /**
             * @brief Called during initialization in chain with all the other 
             * submodules. No logic from engine being improperly initialized 
             * should happen in this function.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to.
             * @param previous the DeviceBuilder after coming out of the previously chained submodule
             * 
             * @throws std::string
             * 
             * @returns The PhysicalDeviceSelector after being adjusted by this submodule's needs
            */
            virtual DeviceBuilder adjustDeviceParams(Engine* parent, DeviceBuilder &previous) {return previous;}
            /**
             * @brief Called after Device Creation. No logic from engine being 
             * improperly initialized should happen in this function.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to
             * 
             * @throws std::string
            */
           virtual void afterDeviceCreation(Engine* parent) {}

            /**
             * @brief Updates the internal state of the submodule
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to
             * 
             * @throws std::string
            */
            virtual void update(Engine* parent) {}

            /**
             * @brief Called before all other close() functions. All close functions should always suceed.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to
            */
            virtual void beforeClose(Engine* parent) {}
            /**
             * @brief Cleans up the main body of the submodule. All close functions should always suceed.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to
            */
            virtual void close(Engine* parent) {}
            /**
             * @brief Called after all other close() functions. All close functions should always suceed.
             * 
             * @param parent A pointer to the Dragon::Engine instance that this submodule is attached to
            */
            virtual void afterClose(Engine* parent) {}
    };
} // namespace Dragon
