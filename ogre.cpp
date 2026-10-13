#include "Ogre.h"
#include <iostream>
#include <random>

Ogre::Ogre(std::string name, int hp, int damage) : Enemy(name, hp, damage) {
}
int Ogre::attack_damage(){
    std::random_device rd;
    std::mt19937 crit(rd());
    std::bernoulli_distribution coin(0.15);
    if(coin(crit)){
        std::cout << "Critical damage" << std::endl;
        return damage + (damage * 18 / 100);
    }else{
        return damage;
    }
}