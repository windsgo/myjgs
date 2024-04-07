#pragma once

#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <iostream>
#include <cstring>

#include "type.h"
#include "item.h"
#include "block.h"

namespace myjgs {

class Player {
public:
    // using ptr = ::std::shared_ptr<Player>;
    // Player() = default;
    Player(const JGSPLayerInfoBlock& player_info);

    Player(const Player&) = default;
    Player& operator=(const Player&) = default;

    PlayerColor color() const {return _color;}

    void remove_item(const Position& pos);

    inline void clear() {
        _pos_item_map.clear();
    }

    inline void move_item(const Position& start_pos, const Position& end_pos) {
        _pos_item_map.insert(::std::make_pair(end_pos, _pos_item_map.at(start_pos)));
        _pos_item_map.at(start_pos).move_to(end_pos);
        _pos_item_map.erase(start_pos);
        // update map after move!!!
        // todo
    }

    const Item& get_item(const Position& pos) const {return _pos_item_map.at(pos);}

    bool has_item(const Position& pos) const;

    int get_current_score() const;

    inline uint32_t qq() const {return _qq;}
    inline const char* name() const {return _name;}

    // 用于统计荣誉称号数据
    // 告知player自己击杀他人的信息
    inline void notify_kill_event(const Item& killer, const Item& dead) {
        auto killertype = killer.get_type();
        auto deadtype = dead.get_type();
        // 神兵天降 (只在己方击杀他方(notify_kill_event)中记录, notify_dead_event中他方用炸弹,工兵击杀我方工兵不记录)
        if (killertype == ItemType::Gongbing) {
            if (deadtype == ItemType::Zhadan || deadtype == ItemType::Junqi) {
                _gongbing_destroyed_values += 3;
            } else if (deadtype == ItemType::Dilei) {
                _gongbing_destroyed_values += 2;
            } else if (deadtype == ItemType::Gongbing) {
                _gongbing_destroyed_values += 1;
            } else {
                throw GameException(std::string("notify_kill_event, gongbing kill invalid: ") + item_type2string(deadtype));
            }
        }

        // 拆弹专家
        if (deadtype == ItemType::Zhadan) {
            ++_destroyed_zhadan_count;
        }

        // 运筹帷幄
        if (killertype == ItemType::Silin) {
            if (deadtype == ItemType::Silin || deadtype == ItemType::Junzhang) {
                _silin_destroyed_values += 5;
            } else if (deadtype == ItemType::Shizhang) {
                _silin_destroyed_values += 4;
            } else if (deadtype == ItemType::Lvzhang) {
                _silin_destroyed_values += 3;
            } else if (deadtype == ItemType::Tuanzhang) {
                _silin_destroyed_values += 2;
            } else {
                _silin_destroyed_values += 1;
            }
        }

        // 七、八大天王
        if (deadtype == ItemType::Silin || deadtype == ItemType::Junzhang || deadtype == ItemType::Shizhang) {
            ++_destroyed_403938_count;
        }
    }
    // 告知player自己被他人击杀而死亡的信息
    inline void notify_dead_event(const Item& killer, const Item& dead) {
        (void)(killer);
        (void)(dead);
    }

    inline std::vector<int> get_stat() const { return std::vector<int> {
        _gongbing_destroyed_values,
        _destroyed_zhadan_count,
        _silin_destroyed_values,
        _destroyed_403938_count
    }; }

private:
    char _name[20];
    uint32_t _qq;
    PlayerColor _color;
    std::string _color_str;
    JGSLayoutBlock _init_layout;

    ::std::unordered_map<Position, Item> _pos_item_map;

    // 记录player的"荣誉称号"数据
    // "（1）“神兵天降”：使用工兵消灭敌方单位价值最高。
    // 注1：工兵消灭的单位中，炸弹与军旗价值3，地雷价值2，工兵价值1。"
    int _gongbing_destroyed_values {0}; // 己方工兵消灭单位的价值总和

    //（2）“拆弹专家”：消灭炸弹数量最多
    int _destroyed_zhadan_count {0}; // 己方消灭的他方炸弹数目总和

    // "（3）“运筹帷幄”：除炸弹与军旗外，司令消灭敌方单位价值最高
    // 注2：司令消灭的单位中，司令与军长价值5，师长价值4，旅长价值3，团长价值2，其余子力价值1。"
    int _silin_destroyed_values {0}; // 己方40消灭的他方单位价值总和

    // （4）“七大天王”/“八大天王”：单次战斗中斩获司令、军长、师长共计七枚/八枚
    int _destroyed_403938_count {0}; // 己方消灭他方40,39,38的数目总和
};

}
