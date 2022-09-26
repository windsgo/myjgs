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
    os << "self color: " << jgs_header.self_color << "\n";
    os << "total steps:" << jgs_header.all_steps << "\n";
    
    return os; 
}