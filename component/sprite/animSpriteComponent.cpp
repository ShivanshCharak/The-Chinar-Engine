#include "animSpriteComponent.h"

namespace Chinar {
    
    AnimSpriteComponent::AnimSpriteComponent(Actor* owner, const uint32_t drawOrder)
    : SpriteComponent(owner, drawOrder)
    , mAnimFPS{24.0f}
    , mCurrentFrame{0.0f} {}

    void AnimSpriteComponent::update(const float deltaTime) {
        SpriteComponent::update(deltaTime);
        if (!mAnimTextures.empty()) {
            mCurrentFrame += mAnimFPS * deltaTime;

            while (mCurrentFrame >= mAnimTextures.size()) {
                mCurrentFrame -= mAnimTextures.size();
            }

            setTexture(mAnimTextures[static_cast<int>(mCurrentFrame)]);
        }
    }

    void AnimSpriteComponent::setAnimTextures(const std::vector<SDL_Texture*>& textures) {
        
        mAnimTextures = textures;
        if (!mAnimTextures.empty()) {
            mCurrentFrame = 0.0f;
            setTexture(mAnimTextures[0]);
        }
    }
}
