#pragma once

#include <stdint.h>

namespace Chinar {
    
    class Component {
        public:
            Component(class Actor* owner, const uint32_t updateOrder = 100);

            virtual ~Component() {}

            virtual void processInput(const uint8_t* keyState) {}
            virtual void update(const float deltaTime) {}

            const auto getUpdateOrder() { return mUpdateOrder; }

        protected:

            const uint32_t mUpdateOrder;

            class Actor* mOwner;
    };
}
