#pragma once

#include <cstdint>
#include <string>
#include <memory>
#include <ostream>

#include "type.h"

namespace myjgs {
class Item
{
    friend ::std::ostream &operator<<(::std::ostream &os, const myjgs::Item &item);

public:
    // using ptr = ::std::shared_ptr<Item>;
    // Item() = default;
    Item(const ItemType &type, const ItemColor &color, const Position &pos)
        : _type(type), _color(color), _pos(pos) {}
    
    Item(const Item& rhs) : _type(rhs._type), _color(rhs._color), _pos(rhs._pos) {}

    ItemType get_type() const { return _type; }
    void set_type(const ItemType &type) { _type = type; }

    ItemColor get_color() const { return _color; }
    void set_color(const ItemColor &color) { _color = color; }

    Position get_pos() const { return _pos; }
    void set_pos(const Position &pos) { _pos = pos; }
    inline void move_to(const Position& to_pos) { set_pos(to_pos); } // the same as set_pos

private:
    ItemType _type = ItemType::JQNone;
    ItemColor _color;
    Position _pos;
};

::std::ostream &operator<<(::std::ostream &os, const Item &item);

}
