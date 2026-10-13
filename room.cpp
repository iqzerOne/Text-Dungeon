#include "room.h"
#include <vector>
#include "ogre.h"
#include "skeleton.h"

std::vector<std::vector<RoomData>> levels = {
    {  // level 1
        {true, "Ogre", 100, 3, true, "sword_uncommon", ItemType::Weapon, 3},
        {true, "Ogre", 100, 3, false, "Unknown", ItemType::Unknown, 0},
        {false, "None", 0, 0, true, "potion_heal", ItemType::Potion, 30}
    },
    {  // level 2
        {true, "Skeleton", 50, 5, false, "Unknown", ItemType::Unknown, 0},
        {true, "Ogre", 100, 3, true, "potion_heal", ItemType::Potion, 35},
        {true,"Ogre",120,4,false,"Unknown",ItemType::Unknown,3},
        {false,"None",0,0,true,"potion_heal",ItemType::Potion,15},
    }
};

Room::Room(std::unique_ptr<Enemy> enemy, Item chest_item, bool is_enemy, bool is_chest, bool is_chest_open)
    : enemy(std::move(enemy)),
      chest_item(chest_item),
      is_enemy(is_enemy),
      is_chest(is_chest),
      is_chest_open(is_chest_open)
{
}
Item Room::get_chest_item(){
    return chest_item;
}
Enemy& Room::get_enemy(){
    return *enemy;
}
bool Room::get_is_enemy()const{
    return is_enemy;
}
bool Room::get_has_chest()const{
    return is_chest;
}
bool Room::get_has_chest_open()const{
    return is_chest_open;
}

void Room::print_enemy_room()const{
    if(enemy){
        enemy->print_enemy();
    }
} 

void Room::print_item_room()const{
    chest_item.print_item();
}

void Room::open_chest(){
    if(is_chest && !is_chest_open){
        is_chest_open = true;
    }
}

void Room::clear_enemy(){
    if(is_enemy && enemy && enemy->get_hp() <= 0){
        is_enemy = false;
    } 
    
}

void Room::clear_item_chest(){
    chest_item.clear_item();
}

Room build_room(const RoomData& data){
    std::unique_ptr<Enemy> enemy;
    if(data.has_enemy){
        if (data.enemy_name == "Ogre") enemy = std::make_unique<Ogre>(data.enemy_name,data.enemy_hp,data.enemy_damage);
        else if (data.enemy_name == "Skeleton") enemy = std::make_unique<Skeleton>(data.enemy_name,data.enemy_hp,data.enemy_damage);
    }
    Item item("None",ItemType::Unknown,0);
    if(data.has_chest){
        item = Item(data.item_name,data.item_type,data.item_value);
    }
    return Room(std::move(enemy),item,data.has_enemy,data.has_chest,false);
}

std::vector<Room> create_rooms(int level){
    std::vector<Room> rooms;
    const auto& data_list = levels[level - 1];
    for (int i = 0; i < data_list.size(); i++) {
        rooms.push_back(build_room(data_list[i]));
    }
    return rooms;
}