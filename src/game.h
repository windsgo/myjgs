#pragma once

#include <string>
#include <memory>
#include <list>
#include <fstream>
#include <exception>
#include <iostream>
#include <ostream>

#include "player.h"
#include "block.h"

namespace myjgs {

class Game {
    friend ::std::ostream& operator<<(::std::ostream& os, const Game& game);
    
public:
    using ptr = ::std::shared_ptr<Game>;
    Game(const ::std::string& jgs_file_name);
    
    // at present, do not support go back steps
    // so process all events
    void process_all_events();

    // get player
    inline const Player& get_player(PlayerColor color) const {return _color_player_map.at(color);}

private:
    void _init();
    void _process_event(const JGSEventBlock&);

    // ignore color: color will not search in this function
    PlayerColor _which_player(const Position& pos, PlayerColor ignore_color = PlayerColor::UNKNOWN_COLOR) const;

    void _print() const;

private:
    ::std::string _jgs_file_name;
    ::std::list<JGSEventBlock> _event_list;
    ::std::list<JGSEventBlock>::iterator _cur_event_iterator; // not used

    ::std::unordered_map<ItemColor, Player> _saved_init_color_player_map; // not used, a deep copy
    ::std::unordered_map<ItemColor, Player> _color_player_map;

    uint16_t _total_steps;
    PlayerColor _self_color;
};

::std::ostream& operator<<(::std::ostream& os, const Game& game);

}
