#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <unordered_map>
#include <map>
#include <iostream>
#include <cstring>

#include "type.h"
#include "item.h"
#include "block.h"

namespace myjgs {

class Player {
public:
    using ptr = ::std::shared_ptr<Player>;
    Player() = default;
    Player(const JGSPLayerInfoBlock& player_info);

    Player(const Player& rhs) : _qq(rhs._qq), _color(rhs._color), _init_layout(rhs._init_layout) {
        memcpy(_name, rhs._name, 20);

        _pos_item_map.reserve(rhs._pos_item_map.size());
        for (const auto& [key, value] : rhs._pos_item_map) {
            // copy the item
            Item::ptr item_copy = ::std::make_shared<Item>(*value); // copy constructor

            // insert
            _pos_item_map.insert(::std::make_pair(key, item_copy));
        }
    }

    Player& operator=(const Player&) = delete;

    PlayerColor color() const {return _color;}

    void remove_item(const Position& pos);
    void remove_item(Item::ptr item_ptr);

    inline void clear() {
        _pos_item_map.clear();
    }

    inline void move_item(const Position& start_pos, const Position& end_pos) {
        _pos_item_map.insert(::std::make_pair(end_pos, _pos_item_map.at(start_pos)));
        _pos_item_map.at(start_pos)->move_to(end_pos);
        _pos_item_map.erase(start_pos);
        // update map after move!!!
        // todo
    }

    Item::ptr get_item(const Position& pos) {return _pos_item_map.at(pos);}

    bool has_item(const Position& pos) const;

    int get_current_score() const;

    inline uint32_t qq() const {return _qq;}
    inline const char* name() const {return _name;}

private:
    char _name[20];
    uint32_t _qq;
    PlayerColor _color;
    JGSLayoutBlock _init_layout;

    ::std::unordered_map<Position, Item::ptr> _pos_item_map;

};

}