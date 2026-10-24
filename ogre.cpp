#include "ogre.h"
#include "room.h"
#include <iostream>
#include <random>

Ogre::Ogre(std::string name, int hp, int damage) : Enemy(name, hp, damage) {
}
int Ogre::attack_damage(){
    std::bernoulli_distribution coin(0.15);
    if(coin(get_global_rng())){
        std::cout << "Critical damage" << std::endl;
        return damage + (damage * 18 / 100);
    }else{
        return damage;
    }
}