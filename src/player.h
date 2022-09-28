#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <map>
#include <cstring>

#include "type.h"
#include "item.h"
#include "block.h"

class Player {
public:
    using ptr = std::shared_ptr<Player>;
    Player() = default;
    Player(const JGSPLayerInfoBlock& player_info);

    void remove_item(const Position& pos);
    void remove_item(Item::ptr item_ptr);

    inline void move_item(const Position& start_pos, const Position& end_pos) {
        _pos_item_map.at(start_pos)->move_to(end_pos);
    }

    Item::ptr get_item(const Position& pos) {return _pos_item_map.at(pos);}

    int get_current_score() const;

private:
    char _name[20];
    uint32_t _qq;
    PlayerColor _color;
    JGSLayoutBlock _init_layout;

    std::unordered_map<Position, Item::ptr> _pos_item_map;

};