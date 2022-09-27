#include "type.h"
#include <unordered_map>
#include <cassert>

using ItemTypeMap = std::unordered_map<ItemType, std::string>;
using ItemColorMap = std::unordered_map<ItemColor, std::string>;
using ItemScoreMap = std::unordered_map<ItemType, ItemScore>;

#ifdef ItemTypeStringShort
static const ItemTypeMap itemtype_map = {
    {ItemType::JQNone,    "○○"},
    {ItemType::Junqi,     "旗"},
    {ItemType::Dilei,     "雷"},
    {ItemType::Zhadan,    "炸"},
    {ItemType::Silin,     "司"},
    {ItemType::Junzhang,  "军"},
    {ItemType::Shizhang,  "师"},
    {ItemType::Lvzhang,   "旅"},
    {ItemType::Tuanzhang, "团"},
    {ItemType::Yinzhang,  "营"},
    {ItemType::Lianzhang, "连"},
    {ItemType::Paizhang,  "排"},
    {ItemType::Gongbing,  "兵"}
};
#else
static const ItemTypeMap itemtype_map = {
    {ItemType::JQNone,    " ○○ "},
    {ItemType::Junqi,     "军旗"},
    {ItemType::Dilei,     "地雷"},
    {ItemType::Zhadan,    "炸弹"},
    {ItemType::Silin,     "司令"},
    {ItemType::Junzhang,  "军长"},
    {ItemType::Shizhang,  "师长"},
    {ItemType::Lvzhang,   "旅长"},
    {ItemType::Tuanzhang, "团长"},
    {ItemType::Yinzhang,  "营长"},
    {ItemType::Lianzhang, "连长"},
    {ItemType::Paizhang,  "排长"},
    {ItemType::Gongbing,  "工兵"}
};
#endif

static const ItemColorMap itemcolor_map = {
    {ItemColor::YELLOW,   "黄色"},
    {ItemColor::BLUE,     "蓝色"},
    {ItemColor::GREEN,    "绿色"},
    {ItemColor::PURPLE,   "紫色"},
};

static ItemScoreMap itemscore_map = {
    {ItemType::JQNone,    0},
    {ItemType::Junqi,     0},
    {ItemType::Dilei,     15},
    {ItemType::Zhadan,    100},
    {ItemType::Silin,     220},
    {ItemType::Junzhang,  180},
    {ItemType::Shizhang,  120},
    {ItemType::Lvzhang,   80},
    {ItemType::Tuanzhang, 40},
    {ItemType::Yinzhang,  20},
    {ItemType::Lianzhang, 10},
    {ItemType::Paizhang,  5},
    {ItemType::Gongbing,  30}
};

std::string item_type2string(const ItemType& item_type) {
    return itemtype_map.at(item_type);
}

std::string item_type2string(uint8_t item_type) {
    return item_type2string(static_cast<ItemType>(item_type));
}

std::string itemcolor_type2string(const ItemColor& item_color) {
    return itemcolor_map.at(item_color);
}

ItemScore item_score(const ItemType& item_type) {
    return itemscore_map.at(item_type);
}

void set_item_score(const ItemType& item_type, const ItemScore& score) {
    itemscore_map.at(item_type) = score;
}

std::ostream& operator<<(std::ostream& os, const ItemType& item_type) {
    os << item_type2string(item_type);
    return os;
}

std::ostream& operator<<(std::ostream& os, const ItemColor& item_color) {
    os << itemcolor_type2string(item_color);
    return os;
}

static const Position NonePosition = {0, 0};

std::ostream &operator<<(std::ostream &os, const Position& pos) {
    char buf[50];
    sprintf(buf, "Pos(row:%2x, col:%2x)", pos.row, pos.col);
    os << buf;
    return os;
}

std::string event_type2string(const EventType& event_type) {
    switch (event_type)
    {
    case EventType::MoveEventType:
        return "动作命令";
        break;
    
    case EventType::InfoEventType:
        return "通知命令";
        break;

    default:
        return "未知命令";
        break;
    }
}

static const std::array<std::string, 4> moveresult_arr = {
    "移动", "吃子", "反弹", "交换"
};

std::string event_moveresult2string(const MoveResultType &move_result) {
    return moveresult_arr.at(static_cast<uint8_t>(move_result));
}

std::ostream &operator<<(std::ostream &os, const EventType &event_type) {
    os << event_type2string(event_type);
    return os;
}

std::ostream &operator<<(std::ostream &os, const MoveResultType &move_result) {
    if ((int)move_result < 4)
        os << event_moveresult2string(move_result);
    
    assert(move_result < 4);
    return os;
}