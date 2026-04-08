#pragma once

#include "Core/BaseObject.h"

class Square : public BaseObject
{
public:
    Square(const ax::Vec2& position, float size, const ax::Color4F& color);
    ~Square() override;

    void setPosition(const ax::Vec2& position) override;
    void setColor(const ax::Color4F& color);
    const ax::Color4F& getColor() const;

    void draw(ax::Node* parent) override;
    void update(float delta) override;

    ax::DrawNode* getDrawNode() const;

private:
    void refresh();

    ax::Color4F _color;
    ax::DrawNode* _node;
};
