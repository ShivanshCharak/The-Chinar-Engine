#pragma once

#include <vector>
#include <SDL2/SDL.h>

#include "spriteComponent.h"

namespace Chinar {
    
    class AnimSpriteComponent : public SpriteComponent {
        public:
            AnimSpriteComponent(class Actor* owner, const uint32_t drawOrder = 100);

            void update(const float deltaTime) override;

            void setAnimTextures(const std::vector<SDL_Texture*>& texture);

            void setAnimFPS(const float fps) { mAnimFPS = fps; }
            auto getAnimFPS() const { return mAnimFPS; }
        private:
            float mAnimFPS;
            float mCurrentFrame;
            std::vector<SDL_Texture*> mAnimTextures;
    };
}
