#pragma once

#include <cstdint>
#include <ostream>
#include <array>
#include <cassert>

#include "type.h"

#define _sizeof_type(T) (size_t)((T*)0 + 1)   //适用于类型

using _ItemColor = ItemColor;
using _ItemType = ItemType;

// 0x00 ~ 0x1F
struct __attribute__ ((__packed__)) JGSHeaderBlock {
    // 0x00 ~ 0x0F
    char discription[0x0B];         // 0x00 ~ 0x0A
    char _n1[0x04];                 // 0x0B ~ 0x0E
    _ItemColor self_color;           // 0x0F, 00:yellow, 01:blue, 02:green, 03:purple

    // 0x10 ~ 0x1F
    char _n2[0x0A];                 // 0x10 ~ 0x19
    uint16_t all_steps;             // 0x1A ~ 0x1B
    char _n3[0x04];                 // 0x1C ~ 0x1F
};

// layout of player, 30 bytes, 5 * 6(6 lines, 5 item each line)
class __attribute__ ((__packed__)) JGSLayoutBlock {
public:
    static constexpr int row_num = 6;
    static constexpr int col_num = 5;

    _ItemType item(int row, int col) const {
        assert(row >= 0 && row < row_num);
        assert(col >= 0 && col < col_num);
        return _items[row][col];
    }
private:
    _ItemType _items[row_num][col_num];
};

// 0x020 ~ 0x17F, 4 * (11 * 8) bytes, each 88 bytes
struct __attribute__ ((__packed__)) JGSPLayerInfoBlock {
    // 0x20 ~ 0x2F
    _ItemColor player_color;         // 0x20, 00:yellow, 01:blue, 02:green, 03:purple
    char _n1[0x07];                 // 0x21 ~ 0x27
    char player_name[20];           // 0x28 ~ 0x3B, name at most 19 bytes, end with a 1-byte '\0'
    JGSLayoutBlock player_layout;    // 0x3C ~ 0x59, layout 30 bytes
    char _reserve[2];               // 0x5A ~ 0x5B, 2 bytes 0, reserved
    uint32_t player_qqnumber;       // 0x5C ~ 0x5F, qq number, if unknown, it is 0, little endian
    char _n2[24];                   // 0x5A ~ 0x77, 24 bytes unknown
};

// 10 bytes
struct __attribute__ ((__packed__)) JGSEventBlock {
    // char event_type;                // 0x5F: move, 0xF5, info
    char byte[10];
};

// jgs file info block, exclude event blocks, which is of dynamic size
// 0x000 ~ 0x19b
struct __attribute__ ((__packed__)) JGSTotalInfoBlock {
    JGSHeaderBlock header_block;
    JGSPLayerInfoBlock player_0_info_block;
    JGSPLayerInfoBlock player_1_info_block;
    JGSPLayerInfoBlock player_2_info_block;
    JGSPLayerInfoBlock player_3_info_block;
    char _n[28]; // 0x180 ~ 0x19B
};

// jgs end with 8-byte 0
struct __attribute__ ((__packed__)) JGSFileTailBlock {
    char tail[8];
};

std::ostream& operator<<(std::ostream& os, const JGSLayoutBlock& jgs_layout);
std::ostream& operator<<(std::ostream& os, const JGSHeaderBlock& jgs_header);