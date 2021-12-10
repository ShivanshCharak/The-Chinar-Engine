#pragma once

#include "spriteComponent.h"
#include "math/vector.hpp"

#include <SDL2/SDL.h>
#include <vector>

namespace Chinar {
    
    class BGSpriteComponent : public SpriteComponent {
        public:
            BGSpriteComponent(class Actor* owner, const uint32_t drawOrder = 100);

            void update(const float deltaTime) override;
            void draw(SDL_Renderer* renderer) override;

            auto getScrollSpeed() const { return mScrollSpeed; }

            void setScrollSpeed(const float speed) { mScrollSpeed = speed; }
            void setScreenSize(const Vector2<uint16_t>& size) { mScreenSize = size; }
            void setBGTextures(const std::vector<SDL_Texture*>& textures);

        private:
            struct BGTexture {
                SDL_Texture* mTexture;
                Vector2<float> mOffset;
            };

            std::vector<BGTexture> mBGTextures;
            float mScrollSpeed;
            Vector2<uint16_t> mScreenSize;
    };
}
