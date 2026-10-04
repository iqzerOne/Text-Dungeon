#include <iostream>
#include <vector>
#include <map>
#include "item.h"
#include "inventory.h"
#include "player.h"
#include "enemy.h"
#include "room.h"

std::vector<Room> create_room(int level){
    std::vector<Room> rooms;
    Enemy enemy_1("Ogo", 30,10);
    Item sword("sword",ItemType::Weapon,20);
    bool is_enemy = true; 
    bool is_chest = true; 
    bool is_chest_open = false;
    Room room_1(enemy_1,sword,is_enemy,is_chest,is_chest_open);
    rooms.push_back(room_1);
    is_chest = false; 
    Room room_2(enemy_1,sword,is_enemy,is_chest,is_chest_open);
    rooms.push_back(room_2);
    is_enemy = false;
    is_chest = true;
    Room room_3(enemy_1,sword,is_enemy,is_chest,is_chest_open);
    rooms.push_back(room_3);
    return rooms;
}

std::string create_text_room(Room& room){
    std::string text = "Its room has";
    if(room.get_is_enemy()){
        text += " enemy ";
    }
    if(room.get_has_chest()){
        text += " chest ";
    }
    if(!room.get_is_enemy() && !room.get_has_chest()){
        text += " nothing ";
    }
    return text;
}

bool battle_enemy(Enemy& enemy,Player& hero){
    bool turn = true;
    while(enemy.get_hp() > 0 && hero.get_hp() > 0){
        if(turn){
            enemy.take_damage(hero.get_damage());
            turn = false;
        }else{
            hero.take_damage(enemy.get_damage());
            turn = true;
        }
    }
    if(hero.get_hp() > 0){
        return true;
    }else{
        return false;
    }
}

int correct_number(int min, int max){
    std::string s;
    while (true) {
        std::cin >> s;
        bool ok = !s.empty();
        for (char c : s) {
            if (!std::isdigit(static_cast<unsigned char>(c))) {
                ok = false;
                break;
            }
        }
        if (ok){
            int number = std::stoi(s);
            if(number < min){
                std::cout << "Pls input correct number" << std::endl;
            }else if(number > max){
                std::cout << "Pls input correct number" << std::endl;
            }else{
                return number;
            }
        }else{
            std::cout << "Pls input number" << std::endl;
        }
        s = "";
    }
    return 0;
}


void use_item(Player& hero){
    hero.show_inventory();
    std::cout << "Choice item" << std::endl;
    int choice = correct_number(1,hero.size_inventory_player()) - 1;
    //Выбираем
    //применяем
    Item item = hero.get_item_player(choice);
    hero.use_item_player(item);
    hero.delete_item_player(choice);
    //удаляем +
}

void inventory_choice(Player& hero){
    hero.show_inventory();
    std::cout << "1.Use item" << std::endl;
    std::cout << "2.Close inventory" << std::endl;
    int choice = correct_number(1,2);
    if(choice == 1){
        use_item(hero);
    }else{
        return;
    }

}

int choice_menu_hero_room(Room& room,int count_room_size,int current_room,Player& hero){
    int ui = 1;
    std::map<int,std::string> mp_choice;
    if(current_room >= 0 && current_room < count_room_size){
        if(current_room + 1 == count_room_size){
            std::cout << ui << ".Exit" << std::endl;
            mp_choice[ui] = "Exit";
            ui += 1;
        }else{
            std::cout << ui << ".Next room" << std::endl;
            mp_choice[ui] = "Next";
            ui += 1; 
        }
    }
    if(current_room > 0){
        std::cout << ui << ".Back room" << std::endl;
        mp_choice[ui] = "Back";
        ui += 1;
    }
    if(room.get_has_chest() && !room.get_has_chest_open()){
        std::cout << ui << ".Open chest" << std::endl;
        mp_choice[ui] = "Open";
        ui += 1;
    }
    if(hero.size_inventory_player() > 0){
        std::cout << ui << ".Open inventory" << std::endl;
        mp_choice[ui] = "OpenInv";
        ui += 1;
    }

    int choice = correct_number(1, ui - 1);
    if(mp_choice[choice] == "Next" || mp_choice[choice] == "Exit"){
        return current_room + 1;
    }
    if(mp_choice[choice] == "Back"){
        return current_room - 1;
    }
    if(mp_choice[choice] == "Open"){
        room.print_item_room();
        hero.add_item_inventory_player(room.get_chest_item());
        room.clear_item_chest();
        room.open_chest();
    }
    if(mp_choice[choice] == "OpenInv"){
        inventory_choice(hero);
        // hero.show_inventory();
    }
    return current_room;
}

void play(){
    Player hero("hero", 100, 20);
    int current_room = 0;
    int level = 1;
    std::vector<Room> rooms = create_room(level);
    bool turn = true;
    while(current_room < rooms.size() && hero.get_hp() > 0){
        std::cout << "Room "<< current_room+1 <<"\n" << create_text_room(rooms[current_room]) << std::endl;
        std::cout << "HP:" << hero.get_hp() << std::endl;
        if(rooms[current_room].get_is_enemy()){
            std::cout << "Kill all enemy" << std::endl;
            if(!battle_enemy(rooms[current_room].get_enemy(),hero)){
                return;
            }
            rooms[current_room].clear_enemy();
        }
        current_room = choice_menu_hero_room(rooms[current_room],rooms.size(),current_room,hero);
    }
}


int main(){
    play();
    return 0;
}