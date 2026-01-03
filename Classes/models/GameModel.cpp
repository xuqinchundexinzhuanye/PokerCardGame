//#pragma once
//#include "models/CardModel.h"
//#include "models/GameModel.h"
//
//CardModel* GameModel::getCardById(int cardId) {
//    for (auto& c : playFieldCards)
//        if (c.cardId == cardId) return &c;
//
//    for (auto& c : stackCards)
//        if (c.cardId == cardId) return &c;
//
//    if (trayCard.cardId == cardId)
//        return &trayCard;
//
//    return nullptr;
//}
//
//void GameModel::uncoverBelow(const CardModel& removedCard) {
//    for (auto& card : playFieldCards) {
//        if (!card.isRemoved && card.coverCount > 0) {
//            card.coverCount--;
//        }
//    }
//}
//
//void GameModel::restoreCover(const CardModel& restoredCard) {
//    for (auto& card : playFieldCards) {
//        if (!card.isRemoved) {
//            card.coverCount++;
//        }
//    }
//}


//#include "models/GameModel.h"
//
///**
// * 通过 cardId 查找卡牌
// * 注意：Tray 本身不存卡牌实体，只指向已有牌
// */
//CardModel* GameModel::getCardById(int cardId) {
//    if (cardId == -1) return nullptr;
//
//    for (auto& c : playFieldCards) {
//        if (c.cardId == cardId) return &c;
//    }
//
//    for (auto& c : stackCards) {
//        if (c.cardId == cardId) return &c;
//    }
//
//    return nullptr;
//}
//
///**
// * 从主牌区移除一张牌（逻辑移除）
// */
//void GameModel::removePlayFieldCard(int cardId) {
//    for (auto it = playFieldCards.begin(); it != playFieldCards.end(); ++it) {
//        if (it->cardId == cardId) {
//            playFieldCards.erase(it);
//            return;
//        }
//    }
//}
//
///**
// * 主牌被移除后，解锁其正下方的牌
// * 优化：只处理同位置下方的牌（根据坐标判断）
// */
//void GameModel::uncoverBelow(const CardModel& removedCard) {
//    for (auto& card : playFieldCards) {
//        // 简化判断：同列（x 坐标接近）且 y 坐标更小（在下方）
//        if (abs(card.position.x - removedCard.position.x) < 10
//            && card.position.y < removedCard.position.y
//            && card.coverCount > 0) {
//            card.coverCount--;
//        }
//    }
//}
//
///**
// * Undo 时，恢复覆盖关系
// * 优化：只恢复被回退牌正下方的牌
// */
//void GameModel::restoreCover(const CardModel& restoredCard) {
//    for (auto& card : playFieldCards) {
//        if (abs(card.position.x - restoredCard.position.x) < 10
//            && card.position.y < restoredCard.position.y) {
//            card.coverCount++;
//        }
//    }
//}
//
