#include "component.h"
#include "actor/actor.h"

namespace Chinar {
    
    Component::Component(Actor* owner, const uint32_t updateOrder)
    : mOwner{owner}
    , mUpdateOrder{updateOrder} {
        mOwner->addComponent(this);
    }
}
