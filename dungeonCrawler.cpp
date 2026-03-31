#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Character {
protected:
    string name;
    int health;
    int attack;

public:
    Character(string n, int h, int a) : name(n), health(h), attack(a) {}
    virtual ~Character() {}

    virtual void displayStats() const {
        cout << name << " | HP: " << health << " | ATK: " << attack << endl;
    }

    int getHealth() const { return health; }
    int getAttack() const { return attack; }
    string getName() const { return name; }

    void takeDamage(int dmg) { health -= dmg; }
    bool isAlive() const { return health > 0; }
};

class Player : public Character {
private:
    int level;

public:
    Player(string n) : Character(n, 30, 5), level(1) {}

    void levelUp() {
        level++;
        health += 10;
        attack += 3;
        cout << "\nLevel Up! You are now level " << level << "!\n";
    }
};

class Enemy : public Character {
public:
    Enemy(string n, int h, int a) : Character(n, h, a) {}
};

class Game {
private:
    unique_ptr<Player> player;

public:
    Game() {
        srand(time(0));
    }

    void start() {
        string name;
        cout << "Enter your character name: ";
        cin >> name;

        player = make_unique<Player>(name);

        cout << "\nWelcome to the Dungeon, " << name << "!\n";
        gameLoop();
    }

    unique_ptr<Enemy> generateEnemy(int level) {
        return make_unique<Enemy>(
            "Goblin Lv." + to_string(level),
            10 + level * 5,
            3 + level * 2
        );
    }

    void battle(Enemy& enemy) {
        cout << "\nA wild " << enemy.getName() << " appears!\n";

        while (player->isAlive() && enemy.isAlive()) {
            cout << "\n1) Attack  2) Run\n";
            int choice;
            cin >> choice;

            if (choice == 1) {
                int playerDmg = rand() % player->getAttack() + 1;
                int enemyDmg = rand() % enemy.getAttack() + 1;

                enemy.takeDamage(playerDmg);
                cout << "You deal " << playerDmg << " damage!\n";

                if (enemy.isAlive()) {
                    player->takeDamage(enemyDmg);
                    cout << enemy.getName() << " hits back for " << enemyDmg << " damage!\n";
                }

                player->displayStats();
                enemy.displayStats();
            } else {
                cout << "You escaped!\n";
                return;
            }
        }

        if (player->isAlive()) {
            cout << "\nYou defeated the " << enemy.getName() << "!\n";
            player->levelUp();
        } else {
            cout << "\nGame Over...\n";
        }
    }

    void gameLoop() {
        int level = 1;

        while (player->isAlive()) {
            cout << "\n--- Dungeon Level " << level << " ---\n";
            auto enemy = generateEnemy(level);
            battle(*enemy);

            if (!player->isAlive()) break;

            cout << "\nContinue? (1 = yes, 0 = no): ";
            int cont;
            cin >> cont;
            if (!cont) break;

            level++;
        }

        cout << "\nFinal Stats:\n";
        player->displayStats();
    }
};

int main() {
    Game game;
    game.start();
    return 0;
}


