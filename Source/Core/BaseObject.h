#pragma once

#include "axmol.h"

class BaseObject
{
public:
    BaseObject(const ax::Vec2& position = ax::Vec2::ZERO, float width = 0.0f, float height = 0.0f);
    virtual ~BaseObject();

    virtual void setPosition(const ax::Vec2& position);
    const ax::Vec2& getPosition() const;

    virtual void setSize(float width, float height);
    void setSize(float size);
    ax::Size getSize() const;

    void setRotation(float rotation);
    float getRotation() const;

    ax::Rect getBounds() const;
    virtual bool containsPoint(const ax::Vec2& point) const;
    virtual bool hitTest(const ax::Vec2& point) const;
    void getRotatedCorners(ax::Vec2 corners[4]) const;
    bool intersects(const BaseObject& other) const;

    virtual void draw(ax::Node* parent) = 0;
    virtual void update(float delta);

    void setVisible(bool visible);
    bool isVisible() const;

protected:
    ax::Vec2 _position;
    float _width;
    float _height;
    float _rotation;
    bool _visible;
};
