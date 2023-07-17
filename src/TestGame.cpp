#include "TestGame.h"

TestGame::TestGame(GameEngine *gameEngine)
    : Scene(gameEngine)
{
    init();

    if (!m_music.openFromFile("/Users/gillifish/Desktop/GitRepos/PhoenixGameEngine/sounds/littleroot_town.ogg"))
            return; // error
    m_music.play();
}

void TestGame::init()
{
    m_tileWidth = 32;
    m_tileHeight = 32;

    m_tilemap = Tilemap("outside_ts", Vec2(32, 32), "config/map.txt");

    registerAction(sf::Keyboard::W, "UP");
    registerAction(sf::Keyboard::S, "DOWN");
    registerAction(sf::Keyboard::A, "LEFT");
    registerAction(sf::Keyboard::D, "RIGHT");
    registerAction(sf::Keyboard::G, "DEBUG");

    bottomLayer();
    middleLayer();
    topLayer();

    m_camera.setSize(sf::Vector2f(960.0, 640.0f));
    m_camera.setCenter(m_player->getComponent<CTransform>().pos.x, m_player->getComponent<CTransform>().pos.x);
    m_camera.zoom(0.7);
}

void TestGame::topLayer()
{

}

void TestGame::middleLayer()
{
    auto e = m_entityManager.addEntity("player");
    e->addComponent<CTransform>().pos = gridToMidPixel(2, 2, 0, -8);
    e->addComponent<CState>("IDLE_DOWN");
    e->addComponent<CAnimation>(m_game->assets().getAnimation("IDLE_DOWN"), true);
    e->addComponent<CBoundingBox>(Vec2(32, 48));

    m_player = e;
}

void TestGame::bottomLayer()
{
    auto f1 = m_entityManager.addEntity("TILE");
    f1->addComponent<CTransform>().pos = gridToMidPixel(3, 6);
    f1->addComponent<CAnimation>(m_game->assets().getAnimation("FLOWER_1"), true);
    f1->addComponent<CBoundingBox>(Vec2(32, 32));

    auto f2 = m_entityManager.addEntity("TILE");
    f2->addComponent<CTransform>().pos = gridToMidPixel(4, 6);
    f2->addComponent<CAnimation>(m_game->assets().getAnimation("FLOWER_2"), true);
    f2->addComponent<CBoundingBox>(Vec2(32, 32));

    for (auto tile : m_tilemap.getTileMap())
    {
        auto e = m_entityManager.addEntity(tile.tag);
        e->addComponent<CSprite>();
        auto &sprite = e->getComponent<CSprite>().sprite;
        sprite.setTexture(m_game->assets().getTexture(m_tilemap.getTextureTag()));
        Vec2 v(m_tilemap.gridToPixel(tile.textureX, tile.textureY));
        sprite.setTextureRect(sf::IntRect(v.x, v.y, m_tilemap.getTileSize().x, m_tilemap.getTileSize().y));
        sprite.setOrigin(m_tilemap.getTileSize().x / 2, m_tilemap.getTileSize().y / 2);

        auto pos = gridToMidPixel(tile.renderX, tile.renderY);
        sprite.setPosition(pos.x, pos.y);
    }
}

void TestGame::update()
{
    m_entityManager.update();

    // TODO: implement pause functionality

    sMovement();
    sLifespan();
    sCollision();
    sAnimation();
    sCamera();
    sRender();
}

void TestGame::sMovement()
{
    m_player->getComponent<CTransform>().velocity = {0.0, 0.0};

    // Implement player movement
    if (m_player->getComponent<CInput>().up)
    {
        m_player->getComponent<CTransform>().velocity.y = -3;
        m_player->getComponent<CState>().state = "WALK_UP";
    }
    else if (m_player->getComponent<CInput>().down)
    {
        m_player->getComponent<CTransform>().velocity.y = 3;
        m_player->getComponent<CState>().state = "WALK_DOWN";
    }
    else if (m_player->getComponent<CInput>().left)
    {
        m_player->getComponent<CTransform>().velocity.x = -3;
        m_player->getComponent<CState>().state = "WALK_LEFT";
    }
    else if (m_player->getComponent<CInput>().right)
    {
        m_player->getComponent<CTransform>().velocity.x = 3;
        m_player->getComponent<CState>().state = "WALK_RIGHT";
    }
    else if (m_player->getComponent<CTransform>().velocity == Vec2(0.0f, 0.0f))
    {
        m_player->getComponent<CState>().state = "IDLE_DOWN";
    }

    // Update all entities by their current velocity

    for (auto e : m_entityManager.getEntities())
    {
        e->getComponent<CTransform>().pos.x += e->getComponent<CTransform>().velocity.x;
        e->getComponent<CTransform>().pos.y += e->getComponent<CTransform>().velocity.y;
    }
}

