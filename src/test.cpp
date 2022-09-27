#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include <locale>
#include <exception>

#include "config.h"

#include <fstream>

#include "item.h"
#include "block.h"

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

void testread() {
    std::ifstream in_file(file_dir, std::ios::binary);
    if (!in_file) {
        std::cerr << "open error, file_dir: " << file_dir << std::endl;
        return;
    }

    JGSHeaderBlock header;
    in_file.read(reinterpret_cast<char *>(&header), sizeof(header));

    JGSPLayerInfoBlock player1_info;
    in_file.read(reinterpret_cast<char *>(&player1_info), sizeof(player1_info));

    
    JGSPLayerInfoBlock player2_info;
    in_file.read(reinterpret_cast<char *>(&player2_info), sizeof(player2_info));


    std::cout << header;

    // std::ofstream of("output.txt");

    // of << player1_info.player_name;
    // of.close();

    
    
    std::cout << player1_info.player_color << std::endl;   
    std::cout << player1_info.player_name << std::endl;
    std::cout << player1_info.player_layout;

    std::cout << player2_info.player_color << std::endl;
    std::cout << player2_info.player_name << std::endl;
    std::cout << player2_info.player_qqnumber << std::endl;
    std::cout << player2_info.player_layout;

    in_file.close();
}

void testread2() {
    std::ifstream in_file(file_dir, std::ios::binary);
    if (!in_file) {
        std::cerr << "open error, file_dir: " << file_dir << std::endl;
        return;
    }

    JGSTotalInfoBlock info;
    in_file.read(reinterpret_cast<char*>(&info), sizeof(info));

    JGSEventBlock event1;
    in_file.read(reinterpret_cast<char*>(&event1), sizeof(event1));

    

    auto& os = std::cout;

    os << info << "\n";

    for (size_t i = 0; i < sizeof(event1); ++i) {
        printf("%x\n", event1.byte[i]);
    }

    in_file.close();
}

int main(int argc, char** argv) {
    static_assert(sizeof(ItemColor) == 1);
    static_assert(sizeof(ItemType) == 1);
    static_assert(sizeof(bool) == 1);

    std::cout << sizeof(JGSPLayerInfoBlock) << std::endl;
    std::cout << sizeof(JGSTotalInfoBlock) << std::endl;

    static_assert(sizeof(JGSPLayerInfoBlock) == 88);
    static_assert(sizeof(JGSTotalInfoBlock) == 0x19c);

    std::cout << ConfigManager::getUniqueInstance()->addConfigFile("default", "config.json") << std::endl;
    auto v = ConfigManager::getUniqueInstance()->getConfig("default")->at("item_score");
    for (auto&& [name, value] : v.as_object()) {
        std::cout << name << ": [" << value.as_array().at(0) << ", " << value.as_array().at(1) << "]\n";
    }
    try {
        ConfigManager::getUniqueInstance()->getConfig("default")->at("1");
    } catch (const std::out_of_range& oor) {
        std::cerr << oor.what() << std::endl;
    }
    
    
    std::ifstream ifs("config.json");

    // json::parse()

    ifs.close();
    

    testread2();

    return 0;
}