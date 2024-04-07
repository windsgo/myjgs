#include "player.h"

namespace myjgs {

Player::Player(const JGSPLayerInfoBlock &player_info)
{
    memcpy(_name, player_info.player_name, 20);
    _qq = player_info.player_qqnumber;
    _color = player_info.player_color;
    _color_str = itemcolor_type2string(_color);
    _init_layout = player_info.player_layout;

    for (int init_row = 0; init_row < JGSLayoutBlock::row_num; ++init_row)
    {
        for (int init_col = 0; init_col < JGSLayoutBlock::col_num; ++init_col)
        {
            if (_init_layout.item(init_row, init_col) == ItemType::JQNone) continue;
            Position pos = Position::from_init_layout_pos(init_row, init_col);
            switch (_color)
            {
            case PlayerColor::YELLOW:
                // pos
                break;

            case PlayerColor::PURPLE:
                pos.rotate_counter_clockwise(1);
                break;

            case PlayerColor::GREEN:
                pos.rotate_counter_clockwise(2);
                break;

            case PlayerColor::BLUE:
                pos.rotate_counter_clockwise(3);
                break;
            
            default:
                break;
            }
            // Item::ptr i_p = std::make_shared<Item>(_init_layout.item(init_row, init_col), _color, pos);
            Item i {_init_layout.item(init_row, init_col), _color, pos};
            _pos_item_map.emplace(pos, i);
        }
    }
   
}

void Player::remove_item(const Position& pos) {
    if (_pos_item_map.erase(pos) != 1) {
        throw GameException("Player::remove_item failed");
    }
}

int Player::get_current_score() const {
    int score = 0;
    for (const auto& [pos, item_p] : _pos_item_map) {
        _unused(pos);
        score += item_score(item_p.get_type());
    }

    return score;
}

bool Player::has_item(const Position& pos) const {
    return (_pos_item_map.find(pos) != _pos_item_map.end()); // not equal means 'has'
}

}
