#pragma once

/**
 * @defgroup Core Core Engine
 * 
 * @brief This group containst structs and classes from the Dragon::Core module
*/
/* DGAPI is used to declare public API functions for export
 * from the DLL / shared library / dynamic library.
 */
#if defined(_WIN32) && defined(DRAGON_CORE_BUILD_DLL)
 /* We are building Dragon as a Win32 DLL */
 #define DGCOREAPI __declspec(dllexport)
#elif defined(_WIN32) && defined(DRAGON_CORE_DLL)
 /* We are calling a Win32 DLL */
 #define DGCOREAPI __declspec(dllimport)
#elif defined(__GNUC__) && defined(DRAGON_CORE_BUILD_DLL)
 /* We are building Dragon as a Unix shared library */
 #define DGCOREAPI __attribute__((visibility("default")))
#else
 #define DGCOREAPI
#endif

// Predecl
namespace Dragon {
    class Engine;
    class Instance;
    class PhysicalDevice;
    class Device;
    class Queue;
}

#include <boost/predef.h>
#include <boost/preprocessor.hpp>
#if BOOST_OS_WINDOWS
    #define VK_USE_PLATFORM_WIN32_KHR
#endif

#include <vulkan/vulkan.hpp>

#include <fmt/core.h>

#include <vk_mem_alloc.h>

#include "core/vk_helpers/buffer.hpp"
#include "core/vk_helpers/device.hpp"
#include "core/vk_helpers/instance.hpp"
#include "core/vk_helpers/physical_device.hpp"
#include "core/vk_helpers/queue.hpp"
#include "core/vk_helpers/vk_enum_string_helper.h"
#include "core/config.hpp"
#include "core/engine.hpp"
#include "core/result.hpp"
#include "core/submodule.hpp"