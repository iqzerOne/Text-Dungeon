#include "Enemy.h"


class Skeleton : public Enemy{
    private:
        int counter_turn;
    public:
        Skeleton(std::string name, int hp, int damage);
        int attack_damage()override;
};