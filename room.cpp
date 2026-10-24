#include "room.h"
#include "ogre.h"
#include "skeleton.h"

std::vector<LevelData> levels = {
    {3,0.35,0.45},  // level 1
    {4,0.40,0.44},  // level 2
};

Room::Room(std::unique_ptr<Enemy> enemy, Item chest_item, bool is_enemy, bool is_chest, bool is_chest_open)
    : enemy(std::move(enemy)),
      chest_item(chest_item),
      is_enemy(is_enemy),
      is_chest(is_chest),
      is_chest_open(is_chest_open)
{
}
Item Room::get_chest_item(){
    return chest_item;
}
Enemy& Room::get_enemy(){
    return *enemy;
}
bool Room::get_is_enemy()const{
    return is_enemy;
}
bool Room::get_has_chest()const{
    return is_chest;
}
bool Room::get_has_chest_open()const{
    return is_chest_open;
}

void Room::print_enemy_room()const{
    if(enemy){
        enemy->print_enemy();
    }
} 

void Room::print_item_room()const{
    chest_item.print_item();
}

void Room::open_chest(){
    if(is_chest && !is_chest_open){
        is_chest_open = true;
    }
}

void Room::clear_enemy(){
    if(is_enemy && enemy && enemy->get_hp() <= 0){
        is_enemy = false;
        enemy.reset();
    }
}

void Room::clear_item_chest(){
    chest_item.clear_item();
}

std::mt19937& get_global_rng(){
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

bool is_flag(double chance){
    std::bernoulli_distribution coin(chance);
    return coin(get_global_rng());
}

EnemyBase random_enemy() {
    std::uniform_int_distribution<int> ran_enemy(0, Enemies.size()-1);
    EnemyBase selected_enemy = Enemies[ran_enemy(get_global_rng())];
    ran_enemy = std::uniform_int_distribution<int>(selected_enemy.damage,selected_enemy.damage+10);
    selected_enemy.damage = ran_enemy(get_global_rng());
    ran_enemy = std::uniform_int_distribution<int>(selected_enemy.hp,selected_enemy.hp+10);
    selected_enemy.hp = ran_enemy(get_global_rng());
    return selected_enemy;
}

ItemBase random_item() {
    std::uniform_int_distribution<int> ran_item(0, ItemsBase.size()-1);
    ItemBase selected_item = ItemsBase[ran_item(get_global_rng())];
    std::uniform_int_distribution<int>val(selected_item.value,selected_item.value+10);
    selected_item.value = val(get_global_rng());
    return selected_item;
}

Room build_room(double chance_enemy,double chance_chest) {
    std::unique_ptr<Enemy> enemy;
    bool has_enemy = is_flag(chance_enemy);
    if(has_enemy){
        auto enemy_ran = random_enemy();
        if (enemy_ran.name == "Ogre") enemy = std::make_unique<Ogre>(enemy_ran.name,enemy_ran.hp,enemy_ran.damage);
        else if (enemy_ran.name == "Skeleton") enemy = std::make_unique<Skeleton>(enemy_ran.name,enemy_ran.hp,enemy_ran.damage);
    }
    Item item("None",ItemType::Unknown,0);
    bool has_chest = is_flag(chance_chest);
    if(has_chest){
        auto item_ran = random_item();
        item = Item(item_ran.name,item_ran.type,item_ran.value);
    }
    return Room(std::move(enemy),item,has_enemy,has_chest,false);
}

std::vector<Room> create_rooms(int level){
    std::vector<Room> rooms;
    const LevelData& data = levels[level - 1];
    for (int i = 0; i < data.room_count; i++) {
        rooms.push_back(build_room(data.chance_enemy,data.chance_chest));
    }
    return rooms;
}