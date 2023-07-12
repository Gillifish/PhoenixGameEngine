#include "Scene.h"

struct PlayerConfig
{
};

class Scene_Play : public Scene
{
    std::string m_levelPath;
    std::shared_ptr<Entity> m_player;
    PlayerConfig playerConfig;

    void init(const std::string &levelPath);

    void spawnPlayer();
    void sAnimation();
    void sMovement();
    void sLifespan();
    void sEnemySpawner();
    void sCollision();
    void sRender();
    void sDoAction(Action action);
    void sDebug();
    void onEnd();

public:
    Scene_Play(GameEngine *gameEngine, const std::string &levelPath);
    Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);
    void update();
};