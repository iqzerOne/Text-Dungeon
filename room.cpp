#include "room.h"


Room::Room(Enemy enemy, Item chest_item, bool is_enemy, bool is_chest, bool is_chest_open)
    : enemy(enemy),
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
    return enemy;
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
    enemy.print_enemy();
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
    if(is_enemy && enemy.get_hp() <= 0){
        is_enemy = false;
    }
}

void Room::clear_item_chest(){
    chest_item.clear_item(chest_item);
}
