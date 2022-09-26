#include "item.h"

std::ostream& operator<<(std::ostream& os, const Item& item) {
    os << item.get_type();
    return os;
}

