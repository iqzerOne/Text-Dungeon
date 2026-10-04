#include <iostream>
#include "inventory.h"

void Inventory::add_item_inventory(const Item& item){
    items.push_back(item);
}

int Inventory::get_size_inventory()const{
    return items.size();
}

void Inventory::print_inventory()const{
    for(int i = 0; i < items.size(); i++){
        std::cout << i + 1 << "." <<items[i].get_name() << " " << item_type_to_string(items[i].get_type()) << " " << items[i].get_value() << std::endl;
    }
}

Item Inventory::get_item(int index)const{
    return items[index];
}

void Inventory::delete_item(int index){
    items.erase(items.begin() + index);
}