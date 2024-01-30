#include "ExampleScene.h"
#include <imgui-SFML.h>
#include <imgui.h>

ExampleScene::ExampleScene(GameEngine *gameEngine)
    : Scene(gameEngine)
{
    init();
}

void ExampleScene::init()
{
}

void ExampleScene::topLayer()
{

}

void ExampleScene::middleLayer()
{
}

void ExampleScene::bottomLayer()
{
}

void ExampleScene::update()
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

void ExampleScene::sMovement()
{
    
}

void ExampleScene::sCamera()
{
}

void ExampleScene::sLifespan()
{
}

void ExampleScene::sCollision()
{
}

void ExampleScene::sAnimation()
{
}

void ExampleScene::sRender()
{
    ImGui::ShowDemoWindow();
}

void ExampleScene::onEnd()
{
}

void ExampleScene::sDebug()
{
}

void ExampleScene::sDoAction(const Action &action)
{
}

Vec2 ExampleScene::gridToMidPixel(float gridX, float gridY, float offsetX, float offsetY)
{
    float pixelX = gridX * m_tileWidth;
    float pixelY = gridY * m_tileHeight;

    return Vec2((pixelX + (m_tileWidth / 2)) + offsetX, (pixelY + (m_tileHeight / 2)) + offsetY);
}