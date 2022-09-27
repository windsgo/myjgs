#pragma once

#include <string>
#include <ostream>
#include <cstdint>

#define ItemTypeStringShort

// explicitly size to 1 byte
enum ItemType : uint8_t
{
    JQNone = 0x00,
    Junqi = 0x02,
    Dilei = 0x03,
    Zhadan = 0x04,
    Silin = 0x05,
    Junzhang = 0x06,
    Shizhang = 0x07,
    Lvzhang = 0x08,
    Tuanzhang = 0x09,
    Yinzhang = 0x0A,
    Lianzhang = 0x0B,
    Paizhang = 0x0C,
    Gongbing = 0x0D
};

// explicitly size to 1 byte
enum ItemColor : uint8_t
{
    YELLOW = 0,
    BLUE = 1,
    GREEN = 2,
    PURPLE = 3
};

using ItemScore = uint32_t;

typedef ItemColor PlayerColor;

std::string item_type2string(const ItemType &item_type);
std::string item_type2string(uint8_t item_type);
std::string itemcolor_type2string(const ItemColor &item_color);
ItemScore item_score(const ItemType &item_type);
void set_item_score(const ItemType &item_type, const ItemScore &score); // update settings

std::ostream &operator<<(std::ostream &os, const ItemType &item_type);
std::ostream &operator<<(std::ostream &os, const ItemColor &item_color);

using Axis = uint8_t;
struct __attribute__((__packed__)) Position
{
    static constexpr Axis max_axis = 0x10;
    static const Position NonePosition;
    Axis row;
    Axis col;
    bool operator==(const Position& rhs) const {return (row == rhs.row && col == rhs.col);}
    bool is_none() const {return (*this == NonePosition);}
};

std::ostream &operator<<(std::ostream &os, const Position& pos);

enum EventType : uint8_t
{
    UnknownEventType,
    MoveEventType = 0x5f,
    InfoEventType = 0xf5
};

enum MoveResultType : uint8_t
{
    ResultMove = 0,    // 移动
    ResultEat = 1,     // 吃子
    ResultRebound = 2, // 反弹
    ResultSwap = 3     // 交换，打对
};

std::string event_type2string(const EventType& event_type);
std::string event_moveresult2string(const MoveResultType &move_result);

std::ostream &operator<<(std::ostream &os, const EventType &event_type);
std::ostream &operator<<(std::ostream &os, const MoveResultType &move_result);

/**
 * Position Value Define
 *              Green                   0x00
 *                                      0x01
 *                                        :
 *  Blue                    Purple        :
 *                                        :
 *                                        :
 *              Yellow                  0x10
 * 0x10 ···  ···           ··· 0x01 0x00
 */