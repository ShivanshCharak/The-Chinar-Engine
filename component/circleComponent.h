#pragma once

#include "math/vector.hpp"
#include "component.h"

namespace Chinar {
    
    class CircleComponent : public Component {
        public:
            CircleComponent(class Actor* owner);

            void setRadius(const float radius) { mRadius = radius; }
            auto getRadius() const { return mRadius; }

            const Vector2<float>& getCenter() const;
        private:
            float mRadius;
    };

    bool interset(const CircleComponent& a, const CircleComponent& b);
}
