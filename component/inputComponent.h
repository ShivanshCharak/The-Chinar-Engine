#pragma once

#include "moveComponent.h"

namespace Chinar {
    
    class InputComponent : public MoveComponent {
        public:
            InputComponent(class Actor* owner);

            void processInput(const uint8_t* keyState) override;

            auto getMaxForwardSpeed() const { return mMaxForwardSpeed; }
            auto getMaxAngularSpeed() const { return mMaxAngularSpeed; }
            auto getForwardkey() const { return mForwardKey; }
            auto getBackKey() const { return mBackKey; }
            auto getClockwiseKey() const { return mClockwiseKey; }
            auto getCounterClockwiseKey() const { return mCounterClockwiseKey; }

            void setMaxForwardSpeed(const float speed) { mMaxForwardSpeed = speed; }
            void setMaxAngularSpeed(const float speed) { mMaxAngularSpeed = speed; }
            void setForwardKey(const uint8_t key) { mForwardKey = key; }
            void setBackKey(const uint8_t key) { mBackKey = key; }
            void setClockwiseKey(const uint8_t key) { mClockwiseKey = key; }
            void setCounterClockwiseKey(const uint8_t key) { mCounterClockwiseKey = key; }

        private:

            float mMaxForwardSpeed;
            float mMaxAngularSpeed;

            uint8_t mForwardKey;
            uint8_t mBackKey;

            uint8_t mClockwiseKey;
            uint8_t mCounterClockwiseKey;
    };
}
