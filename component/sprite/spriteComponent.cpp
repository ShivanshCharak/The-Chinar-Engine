#include "spriteComponent.h"
#include "actor/actor.h"
#include "engine.h"
#include "util/math.h"

namespace Chinar {
    
    SpriteComponent::SpriteComponent(Actor* owner, const uint32_t drawOrder)
    : Component(owner)
    , mDrawOrder{drawOrder}
    , mTexture{nullptr} {
        mOwner->getEngine()->addSprite(this);
    }

    void SpriteComponent::draw(SDL_Renderer* renderer) {
        if (mTexture) {
            SDL_Rect r;

            r.w = static_cast<int>(mTextureWidth * mOwner->getScale());
            r.h = static_cast<int>(mTextureHeight * mOwner->getScale());
            r.x = static_cast<int>(mOwner->getPosition().x - r.w/2);
            r.y = static_cast<int>(mOwner->getPosition().y - r.h/2);

            SDL_RenderCopyEx(renderer,
                    mTexture,
                    nullptr,
                    &r,
                    -Math::toDegree(mOwner->getRotation()),
                    nullptr,
                    SDL_FLIP_NONE);

        }
    }

    void SpriteComponent::setTexture(SDL_Texture* texture) {
        mTexture = texture;
        SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
    }
}
