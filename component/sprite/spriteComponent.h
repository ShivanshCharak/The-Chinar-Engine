#pragma once

#include "component/component.h"
#include <SDL2/SDL.h>

namespace Chinar {
    
    class SpriteComponent : public Component {
        public:
            SpriteComponent(class Actor* owner, const uint32_t drawOrder = 100);

            const auto getDrawOrder() const { return mDrawOrder; }

            virtual void draw(SDL_Renderer* renderer);

            void setTexture(SDL_Texture* texture);

            auto getTextureWidth() const { return mTextureWidth; }
            auto getTextureHeight() const { return mTextureHeight; }

        private:
            const uint32_t mDrawOrder;

            SDL_Texture* mTexture;

            int mTextureWidth;
            int mTextureHeight;
    };
}
