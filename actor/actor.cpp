#include "actor.h"
#include "engine.h"
#include <iostream>

namespace Chinar {
    
    Actor::Actor(Engine* engine)
    : mState{EActive}
    , mRotation{0.0f}
    , mScale{1.0f}
    , mEngine{engine} {
        mEngine->addActor(this);
    }

    void Actor::processInput(const uint8_t* keyState) {
        if (mState == EActive) {
            for (auto& comp : mComponents) {
                comp->processInput(keyState);
            }
            actorInput(keyState);
        }
    }

    void Actor::update(const float deltaTime) {
        if (mState == EActive) {
            updateComponents(deltaTime);
            updateActor(deltaTime);
        }
    }

    void Actor::updateComponents(const float deltaTime) {
        for (auto& comp : mComponents) {
            comp->update(deltaTime);
        }
    }

    void Actor::addComponent(Component* component) {
        const auto order = component->getUpdateOrder();
        auto iter = mComponents.begin();
        for (; iter != mComponents.end(); ++iter) {
            if (order < (*iter)->getUpdateOrder()) {
                break;
            }
        }
        mComponents.insert(iter, std::unique_ptr<Component>(component));
    }

    void Actor::removeComponent(Component* component) {
        auto iter = std::find_if(mComponents.begin(), mComponents.end(), [&](const std::unique_ptr<Component>& comp) { return comp.get() == component; } );
        if (iter != mComponents.end()) {
            mComponents.erase(iter);
        }
    }
}
