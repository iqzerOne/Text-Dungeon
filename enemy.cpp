#include "enemy.h"
#include <iostream>

Enemy::Enemy(std::string name, int hp, int damage){
    this->name = name;
    this->hp = hp;
    this->damage = damage;
}

std::string Enemy::get_name()const{
    return name;
}
int Enemy::get_hp()const{
    return hp;
}
int Enemy::get_damage()const{
    return damage;
}
void Enemy::take_damage(int value){
    this->hp -= value;
    if(this->hp < 0){
        this->hp = 0;
    }
}

void Enemy::print_enemy()const{
    std::cout << this->name << " " << this->hp << " " << this->damage << std::endl;
}

int Enemy::attack_damage(){
    return damage;
}