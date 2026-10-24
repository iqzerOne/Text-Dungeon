#include "player.h"

Player::Player(std::string name, int hp, int damage){
    this->name = name;
    this->hp = hp;
    this->damage = damage;
}
std::string Player::get_name()const{
    return name;
}
int Player::get_hp()const{
    return hp;
}
int Player::get_damage()const{
    return damage;
}

std::optional<Item> Player::get_equip()const{
    if(hands_weapon){
        return hands_weapon;
    }else{
        return std::nullopt;
    }
}

void Player::take_damage(int value){
    this->hp -= value;
    if(this->hp < 0){
        this->hp = 0;
    } 
}
void Player::add_item_inventory_player(const Item& item){
    items.add_item_inventory(item);
}
void Player::show_inventory()const{
    items.print_inventory();
}

int Player::size_inventory_player()const{
    return items.get_size_inventory();
}

void Player::delete_item_player(int index){
    items.delete_item(index);
}
void Player::use_item_player(const Item& item){
    if(item.get_type() == ItemType::Potion){
        this->hp += item.get_value();
    }else if(item.get_type() == ItemType::Weapon){
        // this->damage += item.get_value();
        if(hands_weapon){
            Item change_weapon = *hands_weapon;
            add_item_inventory_player(change_weapon);
            hands_weapon = item;
        }else{
            hands_weapon = item;
        }
        
    }
}

Item Player::get_item_player(int index)const{
    return items.get_item(index);
}

int Player::attack_damage(){
    if(hands_weapon){
        return damage + hands_weapon->get_value();
    }else{
        return damage;
    }
    // return damage;
}