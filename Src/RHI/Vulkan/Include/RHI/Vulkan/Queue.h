#pragma once

#include <vulkan/vulkan.hpp>

#include <memory>

namespace RHI::Vulkan {
    class QueuePrivate;
    class VKQueue {
        std::unique_ptr<QueuePrivate> m_private;

    public:
        explicit VKQueue(vk::Queue vkQueue);
        ~VKQueue();

        vk::Queue GetQueue() const;
    };
} // namespace RHI::Vulkan
