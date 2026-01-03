//#pragma once
//#include "models/CardModel.h"
//
///**
// * 卡牌规则工具类（无状态）
// */
//class CardRuleUtil {
//public:
//    /**
//     * 判断是否可匹配（点数差 1）
//     */
//    static bool canMatch(const CardModel& a, const CardModel& b) {
//        int da = static_cast<int>(a.face);
//        int db = static_cast<int>(b.face);
//        return abs(da - db) == 1;
//    }
//};


//#pragma once
//#include "models/CardModel.h"
//
//class CardRuleUtil {
//public:
//    // 判断两张牌是否满足差值为1的规则
//    static bool canMatch(const CardModel& cardA, const CardModel& cardB);
//    // 将牌面转换为数值（ACE=1, TWO=2...KING=13）
//    static int getCardValue(CardFaceType face);
//};