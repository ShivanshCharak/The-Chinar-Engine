#pragma once

#include "math/vector.hpp"
#include "component/component.h"

#include <memory>
#include <vector>

namespace Chinar {
    
    class Actor {
        public:
            
            enum State {
                EActive,
                EPause,
                EDead
            };

            Actor(class Engine* engine);
            virtual ~Actor() {}

            void processInput(const uint8_t* keyState);
            virtual void actorInput(const uint8_t* keyState) {}
            
            void update(const float deltaTime);
            void updateComponents(const float deltaTime);
            virtual void updateActor(const float deltaTime) {}

            State getState() const { return mState; }

            auto& getPosition() const { return mPosition; }
            float getRotation() const { return mRotation; }
            float getScale() const { return mScale; }
            class Engine* getEngine() const { return mEngine; }

            Vector2<float> getForward() {
                return Vector2{std::cos(mRotation), -std::sin(mRotation)};
            }

            void setPosition(const Vector2<float> position) { mPosition = position; }
            void setRotation(const float rotation) { mRotation = rotation; }
            void setScale(const float scale) { mScale = scale; }

            void addComponent(Component* component);
            void removeComponent(Component* component);

        private:

            State mState;

            Vector2<float> mPosition;
            float mRotation;
            float mScale;

            std::vector<std::unique_ptr<Component>> mComponents;

            class Engine* mEngine;
    };
}
