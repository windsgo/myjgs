#include "item.h"

namespace myjgs {

::std::ostream& operator<<(::std::ostream& os, const Item& item) {
    os << item._type << " " << item._color << " " << item._pos;
    return os;
}

}