void TestGame::sCamera()
{
    auto pos = m_player->getComponent<CTransform>().pos;
    m_camera.setCenter(sf::Vector2f(pos.x, pos.y));
    m_game->window().setView(m_camera);
}

void TestGame::sLifespan()
{
}

void TestGame::sCollision()
{
}

void TestGame::sAnimation()
{
    if (m_player->getComponent<CState>().state == "IDLE_DOWN" && m_player->getComponent<CAnimation>().animation.getName() != "IDLE_DOWN")
    {
        m_player->addComponent<CAnimation>(m_game->assets().getAnimation("IDLE_DOWN"));
    }

    if (m_player->getComponent<CState>().state == "WALK_UP" && m_player->getComponent<CAnimation>().animation.getName() != "WALK_UP")
    {
        m_player->addComponent<CAnimation>(m_game->assets().getAnimation("WALK_UP"));
    }

    if (m_player->getComponent<CState>().state == "WALK_DOWN" && m_player->getComponent<CAnimation>().animation.getName() != "WALK_DOWN")
    {
        m_player->addComponent<CAnimation>(m_game->assets().getAnimation("WALK_DOWN"));
    }

    if (m_player->getComponent<CState>().state == "WALK_LEFT" && m_player->getComponent<CAnimation>().animation.getName() != "WALK_LEFT")
    {
        m_player->addComponent<CAnimation>(m_game->assets().getAnimation("WALK_LEFT"));
    }

    if (m_player->getComponent<CState>().state == "WALK_RIGHT" && m_player->getComponent<CAnimation>().animation.getName() != "WALK_RIGHT")
    {
        m_player->addComponent<CAnimation>(m_game->assets().getAnimation("WALK_RIGHT"));
    }

    for (auto e : m_entityManager.getEntities())
    {
        e->getComponent<CAnimation>().animation.update();
    }
}

void TestGame::sRender()
{
    //m_game->window().draw(m_map);
    for (auto e : m_entityManager.getEntities("TILEMAP"))
    {
        m_game->window().draw(e->getComponent<CSprite>().sprite);
    }

    for (auto e : m_entityManager.getEntities())
    {
        auto &transform = e->getComponent<CTransform>();

        if (e->hasComponent<CAnimation>())
        {
            auto &animation = e->getComponent<CAnimation>().animation;
            animation.getSprite().setRotation(transform.angle);
            animation.getSprite().setPosition(transform.pos.x, transform.pos.y);
            animation.getSprite().setScale(transform.scale.x, transform.scale.y);
            m_game->window().draw(animation.getSprite());
        }

        if (e->hasComponent<CBoundingBox>() && e->getComponent<CBoundingBox>().active)
        {
            auto &bBox = e->getComponent<CBoundingBox>();
            bBox.rect.setPosition(transform.pos.x, transform.pos.y);
            m_game->window().draw(bBox.rect);
        }
    }
}

void TestGame::onEnd()
{
}

void TestGame::sDebug()
{
}

void TestGame::sDoAction(const Action &action)
{
    if (action.type() == "START")
    {
        if (action.name() == "UP")
        {
            m_player->getComponent<CInput>().up = true;
        }
        else if (action.name() == "DOWN")
        {
            m_player->getComponent<CInput>().down = true;
        }
        else if (action.name() == "LEFT")
        {
            m_player->getComponent<CInput>().left = true;
        }
        else if (action.name() == "RIGHT")
        {
            m_player->getComponent<CInput>().right = true;
        }
        else if (action.name() == "DEBUG")
        {
            for (auto e : m_entityManager.getEntities())
            {
                if (e->getComponent<CBoundingBox>().has)
                {
                    if (e->getComponent<CBoundingBox>().active)
                    {
                        e->getComponent<CBoundingBox>().active = false;
                    }
                    else
                    {
                        e->getComponent<CBoundingBox>().active = true;
                    }
                }
            }
        }
    }

    if (action.type() == "END")
    {
        if (action.name() == "UP")
        {
            m_player->getComponent<CInput>().up = false;
        }
        else if (action.name() == "DOWN")
        {
            m_player->getComponent<CInput>().down = false;
        }
        else if (action.name() == "LEFT")
        {
            m_player->getComponent<CInput>().left = false;
        }
        else if (action.name() == "RIGHT")
        {
            m_player->getComponent<CInput>().right = false;
        }
    }
}

Vec2 TestGame::gridToMidPixel(float gridX, float gridY, float offsetX, float offsetY)
{
    float pixelX = gridX * m_tileWidth;
    float pixelY = gridY * m_tileHeight;

    return Vec2((pixelX + (m_tileWidth / 2)) + offsetX, (pixelY + (m_tileHeight / 2)) + offsetY);
}