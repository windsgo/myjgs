#include "event.h"

/*

#include <cassert>
#include <cstring>

static EventType block_eventtypetype(const JGSEventBlock& block) {
    return static_cast<EventType>(block.byte[0]);
}

void MoveEvent::set_block(const JGSEventBlock& block) {
    assert(static_cast<EventType>(block.byte[0]) == EventType::MoveEventType);
    _has_40_dead = !!(block.byte[1] & 0b01000000);

    _move_player_color = static_cast<ItemColor>((~block.byte[1] & 0b00011000) >> 3);

    _move_result_type = static_cast<MoveResultType>(block.byte[1] & 0b00000011);

    memcpy(&_start_position, block.byte + 2, sizeof(_start_position));  // 3,4 byte
    memcpy(&_end_position, block.byte + 4, sizeof(_end_position));      // 5,6 byte

    // todo
}

void InfoEvent::set_block(const JGSEventBlock& block) {
    assert(static_cast<EventType>(block.byte[0]) == EventType::InfoEventType);
}

*/