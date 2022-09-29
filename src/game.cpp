#include "game.h"

namespace myjgs {

Game::Game(const ::std::string &jgs_file_name)
    : _jgs_file_name(jgs_file_name)
{
    _init();
}

void Game::_init()
{
    ::std::ifstream ifs(_jgs_file_name, std::ios::binary);
    if (!ifs.is_open())
    {
        throw GameException("open file error");
    }

    // read header
    JGSTotalInfoBlock total_info;
    ifs.read(reinterpret_cast<char *>(&total_info), sizeof(total_info));
    if (ifs.bad())
    {
        throw GameException("read file error 1");
    }

    if (memcmp(total_info.header_block.discription, "QQGame JQS", 10) != 0)
    {
        throw GameException("file discription not matched");
    }

    _self_color = total_info.header_block.self_color;
    _total_steps = total_info.header_block.all_steps;

    for (int i = 0; i < 4; ++i)
    {
        Player::ptr player = ::std::make_shared<Player>(total_info.player_info_block[i]);
        Player::ptr saved_player = ::std::make_shared<Player>(*player); // not used, deep copy

        _color_player_map.insert(::std::make_pair(player->color(), player));
    }

    // read events
    for (int i = 0; i < _total_steps; ++i)
    {
        JGSEventBlock ev;
        ifs.read(reinterpret_cast<char *>(&ev), sizeof(ev));
        if (ifs.bad())
        {
            throw GameException("read events failed on: " + ::std::to_string(i));
        }

        _event_list.push_back(ev); // ev has no move constructor, copy and pushback here
    }

    ifs.close();

    // for (_cur_event_iterator = _event_list.begin();
    //      _cur_event_iterator != _event_list.end();
    //      ++_cur_event_iterator)
    // {
    //     std::cout << _cur_event_iterator->event_type() << std::endl;
    // }
}

void Game::process_all_events()
{
    // int i = 0;
    for (const auto &ev : _event_list)
    {
        // std::cout << i++ << "\n";
        // _print();
        _process_event(ev);
    }
    // _print();
}

void Game::_process_event(const JGSEventBlock &ev)
{
    // std::cout << ev.event_type() << std::endl;
    switch (ev.event_type())
    {
    case EventType::InfoEventType:
        // info event
        if (ev.info_result() == InfoResultType::InfoPlayerDead) {
            // std::cout << "dead:" << ev.info_dead_player_color() << std::endl;
            _color_player_map.at(ev.info_dead_player_color())->clear();
        } else if (ev.info_result() == InfoResultType::InfoGameOver) {
            // game over
            return;
        }
        break; // next event

    // case EventType::UnknownEventType:
    //     ::std::cerr << ev.event_type() << ::std::endl;
    //     throw GameException("meet an unknown event");
    //     break;

    case EventType::MoveEventType:
    {
        // auto cur_move_color = ev.move_color(); 
        auto cur_move_color = _which_player(ev.move_start_pos());
        auto cur_player = _color_player_map.at(cur_move_color);
        // std::cout << "move:" << cur_move_color << std::endl;
        // std::cout << ev << std::endl;

        // each result
        // std::cout << ev.move_result() << std::endl;
        switch (ev.move_result())
        {
        case MoveResultType::ResultMove:
        {
            cur_player->move_item(ev.move_start_pos(), ev.move_end_pos());
            
            break;
        }

        case MoveResultType::ResultRebound:
        {
            cur_player->remove_item(ev.move_start_pos());
            break;
        }

        case MoveResultType::ResultSwap:
        {
            cur_player->remove_item(ev.move_start_pos());
            auto target_color = _which_player(ev.move_end_pos(), cur_move_color);
            if (target_color == PlayerColor::UNKNOWN_COLOR) {
                throw GameException("Unknown Target Pos: ResultSwap");
            }

            _color_player_map.at(target_color)->remove_item(ev.move_end_pos());
            break;
        }

        case MoveResultType::ResultEat:
        {
            cur_player->move_item(ev.move_start_pos(), ev.move_end_pos());
            auto target_color = _which_player(ev.move_end_pos(), cur_move_color);
            // std::cout << _color_player_map.at(BLUE)->has_item(ev.move_end_pos()) << _color_player_map.at(YELLOW)->has_item(ev.move_end_pos()) << std::endl;
            // std::cout << "eaten:" << target_color << std::endl;
            if (target_color == PlayerColor::UNKNOWN_COLOR) {
                throw GameException("Unknown Target Pos: ResultSwap");
            }

            _color_player_map.at(target_color)->remove_item(ev.move_end_pos());
            break;
        }

        default:
            ::std::cerr << ev.event_type() << ::std::endl;
            throw GameException("meet an unknown event");
            break;
        }

        break; // break the switch
    }

    default:
        break;
    }
}

PlayerColor Game::_which_player(const Position& pos, PlayerColor ignore_color) const {
    for (const auto& [color, player] : _color_player_map) {
        if (color == ignore_color) continue;
        if (player->has_item(pos)) {
            return color;
        }
    }

    return PlayerColor::UNKNOWN_COLOR;
    // int i = 0;
    // PlayerColor return_color; 

    // for (const auto& [color, player] : _color_player_map) {
    //     if (player->has_item(pos)) {
    //         return_color = color; ++i;
    //     }
    // }

    // assert(i <= 1);

    // if (i == 0)
    //     return PlayerColor::UNKNOWN_COLOR;
    // else 
    //     return return_color;
}

void Game::_print() const {
    ::std::cout << *this << ::std::endl;
}

::std::ostream& operator<<(::std::ostream& os, const Game& game) {
    for (Axis row = 0; row <= Position::max_axis; ++row) {
        for (int col = Position::max_axis + 1; col >= 0; --col) {
            auto color = game._which_player({row, Axis(col)});
            if (color == PlayerColor::UNKNOWN_COLOR) {
                os << "    ";
            } else {
                os << (int)color << game._color_player_map.at(color)->get_item({row, Axis(col)})->get_type() << " ";
            }
        }
        os << "\n";
    }

    return os;
}

}