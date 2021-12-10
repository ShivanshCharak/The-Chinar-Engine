#include "bgSpriteComponent.h"
#include "actor/actor.h"

namespace Chinar {
    
    BGSpriteComponent::BGSpriteComponent(Actor* owner, const uint32_t drawOrder)
    : SpriteComponent(owner, drawOrder)
    , mScrollSpeed{0.0f} {}

    void BGSpriteComponent::update(const float deltaTime) {
        for (auto& bg : mBGTextures) {
            bg.mOffset.x += mScrollSpeed * deltaTime;

            if (bg.mOffset.x < -mScreenSize.x) {
                bg.mOffset.x = ( mBGTextures.size() - 1) * mScreenSize.x - 1;
            }
        }
    }

    void BGSpriteComponent::draw(SDL_Renderer* renderer) {
        for (auto& bg : mBGTextures) {
            SDL_Rect r;

            r.w = static_cast<int>(mScreenSize.x);
            r.h = static_cast<int>(mScreenSize.y);
            r.x = static_cast<int>(mOwner->getPosition().x - r.w/2 + bg.mOffset.x);
            r.y = static_cast<int>(mOwner->getPosition().y - r.h/2 + bg.mOffset.y);

            SDL_RenderCopy(renderer,
                    bg.mTexture,
                    nullptr,
                    &r);

        }
    }

    void BGSpriteComponent::setBGTextures(const std::vector<SDL_Texture*>& textures) {
        for (size_t count = 0; auto tex : textures) {
            BGTexture bgTex;
            bgTex.mTexture = tex;

            bgTex.mOffset.x = count * mScreenSize.x;
            bgTex.mOffset.y = 0;
            mBGTextures.emplace_back(bgTex);
            ++count;
        }
    }
}
