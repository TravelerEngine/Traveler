#include <utility>

#include "RHI/Vulkan/Queue.h"

namespace RHI::Vulkan {
    using std::shared_ptr;

    class QueuePrivate {
    public:
        vk::Queue vkQueue;
        explicit QueuePrivate(vk::Queue vkQueue)
            : vkQueue(vkQueue)
        {}

        ~QueuePrivate() = default;
    };

    VKQueue::VKQueue(vk::Queue vkQueue)
        : m_private(std::make_unique<QueuePrivate>(vkQueue))
    {
    }

    VKQueue::~VKQueue() = default;

    vk::Queue VKQueue::GetQueue() const
    {
        return m_private->vkQueue;
    }
} // namespace RHI::Vulkan
