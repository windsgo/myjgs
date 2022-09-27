#pragma once

/*

#include "block.h"
#include "type.h"
#include <memory>

class AbstractEvent {
public:

    using ptr = std::shared_ptr<AbstractEvent>;
    AbstractEvent() : _event_type(UnknownEventType) {}
    AbstractEvent(EventType type) : _event_type(type) {}
    static EventType block_eventtype(const JGSEventBlock& block);

    virtual void set_block(const JGSEventBlock& block) = 0; // initialize from block

    inline EventType get_type() const {return _event_type;}
    inline void set_type(EventType type) {_event_type = type;}
    
protected:
    EventType _event_type;

};

class MoveEvent : public AbstractEvent {
public:
    using ptr = std::shared_ptr<MoveEvent>;
    MoveEvent() : AbstractEvent(EventType::MoveEventType) {}

    virtual void set_block(const JGSEventBlock& block) override final;

private:
    bool _has_40_dead = false;
    ItemColor _move_player_color;
    MoveResultType _move_result_type;
    Position _start_position;
    Position _end_position;
    // todo
};

class InfoEvent : public AbstractEvent {
public:
    using ptr = std::shared_ptr<InfoEvent>;
    InfoEvent() : AbstractEvent(EventType::InfoEventType) {}

    virtual void set_block(const JGSEventBlock& block) override final;

private:
};

*/