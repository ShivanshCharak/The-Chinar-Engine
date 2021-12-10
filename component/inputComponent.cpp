#include "inputComponent.h"

namespace Chinar {
    
    InputComponent::InputComponent(Actor* owner)
    : MoveComponent(owner)
    , mMaxForwardSpeed{0.0f} 
    , mMaxAngularSpeed{0.0f}
    , mForwardKey{0}
    , mBackKey{0}
    , mClockwiseKey{0}
    , mCounterClockwiseKey{0} {}

    void InputComponent::processInput(const uint8_t* keyState) {

        float forwardSpeed = 0.0f;
        if (keyState[mForwardKey]) {
            forwardSpeed += mMaxForwardSpeed;
        }
        if (keyState[mBackKey]) {
            forwardSpeed -= mMaxForwardSpeed; 
        }
        setForwardSpeed(forwardSpeed);

        float angularSpeed = 0.0f;
        if (keyState[mClockwiseKey]) {
            angularSpeed += mMaxAngularSpeed;
        }
        if (keyState[mCounterClockwiseKey]) {
            angularSpeed -= mMaxAngularSpeed;
        }
        setAngularSpeed(angularSpeed);
    }
}
