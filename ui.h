#pragma once
#include <string>
#include "room.h"
#include "player.h"

std::string create_text_room(Room& room);
int correct_number(int min, int max);
void use_item(Player& hero);
void inventory_choice(Player& hero);
int choice_menu_hero_room(Room& room,int count_room_size,int current_room,Player& hero);
void show_hp(int hp);
void show_room_info(int current_room,int level,Room& room);
void show_kill_enemy();
void show_damage_battle(bool turn,int damage);