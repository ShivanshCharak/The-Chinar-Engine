#pragma once

#include "component.h"

namespace Chinar {
    
    class MoveComponent : public Component {
        public:
            MoveComponent(class Actor* owner, const uint32_t updateOrder = 100);

            void update(const float deltaTime) override;

            float getAngularSpeed() const { return mAngularSpeed; }
            float getForwardSpeed() const { return mForwardSpeed; }

            void setAngularSpeed(const float speed) { mAngularSpeed = speed; }
            void setForwardSpeed(const float speed) { mForwardSpeed = speed; }
        private:

            float mAngularSpeed;
            float mForwardSpeed;
    };
}
