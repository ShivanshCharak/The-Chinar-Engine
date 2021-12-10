#include "moveComponent.h"
#include "util/math.h"
#include "actor/actor.h"

namespace Chinar {
    
    MoveComponent::MoveComponent(Actor* owner, const uint32_t updateOrder)
    : Component(owner, updateOrder)
    , mAngularSpeed{0.0f}
    , mForwardSpeed{0.0f} {}

    void MoveComponent::update(const float deltaTime) {
        if (!Math::nearZero(mAngularSpeed)) {
            float rot = mOwner->getRotation();
            rot += mAngularSpeed * deltaTime;
            mOwner->setRotation(rot);
        }

        if (!Math::nearZero(mForwardSpeed)) {
            auto pos = mOwner->getPosition();
            pos += mOwner->getForward() * mForwardSpeed * deltaTime;
            mOwner->setPosition(pos);
        }
    }
}
