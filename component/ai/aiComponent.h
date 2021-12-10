#pragma once

#include "component/component.h"
#include <vector>
#include <string>
#include <unordered_map>

namespace Chinar {
    
    class AIComponent : public Component {
        public:
            AIComponent(class Actor* owner);

            void update(const float deltaTime) override;
            void changeState(const std::string& name);

            void registerState(class AIState* state);
        private:

            std::unordered_map<std::string, class AIState*> mStates;

            class AIState* mCurrentState;
    };
}
