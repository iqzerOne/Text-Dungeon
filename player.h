#pragma once
#include <string>
#include <optional>
#include "inventory.h"
#include "item.h"


class Player{
    private:
        std::string name;
        int hp;
        int damage;
        Inventory items;
        std::optional<Item> hands_weapon;
    public:
        Player(std::string name, int hp, int damage);

        std::string get_name()const;
        int get_hp()const;
        int get_damage()const;
        std::optional<Item> get_equip()const;
        void take_damage(int value);
        void add_item_inventory_player(const Item& item);
        void show_inventory()const;
        int size_inventory_player()const;
        Item get_item_player(int index)const;
        void use_item_player(const Item& item);
        void delete_item_player(int index);
        int attack_damage();
};