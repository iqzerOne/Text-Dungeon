#include "Enemy.h"


class Ogre : public Enemy{
    public:
        Ogre(std::string name, int hp, int damage);
        int attack_damage() override;
};