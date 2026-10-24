#include "game.h"
#include "ui.h"
#include "battle.h"
#include "player.h"
#include "room.h"
#include <iostream>
#include <vector>

void play(){
    Player hero("hero", 100, 20);
    int current_room = 0;
    int level = 1;
    std::vector<Room> rooms = create_rooms(level);
    while(hero.get_hp() > 0 && current_room < rooms.size()){
        show_room_info(current_room,level,rooms[current_room]);
        show_hp(hero.get_hp());
        if(rooms[current_room].get_is_enemy()){
            show_kill_enemy();
            if(!battle_enemy(rooms[current_room].get_enemy(),hero)){
                break;
            }
            rooms[current_room].clear_enemy();
        }
        current_room = choice_menu_hero_room(rooms[current_room],rooms.size(),current_room,hero);
        show_hp(hero.get_hp());
        if(current_room >= rooms.size()){
            level += 1;
            if(level <= 2){
                current_room = 0;
                rooms.clear();
                rooms = create_rooms(level); 
            }else{
                break;
            }
        }
    }
    if(hero.get_hp() > 0){
        show_victory();
        return;
    }else{
        show_defeat();
        return;
    }
}