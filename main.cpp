#include <iostream>

#include "Engine.h"

int main() {
    Engine* engine = new Engine({10, 10}, "data.txt", ".");
    engine->play();

    delete engine;
    return 0;
}
