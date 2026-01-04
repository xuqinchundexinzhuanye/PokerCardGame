#pragma once

#include "cocos2d.h"
#include "models/GameModel.h"
#include "CardView.h"
#include <vector>
#include "managers/UndoManager.h"
#include "managers/CardManager.h"


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


USING_NS_CC;
/**
 * @brief 游戏主视图类（遵循MVC架构的views层规范）
 *
 * @职责：
 * 1. 基于GameModel数据渲染游戏主界面，包括主牌区（playfield）和备用牌堆（stackfield）；
 * 2. 管理所有CardView实例的生命周期，根据模型数据动态生成或销毁卡牌视图；
 * 3. 处理全局触摸事件和UI交互（如状态标签点击），并通过回调通知控制器；
 * 4. 提供游戏状态的可视化展示（如_statusLabel显示当前游戏状态）。
 *
 * @渲染结构：
 * - _playfieldCardViews：主牌区卡牌视图集合，对应GameModel中的_playfield；
 * - _stackfieldCardViews：备用牌堆卡牌视图集合，对应GameModel中的_stackfield；
 * - _statusLabel：游戏状态文本标签，这里是回退标签。
 *
 */
class GameView : public Node {
public:
    /**
     * @brief 静态创建 GameView 的方法
     * @param model GameModel 对象，用于初始化 GameView
     */
    static GameView* create(GameModel& model);

protected:
    /**
     * @brief 初始化 GameView 的逻辑
     * @param model GameModel 对象，用于初始化 GameView
     * @return 初始化成功返回 true，否则返回 false
     */
    bool init(GameModel& model);

    /**
     * @brief 根据 GameModel 生成对应的 CardView 数组
     * @param model GameModel 对象，包含卡片信息
     */
    void generateCardViews(GameModel& model);

private:
    std::vector<CardView*> _playfieldCardViews; // 存储 playfield 对应的 CardView 数组
    std::vector<CardView*> _stackfieldCardViews; // 存储 stackfield 对应的 CardView 数组

    // Label 成员变量
    cocos2d::Label* _statusLabel;


    // GameController 成员变量
    GameController* _gameController;
    // 处理 Label 点击的回调函数
    void onLabelClicked();

    // 注册触摸事件
    void registerTouchEvents();
};
