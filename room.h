#pragma once
#include <string>
#include <vector>
#include <memory>
#include <random>
#include "enemy.h"
#include "item.h"

extern std::vector<EnemyBase> Enemies;

struct RoomData {
  bool has_chest;
  std::string item_name;
  ItemType item_type;
  int item_value;
};


class Room{
    private:
        bool is_enemy;
        bool is_chest;
        bool is_chest_open;
        Item chest_item;
        std::unique_ptr<Enemy> enemy;
    public:
        Room(std::unique_ptr<Enemy> enemy,Item chest_item, bool is_enemy, bool is_chest, bool is_chest_open);
        bool get_is_enemy()const;
        bool get_has_chest()const;
        bool get_has_chest_open()const;
        Item get_chest_item();
        void print_enemy_room()const;
        void print_item_room()const;
        Enemy& get_enemy();
        void open_chest();
        void clear_item_chest();
        void clear_enemy();
};

Room build_room(const RoomData& data);
std::vector<Room> create_rooms(int level);
std::mt19937& get_global_rng();
bool is_enemy_flag();
EnemyBase random_enemy();