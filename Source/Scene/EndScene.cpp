#include "Scene/EndScene.h"

using namespace ax;

bool EndScene::init()
{
    if (!Scene::init())
        return false;

    auto visibleSize = _director->getVisibleSize();
    auto origin = _director->getVisibleOrigin();

    auto label = Label::createWithTTF("Success", "fonts/Marker Felt.ttf", 64);
    if (label)
    {
        label->setPosition(origin + Vec2(visibleSize.width / 2, visibleSize.height / 2));
        addChild(label);
    }

    return true;
}
