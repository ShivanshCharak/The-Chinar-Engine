#include "engine.h"
#include "exception/exception.h"

#include <iostream>
#include <SDL2/SDL_image.h>

namespace Chinar {
    
    Engine::Engine(const uint16_t width, const uint16_t height, const std::string& title)
    : mWidth{width}
    , mHeight{height}
    , mTitle{title}
    , mIsRunning{true}
    , mWindow{nullptr}
    , mRenderer{nullptr}
    , mUpdatingActors{false} {}

    void Engine::initialize() {
        
        const auto failed = SDL_Init(SDL_INIT_VIDEO);

        if (failed) {
            throw EngineException("Engine::initialize", "Failed to initialize SDL:", SDL_GetError());
        }

        mWindow = SDL_CreateWindow(mTitle.c_str(),
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                mWidth, mHeight,
                0);

        if (mWindow == nullptr) {
            throw EngineException("Engine::initialize", "Failed to create window:", SDL_GetError());
        }

        mRenderer = SDL_CreateRenderer(mWindow, -1,
                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        if (mRenderer == nullptr) {
            throw EngineException("Engine::initialize", "Failed to create renderer:", SDL_GetError());
        }

        if (!IMG_Init(IMG_INIT_PNG)) {
            throw EngineException("Engine::initialize", "Failed to initialize SDL_IMG:", IMG_GetError());
        }

        mTickCount = SDL_GetTicks();
    }

    void Engine::runLoop() {
        while (mIsRunning) {
            processInput();
            updateEngine();
            generateOutput();
        }
    }

    void Engine::shutdown() {
        unloadData();
        IMG_Quit();
        SDL_DestroyRenderer(mRenderer);
        SDL_DestroyWindow(mWindow);
        SDL_Quit();
    }

    void Engine::unloadData() {
        for (auto [str, tex] : mTextures) {
            SDL_DestroyTexture(tex);
        }
    }

    void Engine::processInput() {

        SDL_Event event;

        if (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                    mIsRunning = false;
                    break;
                }
            }
        }

        const auto keyState = SDL_GetKeyboardState(NULL);

        mUpdatingActors = true;
        for (auto& actor : mActors) {
            actor->processInput(keyState);
        }
        mUpdatingActors = false;
    }

    void Engine::updateEngine() {

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));

        auto deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
        if (deltaTime > 1.5f) {
            deltaTime = 1.5f;
        }

        mTickCount = SDL_GetTicks();

        mUpdatingActors = true;
        for (auto& actor : mActors) {
            actor->update(deltaTime);
        }
        mUpdatingActors = false;

        for (auto& actor : mPendingActors) {
            mActors.emplace_back(std::move(actor));
        }
        mPendingActors.clear();

        std::vector<std::unique_ptr<Actor>> deadActors;
        for (auto& actor : mActors) {
            if (actor->getState() == Actor::EDead) {
                deadActors.emplace_back(std::move(actor));
            }
        }
    }

    void Engine::generateOutput() {
        SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
        SDL_RenderClear(mRenderer);

        for (auto& sprite : mSprites) {
            sprite->draw(mRenderer);
        }

        SDL_RenderPresent(mRenderer);
    }

    SDL_Texture* Engine::getTexture(const std::string& fileName) {
        SDL_Texture* texture = nullptr;
        const auto iter = mTextures.find(fileName);
        if (iter != mTextures.end()) {
            texture = iter->second;
        } else {
            texture = loadTexture(fileName);
            mTextures[fileName] = texture;
        }
        return texture;
    }

    SDL_Texture* Engine::loadTexture(const std::string& fileName) {
        SDL_Surface* surface = IMG_Load(fileName.c_str());
        if (!surface) {
            throw EngineException("Engine::loadTexture", "Failed to load Texture:", IMG_GetError());  
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(mRenderer, surface);
        SDL_FreeSurface(surface);

        if (!texture) {
            throw EngineException("Engine::loadTexture", "Failed to create texture from surface:", SDL_GetError());
        }

        return texture;
    }

    void Engine::addActor(Actor* actor) {
        if (mUpdatingActors) {
            mPendingActors.emplace_back(actor);
        } else {
            mActors.emplace_back(actor);
        }
    }

    void Engine::removeActor(Actor* actor) {
        auto removeFrom = [&](std::vector<std::unique_ptr<Actor>>& actors) {

            auto iter = std::find_if(actors.begin(), actors.end(), [&](const std::unique_ptr<Actor>& a) { return a.get() == actor; } );

            if (iter != actors.end()) {
                std::iter_swap(iter, actors.end() - 1);
                actors.pop_back();
            }
        };
        removeFrom(mActors);
        removeFrom(mPendingActors);
    }

    void Engine::addSprite(SpriteComponent* sprite) {
        const auto order = sprite->getDrawOrder();
        auto iter = mSprites.begin();
        for (; iter != mSprites.end(); iter++) {
            if (order < (*iter)->getUpdateOrder()) {
                break;
            }
        }
        mSprites.insert(iter, sprite);
    }

    void Engine::removeSprite(SpriteComponent* sprite) {
        auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
        if (iter != mSprites.end()) {
            mSprites.insert(iter, sprite);
        }
    }
}
