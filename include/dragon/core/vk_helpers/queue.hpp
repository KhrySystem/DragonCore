#pragma once

#include <vulkan/vulkan.hpp>

namespace Dragon {
    class Queue;
}

#include "queue_family.hpp"

namespace Dragon {
    class Queue {
        private:
            VkQueue queue;
            QueueFamily queueFamily;
        public:
            operator VkQueue() const;

            inline QueueFamily getQueueFamily() {return this->queueFamily;};
    };
}