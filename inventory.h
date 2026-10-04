#pragma once
#include <vector>
#include "item.h"

class Inventory{
    private:
        std::vector<Item> items;
    public:
        int get_size_inventory()const;
        void add_item_inventory(const Item& item);
        void print_inventory()const;
        Item get_item(int index)const;
        void delete_item(int index);
};