#include "skeleton.h"
#include <iostream>
#include <random>

Skeleton::Skeleton(std::string name, int hp, int damage) : Enemy(name, hp, damage) {
    this->counter_turn = 0;
}

int Skeleton::attack_damage(){
    counter_turn++;
    if(counter_turn >= 5){
        std::cout << "Skeleton heals\n";
        hp += 5;
        counter_turn = 0;
    }
    return damage;
}