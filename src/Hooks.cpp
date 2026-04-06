#include <Geode/modify/PlayLayer.hpp>
#include "AIController.hpp"

using namespace geode::prelude;

struct SeraphimPlayLayer : geode::Modify<SeraphimPlayLayer, PlayLayer> {

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects))
            return false;

        AIController::get()->setPlayLayer(this);
        AIController::get()->reset();
        log::info("[SeraphimAI] Level loaded. AI is ready.");
        return true;
    }

    void update(float dt) {
        PlayLayer::update(dt);
        AIController::get()->onUpdate(dt);
    }

    void resetLevel() {
        PlayLayer::resetLevel();
        AIController::get()->reset();
        log::info("[SeraphimAI] Attempt reset. AI memory cleared.");
    }

    void onQuit() {
        PlayLayer::onQuit();
        AIController::get()->setPlayLayer(nullptr);
        log::info("[SeraphimAI] Level exited. AI deactivated.");
    }
};
