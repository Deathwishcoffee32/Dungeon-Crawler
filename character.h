#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
using namespace std;

class Character {
protected:
    string name;
    int health;
    int attack;

public:
    Character(string n, int h, int a);
    virtual ~Character();

    virtual void displayStats() const;

    int getHealth() const;
    int getAttack() const;
    string getName() const;

    void takeDamage(int dmg);
    bool isAlive() const;
};

#endif
