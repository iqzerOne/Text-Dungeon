#include "battle.h"
#include "ui.h"

bool battle_enemy(Enemy& enemy,Player& hero){
    bool turn = true;
    while(enemy.get_hp() > 0 && hero.get_hp() > 0){
        if(turn){
            int dmg = hero.attack_damage();
            enemy.take_damage(dmg);
            show_damage_battle(turn,dmg);
            turn = false;
        }else{
            int dmg = enemy.attack_damage();
            hero.take_damage(enemy.attack_damage());
            show_damage_battle(turn,dmg);
            turn = true;
        }
    }
    if(hero.get_hp() > 0){
        return true;
    }else{
        return false;
    }
}