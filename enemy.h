#pragma once
#include <string>

class Enemy{
    private:
        std::string name;
        int hp;
        int damage;
    public:
        Enemy(std::string name, int hp,int damage);

        std::string get_name()const;
        int get_hp()const;
        int get_damage()const;
        void take_damage(int value);
        void print_enemy()const;
};