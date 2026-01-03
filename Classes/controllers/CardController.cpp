#pragma once

#include "models/GameModel.h"
#include "managers/UndoManager.h"
#include "managers/CardManager.h"
#include <vector>

class CardManager;
/**
 * @brief 游戏控制器类（遵循MVC架构的controllers层规范）
 * 该类是游戏流程的核心控制器，负责协调GameModel与GameView/CardView的交互，
 * 1. 处理主牌堆卡牌点击匹配逻辑（selectCardFromPlayefieldAndMatch），验证卡牌是否符合消除规则（）；
 * 2. 管理Stack区卡牌点击事件，通过UndoManager记录操作状态（）；
 * 3. 实现回退功能（undo），基于UndoModel记录的状态逆向恢复卡牌位置和状态（）；
 * 4. 协调视图层更新，如调用CardView动画接口执行卡牌移动（）。
 *
 */
class GameController {
public:
    GameController(GameModel gameModel);
    ~GameController();

    // 选择主牌堆中翻开的纸牌，点击主牌堆中的牌和底牌匹配
    bool selectCardFromPlayefieldAndMatch(CardModel& selectedCard);

    // 点击Stack区的卡牌，记录其状态到UndoModel中
    void clickStackCard(CardModel& card);

    // 处理卡片点击事件
    void handleCardClicked(CardModel& card);

    // 点击回退按钮
    bool undo();

    void GameController::handleLabelClick();
private:
    GameModel _gameModel;
    UndoManager _undoManager;

    // 获取底牌的CardModel
    CardModel getBottomCard();

    // 检查两张牌是否匹配
    bool isCardMatch(const CardModel& card1, const CardModel& card2);

    // 移动卡牌到原位置
    void moveCardToOriginalPosition(const UndoCardState& state);

    // 根据CardModel获取CardManager
    CardManager* getCardManager(const CardModel& card);
};



#include <iostream>
#include "services/CardIdManagerMap.h"


GameController::GameController(GameModel gameModel)
    : _gameModel(gameModel), _undoManager(gameModel.getUndoModel()) {
    CCLOG(u8"undoMode大小为：%d", _undoManager.getUndoSize());
}

GameController::~GameController() {}

bool GameController::selectCardFromPlayefieldAndMatch(CardModel& selectedCard) {
    if (_undoManager.getUndoSize() == 0) {
        return false;
    }
    CardModel bottomCard = getBottomCard();
    CCLOG(u8"playerfield牌堆点击触发");
    if (isCardMatch(selectedCard, bottomCard)) {
        // 记录当前状态
        UndoCardState state;
        state.id = selectedCard._id;
        state.position = selectedCard.getPosition();
        state.zone = selectedCard.getZone();
        _undoManager.recordUndoState(state);
        handleCardClicked(selectedCard);
        return true;
    }
    return false;
}

void GameController::clickStackCard(CardModel& card) {
    UndoCardState state;
    state.id = card._id;
    state.position = card.getPosition();
    state.zone = card.getZone();
    _undoManager.recordUndoState(state);
    CardManager* cardManager = getCardManager(card);
    CCLOG(u8"stack牌堆点击触发");
    handleCardClicked(card);
}

bool GameController::undo() {
    UndoCardState state;
    if (_undoManager.undo(state)) {
        moveCardToOriginalPosition(state);
        return true;
    }
    return false;
}

CardModel GameController::getBottomCard() {
    UndoCardState state;
    CCLOG(u8"undoModel 中数据为%d", _undoManager.getUndoSize());
    if (_undoManager.undo(state)) {
        _undoManager.recordUndoState(state); // 放回记录
        auto& playfield = _gameModel.getPlayfield();
        for (const auto& card : playfield) {
            if (card._id == state.id) {
                return card;
            }
        }
        auto& stackfield = _gameModel.getStackfield();
        for (const auto& card : stackfield) {
            if (card._id == state.id) {
                return card;
            }
        }
    }
    return CardModel(CardFaceType::CFT_ACE, CardSuitType::CST_SPADES, cocos2d::Vec2::ZERO);
}

bool GameController::isCardMatch(const CardModel& card1, const CardModel& card2) {
    int face1 = static_cast<int>(card1.getFace());
    int face2 = static_cast<int>(card2.getFace());
    return (face1 == face2 + 1) || (face1 == face2 - 1);
}

void GameController::moveCardToOriginalPosition(const UndoCardState& state) {
    auto& playfield = _gameModel.getPlayfield();
    auto& stackfield = _gameModel.getStackfield();
    for (auto card : playfield) {
        if (card._id == state.id) {
            CardManager* cardManager = getCardManager(card);
            if (cardManager) {
                auto moveTo = cocos2d::MoveTo::create(0.5f, state.position);
                cardManager->getView()->runAction(moveTo);
                card.setPosition(state.position);
                card.setZone(state.zone);
                cardManager->getView()->setZOrder(0);
            }
            return;
        }
    }
    for (auto card : stackfield) {
        if (card._id == state.id) {
            CardManager* cardManager = getCardManager(card);
            if (cardManager) {
                auto moveTo = cocos2d::MoveTo::create(0.5f, state.position);
                cardManager->getView()->runAction(moveTo);
                card.setPosition(state.position);
                card.setZone(state.zone);
                cardManager->getView()->setZOrder(0);
            }
            return;
        }
    }
}

CardManager* GameController::getCardManager(const CardModel& card) {
    CardManager* manager = CardIdManagerMap::getInstance().getCardManager(card._id);
    return manager;
}



void GameController::handleCardClicked(CardModel& card) {
    CCLOG(u8"卡牌区域为", card.getZone());
    if (card.getZone() != CardZone::Hand) {
        //CCLOG(u8"卡牌区域为", card.getZone());
        cocos2d::Vec2 newPos(700, 400);
        CardManager* cardManager = getCardManager(card);
        card.setZone(CardZone::Hand);
        card.setPosition(newPos);
        if (cardManager) {
            CCLOG(u8"移动卡牌，%d", card._id);
            auto moveTo = cocos2d::MoveTo::create(0.5f, newPos);
            cardManager->getView()->runAction(moveTo);
            if (_undoManager.getUndoSize() != 0) {
                CardModel& lastCard = getBottomCard();
                cardManager->getView()->setLocalZOrder(getCardManager(lastCard)->getView()->getLocalZOrder() + 1);
            }
        }
    }
}

void GameController::handleLabelClick() {
    // 处理 Label 点击逻辑，这里调用撤销操作
    undo();
}