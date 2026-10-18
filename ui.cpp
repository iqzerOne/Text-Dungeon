#include "ui.h"
#include "room.h"
#include <iostream>
#include <map>


std::string create_text_room(Room& room){
    std::string text = "Its room has";
    if(room.get_is_enemy()){
        text += " enemy ";
    }
    if(room.get_has_chest() && !room.get_has_chest_open()){
        text += " chest ";
    }
    if(!room.get_is_enemy() && !room.get_has_chest()){
        text += " nothing ";
    }
    return text;
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
    Item item = hero.get_item_player(choice);
    hero.use_item_player(item);
    hero.delete_item_player(choice);
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
    }
    return current_room;
}

void show_hp(int hp){
    std::cout <<"HP: "<< hp << std::endl;
}

void show_room_info(int current_room,int level,Room& room){
    std::cout << "Room "<< current_room+1 
    << " Level: "<<level
    <<"\n" << create_text_room(room) << std::endl;
}
void show_kill_enemy(){
    std::cout << "Kill all enemy" << std::endl;
}
void show_damage_battle(bool turn,int damage){
    std::cout << (turn? "Hero attack: " : "Enemy attack: ") << damage << std::endl;
}