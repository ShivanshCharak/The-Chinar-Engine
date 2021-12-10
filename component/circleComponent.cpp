#include "circleComponent.h"
#include "actor/actor.h"

namespace Chinar {

    CircleComponent::CircleComponent(Actor* owner)
    : Component(owner)
    , mRadius{0.0f} {}

    const Vector2<float>& CircleComponent::getCenter() const {
        return mOwner->getPosition();
    }

    bool intersect(const CircleComponent& a, const CircleComponent& b) {
        
        auto diff = a.getCenter() - b.getCenter();
        float distSq = diff.lengthSq();

        float radiiSq = a.getRadius() * b.getRadius();
        radiiSq *= radiiSq;

        return distSq <= radiiSq;
    }
}
