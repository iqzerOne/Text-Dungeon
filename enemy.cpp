#include "enemy.h"
#include <iostream>
#include <vector>

std::vector<EnemyBase> Enemies{
    {"Ogre",100,3},
    {"Skeleton",50,3},
};

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

void Enemy::set_value_hp(int value){
    this->hp = value;
}

void Enemy::set_value_damage(int value){
    this->damage = value;
}