#pragma once
#include "enemy.h"
#include "item.h"

class Room{
    private:
        bool is_enemy;
        bool is_chest;
        bool is_chest_open;
        Item chest_item;
        Enemy enemy;
    public:
        Room(Enemy enemy,Item chest_item, bool is_enemy, bool is_chest, bool is_chest_open);
        bool get_is_enemy()const;
        bool get_has_chest()const;
        bool get_has_chest_open()const;
        Item get_chest_item();
        void print_enemy_room()const;
        void print_item_room()const;
        Enemy& get_enemy();
        void open_chest();
        void clear_item_chest();
        void clear_enemy();

};