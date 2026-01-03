#pragma once

#include "models/GameModel.h"
#include "views/GameView.h"
#include "configs/models/LevelConfig.h"
#include "configs/loaders/LevelConfigLoader.h"
#include <vector>

USING_NS_CC;

class GameModelFromLevelGenerator {
public:
    static GameModel generateGameModel(const std::string levelFile) {
        auto config = LevelConfigLoader::loadLevelConfig("level_one.json");
        GameModel gameModel(config);
        return gameModel;
    }

    static void generateGameView(GameModel& gameModel, Node* parent) {
        auto gameView = GameView::create(gameModel);
        if (gameView) {
            parent->addChild(gameView, 1);
        }
    }
private:
    GameModelFromLevelGenerator() = default;
};

