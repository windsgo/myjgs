#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>
#include <memory>
#include <ostream>

#include "type.h"

class Item 
{
public:
    using ptr = std::shared_ptr<Item>;
    Item() {}
    Item(const ItemType &type) : _type(type) {}
    Item(const Item &) = default;
    Item &operator=(const Item &) = default;

    

    ItemType get_type() const { return _type; }
    void set_type(const ItemType &type) { _type = type; }

protected:
    ItemType _type = ItemType::JQNone;
};

std::ostream &operator<<(std::ostream &os, const Item &item);

