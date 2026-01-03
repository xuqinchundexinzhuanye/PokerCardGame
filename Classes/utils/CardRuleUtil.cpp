//#include "utils/CardRuleUtil.h"
//
//int CardRuleUtil::getCardValue(CardFaceType face) {
//    switch (face) {
//    case CFT_ACE: return 1;
//    case CFT_TWO: return 2;
//    case CFT_THREE: return 3;
//    case CFT_FOUR: return 4;
//    case CFT_FIVE: return 5;
//    case CFT_SIX: return 6;
//    case CFT_SEVEN: return 7;
//    case CFT_EIGHT: return 8;
//    case CFT_NINE: return 9;
//    case CFT_TEN: return 10;
//    case CFT_JACK: return 11;
//    case CFT_QUEEN: return 12;
//    case CFT_KING: return 13;
//    default: return 0;
//    }
//}
//
//bool CardRuleUtil::canMatch(const CardModel& cardA, const CardModel& cardB) {
//    int valA = getCardValue(cardA.face);
//    int valB = getCardValue(cardB.face);
//    return abs(valA - valB) == 1; // 核心规则：差值为1
//}