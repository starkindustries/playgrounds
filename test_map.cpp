#include <iostream>
#include <map>
#include <string>
#include <vector>

// To compile:
// g++ test_map.cpp
struct datablip
{
    char *data;
    size_t size;
};

typedef std::map<std::string, std::vector<datablip>> blipmap;

// Comm Callback simulator
void received_message(std::string msg, std::string receive_time, blipmap &bmap)
{
    datablip blip;
    blip.data = new char[msg.size() + 1];
    std::copy(msg.begin(), msg.end(), blip.data);
    // blip.data = msg.c_str();
    blip.size = msg.length();
    bmap[receive_time].insert(bmap[receive_time].begin(), blip);
}

int main()
{    
    std::cout << "Test map:" << std::endl;
    std::map<int, std::vector<int>> map1 =
        {
            {100, {1, 2, 8, 6}},
            {101, {3, 2, 3, 4}},
            {102, {7, 8, 1, 9}},
            {103, {0, 9, 3, 4}},
            {104, {1, 6, 2, 0}}};

    map1[100].push_back(1000);
    map1[100].push_back(1001);
    map1[100].insert(map1[100].begin(), 0);

    for (auto item : map1)
    {
        std::cout << "Key[" << item.first << "] Size[" << item.second.size() << "] Vector contents: { ";
        for (auto num : item.second)
        {
            std::cout << num << " ";
        }
        std::cout << "}" << std::endl;
    }

    std::cout << "\n=========================================\n" << std::endl;

    std::cout << "Receiving reversed data within one timestep..\n" << std::endl;

    blipmap bmap;
    
    // receive time 2000
    received_message("hello5", "2000", bmap);
    received_message("hello4", "2000", bmap);
    received_message("hello3", "2000", bmap);
    received_message("hello2", "2000", bmap);
    received_message("hello1", "2000", bmap);
    received_message("hello0", "2000", bmap);

    // receive time 1000
    received_message("world2", "1000", bmap);
    received_message("world1", "1000", bmap);
    received_message("world0", "1000", bmap);    

    for (auto item : bmap)
    {
        std::cout << "received_time[" << item.first << "] Size[" << item.second.size() << "] Vector contents: { " << std::endl;
        for (auto db : item.second)
        {
            std::cout << "  " << db.data << "[" << db.size << "]" << std::endl;;
        }
        std::cout << "}" << std::endl;

    }
}