#include <cassert>
#include "../include/Player.h"

int main() {
    Player p("Test");

    // Test initial stats
    assert(p.getHealth() == 30);
    assert(p.getAttack() == 5);

    // Test leveling
    p.levelUp();
    assert(p.getHealth() > 30);
    assert(p.getAttack() > 5);

    return 0;
}
