//#pragma once
//#include "cocos2d.h"
//
///**
// * 卡牌数据模型（纯数据）
// */
//
//enum CardSuitType {
//    CST_NONE = -1,
//    CST_CLUBS,
//    CST_DIAMONDS,
//    CST_HEARTS,
//    CST_SPADES,
//};
//
//enum CardFaceType {
//    CFT_NONE = -1,
//    CFT_ACE,
//    CFT_TWO,
//    CFT_THREE,
//    CFT_FOUR,
//    CFT_FIVE,
//    CFT_SIX,
//    CFT_SEVEN,
//    CFT_EIGHT,
//    CFT_NINE,
//    CFT_TEN,
//    CFT_JACK,
//    CFT_QUEEN,
//    CFT_KING,
//};
//
//enum class CardArea {
//    PlayField,    // 主牌堆（桌面）
//    Tray,         // 底牌堆（中间）
//    Stack         // 备用牌堆（左侧）
//};

//class CardModel {
//public:
//    int cardId = -1;
//
//    CardSuitType suit = CST_NONE;
//    CardFaceType face = CFT_NONE;
//
//    cocos2d::Vec2 position;
//
//    CardArea area = CardArea::PlayField;
//
//    int coverCount = 0;   // >0 表示被覆盖
//    bool isRemoved = false;
//    bool isCovered = false;   // 是否被覆盖（主牌堆用）
//};
//class CardModel {
//public:
//    int cardId = -1;
//    CardSuitType suit = CST_NONE;
//    CardFaceType face = CFT_NONE;
//    cocos2d::Vec2 position;
//
//    // 只保留主牌区用的覆盖关系
//    int coverCount = 0;
//
//    CardArea area = CardArea::PlayField;
//};



//class CardModel {
//public:
//    int cardId = -1;
//    CardSuitType suit = CST_NONE;
//    CardFaceType face = CFT_NONE;
//    cocos2d::Vec2 position;
//
//    // 只用于主牌堆的覆盖关系
//    int coverCount = 0;
//
//    CardArea area = CardArea::PlayField;
//};



#pragma once
#include "cocos2d.h"
USING_NS_CC;
enum class CardZone {
    Playfield,  // 主牌区
    Stack,      // 备用牌堆
    Hand,
};

enum class CardSuitType {
    CST_NONE = -1,
    CST_CLUBS,      // 梅花
    CST_DIAMONDS,   // 方块
    CST_HEARTS,     // 红桃
    CST_SPADES,     // 黑桃
    CST_NUM_CARD_SUIT_TYPES
};


enum class CardFaceType {
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};


class CardModel {
public:
    CardModel(CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position) :
        _face(face)
        , _suit(suit)
        , _position(position) {
    }

    CardModel(CardFaceType face, CardSuitType suit, const cocos2d::Vec2& position, int id, CardZone zone) :
        _face(face)
        , _suit(suit)
        , _position(position)
        , _id(id)
        , _zone(zone) {
    }

    CardFaceType getFace() const { return _face; }
    CardSuitType getSuit() const { return _suit; }
    const cocos2d::Vec2& getPosition() const { return _position; }
    const CardZone getZone() const { return _zone; }
    void setZone(CardZone zone) { _zone = zone; }
    void setPosition(Vec2 position) { _position = position; }
    int _id;

private:
    CardFaceType _face{ CardFaceType::CFT_ACE };
    CardSuitType _suit{ CardSuitType::CST_SPADES };

    CardZone _zone;
    cocos2d::Vec2 _position{ cocos2d::Vec2::ZERO };
};
