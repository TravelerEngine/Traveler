#pragma once

#include "RHI/Queue.h"

#include <vulkan/vulkan.hpp>

#include <memory>

namespace RHI::Vulkan {
    class QueuePrivate;
    class VKQueue : public Queue {
        std::unique_ptr<QueuePrivate> m_private;

    public:
        explicit VKQueue(vk::Queue vkQueue);
        ~VKQueue() override;

        vk::Queue GetQueue() const;
    };
} // namespace RHI::Vulkan
