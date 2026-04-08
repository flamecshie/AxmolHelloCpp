#include "Core/BaseObject.h"

BaseObject::BaseObject(const ax::Vec2& position, float width, float height)
: _position(position)
, _width(width)
, _height(height)
, _visible(true)
{
}

BaseObject::~BaseObject() = default;

void BaseObject::setPosition(const ax::Vec2& position)
{
    _position = position;
}

const ax::Vec2& BaseObject::getPosition() const
{
    return _position;
}

void BaseObject::setSize(float width, float height)
{
    _width = width;
    _height = height;
}

void BaseObject::setSize(float size)
{
    setSize(size, size);
}

ax::Size BaseObject::getSize() const
{
    return ax::Size(_width, _height);
}

ax::Rect BaseObject::getBounds() const
{
    const float halfWidth  = _width * 0.5f;
    const float halfHeight = _height * 0.5f;
    return ax::Rect(_position.x - halfWidth, _position.y - halfHeight, _width, _height);
}

bool BaseObject::containsPoint(const ax::Vec2& point) const
{
    return getBounds().containsPoint(point);
}

bool BaseObject::hitTest(const ax::Vec2& point) const
{
    return _visible && containsPoint(point);
}

void BaseObject::update(float /*delta*/)
{
}

void BaseObject::setVisible(bool visible)
{
    _visible = visible;
}

bool BaseObject::isVisible() const
{
    return _visible;
}
