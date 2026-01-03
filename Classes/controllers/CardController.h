//#pragma once
//
//#include "models/GameModel.h"
//#include "views/GameView.h"
//#include "managers/UndoManager.h"
//
//class CardController {
//public:
//    CardController(GameModel* model, GameView* view, UndoManager* undo);
//
//    void onCardClicked(int cardId);
//    void tryMatchPlayField(CardModel& playCard);
//    void drawFromStack();
//    void undo();
//
//private:
//    void matchPlayFieldCard(CardModel& playCard);
//
//private:
//    GameModel* _gameModel;
//    GameView* _view;
//    UndoManager* _undo;
//};

//#pragma once
//
//#include "models/GameModel.h"
//#include "views/GameView.h"
//#include "managers/UndoManager.h"
//
///**
// * 卡牌控制器
// * 只负责三件事：
// * - 主牌 → 底牌 消除
// * - 备用牌 → 底牌 抽牌
// * - Undo 回退
// */
//class CardController {
//public:
//    CardController(GameModel* model, GameView* view, UndoManager* undo);
//
//    // 主牌点击
//    void onCardClicked(int cardId);
//
//    // 从备用牌堆抽牌
//    void drawFromStack();
//
//    // 回退
//    void undo();
//
//private:
//    // 主牌 → 底牌 匹配逻辑
//    void matchPlayFieldCard(CardModel& playCard);
//
//private:
//    GameModel* _gameModel = nullptr;
//    GameView* _view = nullptr;
//    UndoManager* _undo = nullptr;
//};


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
