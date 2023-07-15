#include <iostream>
#include "Engine/Game/GameEngine.h"
#include "TestGame.h"

int main(int argc, char *argv[])
{
    std::unique_ptr<GameEngine> engine (new GameEngine("config/assets.txt"));

    engine->run();

    return 0;
}
