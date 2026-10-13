#pragma once
#include <string>
#include "inventory.h"

class Player{
    private:
        std::string name;
        int hp;
        int damage;
        Inventory items;
    public:
        Player(std::string name, int hp, int damage);

        std::string get_name()const;
        int get_hp()const;
        int get_damage()const;
        void take_damage(int value);
        void add_item_inventory_player(const Item& item);
        void show_inventory()const;
        int size_inventory_player()const;
        Item get_item_player(int index)const;
        void use_item_player(const Item& item);
        void delete_item_player(int index);
};