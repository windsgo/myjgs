#include "block.h"

std::ostream& operator<<(std::ostream& os, const JGSLayoutBlock& jgs_layout) {
    for (int row = 0; row < JGSLayoutBlock::row_num; ++row) {
        for (int col = 0; col < JGSLayoutBlock::col_num; ++col) {
            os << jgs_layout.item(row, col) << " ";
        }
        os << "\n";
    }
    
    return os;
}

std::ostream& operator<<(std::ostream& os, const JGSHeaderBlock& jgs_header) {
    os << jgs_header.discription << "\n";
    os << "self  color:" << jgs_header.self_color << "\n";
    os << "total steps:" << jgs_header.all_steps;
    
    return os; 
}

std::ostream& operator<<(std::ostream& os, const JGSPLayerInfoBlock& jgs_player_info) {
    os << "color :" << jgs_player_info.player_color << "\n";
    os << "name  :" << jgs_player_info.player_name << "\n";
    os << "qq_num:" << jgs_player_info.player_qqnumber << "\n";
    os << "layout:\n" << jgs_player_info.player_layout;

    return os;
}

std::ostream& operator<<(std::ostream& os, const JGSTotalInfoBlock& jgs_total_info) {
    os << ">>JGS_TOTAL_INFO:\n\n[JGS_HEADER]\n" << jgs_total_info.header_block << "\n\n[JGS_PLAYERINFO]\n";
    for (int i = 0; i < jgs_total_info.player_number; ++i) {
        os << ">Player " << i << ":\n" << jgs_total_info.player_info_block[i] << "\n";
    }

    return os;
}