#include "aiComponent.h"
#include "aiState.h"
#include "actor/actor.h"
#include "exception/exception.h"

namespace Chinar {

    AIComponent::AIComponent(Actor* actor)
    : Component(actor) {}
    
    void AIComponent::registerState(AIState* state) {
        mStates.emplace(state->getName(), state);
    }

    void AIComponent::update(const float deltaTime) {
        if (mCurrentState) {
            mCurrentState->update(deltaTime);
        }
    }
    
    void AIComponent::changeState(const std::string& stateName) {
        if (mCurrentState) {
            mCurrentState->onExit();
        }
        auto iter = mStates.find(stateName);
        if (iter != mStates.end()) {
            mCurrentState = iter->second;
            mCurrentState->onEnter();
        } else {
            mCurrentState = nullptr;
            throw AIException("AIComponent::changeState", "Could not find AIState", stateName, "in state map");
        }
    }
}
