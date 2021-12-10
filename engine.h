#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <memory>
#include <unordered_map>

#include "actor/actor.h"
#include "component/sprite/spriteComponent.h"

namespace Chinar {
    
    class Engine {
        public:
            Engine(const uint16_t width, const uint16_t height, const std::string& title = "The Chinar");

            void initialize();
            void runLoop();
            void shutdown();

            const uint16_t getWidth() const { return mWidth; }
            const uint16_t getHeight() const { return mHeight; }
            const std::string& getTitle() const { return mTitle; }

            SDL_Texture* getTexture(const std::string& fileName);

            void addActor(Actor* actor);
            void removeActor(Actor* actor);

            void addSprite(SpriteComponent* sprite);
            void removeSprite(SpriteComponent* sprite);

        private:
            void processInput();
            void updateEngine();
            void generateOutput();

            SDL_Texture* loadTexture(const std::string& fileName);
            
            void unloadData();

        private:
             const uint16_t mWidth;
             const uint16_t mHeight;
             const std::string mTitle;

             bool mIsRunning;

             uint32_t mTickCount;

             SDL_Window* mWindow;
             SDL_Renderer* mRenderer;

             std::unordered_map<std::string, SDL_Texture*> mTextures;

             bool mUpdatingActors;
             std::vector<std::unique_ptr<Actor>> mActors;
             std::vector<std::unique_ptr<Actor>> mPendingActors;

             std::vector<SpriteComponent*> mSprites;
    };
}
