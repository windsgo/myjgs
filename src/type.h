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

std::string item_type2string(const ItemType& item_type);
std::string item_type2string(uint8_t item_type);
std::string itemcolor_type2string(const ItemColor& item_color);
ItemScore item_score(const ItemType& item_type);
void set_item_score(const ItemType& item_type, const ItemScore& score); // update settings

std::ostream& operator<<(std::ostream& os, const ItemType& item_type);
std::ostream& operator<<(std::ostream& os, const ItemColor& item_color);