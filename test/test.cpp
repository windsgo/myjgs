#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include <locale>
#include <exception>
#include <array>
#include <cstdlib>

#include "config.h"

#include <fstream>

#include "item.h"
#include "block.h"
#include "event.h"
#include "player.h"
#include "game.h"

#include <cstdio>

const std::string file_dir = "./test.jgs";

// std::string StringToUTF8(const std::string& gbkData)
// {
//     const char* GBK_LOCALE_NAME = "zh_CN.GBK";  //GBK在windows下的locale name(.936, CHS ), linux下的locale名可能是"zh_CN.GBK"

//     std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>>
//         conv(new std::codecvt<wchar_t, char, std::mbstate_t>(GBK_LOCALE_NAME));
//     std::wstring wString = conv.from_bytes(gbkData);    // string => wstring

//     std::wstring_convert<std::codecvt_utf8<wchar_t>> convert;
//     std::string utf8str = convert.to_bytes(wString);     // wstring => utf-8

//     return utf8str;
// }    
#include <sstream>
void testGame() {
    try {
        myjgs::Game::ptr game = std::make_shared<myjgs::Game>(file_dir);
        game->process_all_events();
        
        std::stringbuf strbuf;
        std::ostream str_os(&strbuf);
        str_os << *game;
        std::cout <<strbuf.str();

    } catch (const myjgs::GameException& e) {
        std::cerr << "gameexception:" << e.what() << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

using namespace myjgs;

int main(int argc, char** argv) {
    // system("chcp 65001");
    static_assert(sizeof(ItemColor) == 1);
    static_assert(sizeof(ItemType) == 1);
    static_assert(sizeof(bool) == 1);

    std::cout << sizeof(JGSPLayerInfoBlock) << std::endl;
    std::cout << sizeof(JGSTotalInfoBlock) << std::endl;

    static_assert(sizeof(JGSPLayerInfoBlock) == 88);
    static_assert(sizeof(JGSTotalInfoBlock) == 0x19c);
    static_assert(sizeof(JGSEventBlock) == 10);

    // test config
    // std::cout << ConfigManager::getUniqueInstance()->addConfigFile("default", "config.json") << std::endl;
    // auto v = ConfigManager::getUniqueInstance()->getConfig("default")->at("item_score");
    // for (auto&& [name, value] : v.as_object()) {
    //     std::cout << name << ": [" << value.as_array().at(0) << ", " << value.as_array().at(1) << "]\n";
    // }
    // try {
    //     ConfigManager::getUniqueInstance()->getConfig("default")->at("1");
    // } catch (const std::out_of_range& oor) {
    //     std::cerr << oor.what() << std::endl;
    // }

    testGame();
    

    return 0;
}