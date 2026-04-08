#include "Core/BaseObject.h"
#include <algorithm>
#include <cmath>

namespace
{
static float dot(const ax::Vec2& a, const ax::Vec2& b)
{
    return a.x * b.x + a.y * b.y;
}

static ax::Vec2 rotateVector(const ax::Vec2& v, float sinA, float cosA)
{
    return ax::Vec2(v.x * cosA - v.y * sinA, v.x * sinA + v.y * cosA);
}

//算出兩物體在軸上的影長
static bool projectPolygon(const ax::Vec2 axis, const ax::Vec2 points[4], float& min, float& max)
{
    min = max = dot(axis, points[0]);
    for (int i = 1; i < 4; ++i)
    {
        float projection = dot(axis, points[i]);
        min = std::min(min, projection);
        max = std::max(max, projection);
    }
    return true;
}

//檢查影子有沒有疊在一起
static bool overlapOnAxis(const ax::Vec2 axis, const ax::Vec2 a[4], const ax::Vec2 b[4])
{
    float aMin, aMax;
    float bMin, bMax;
    projectPolygon(axis, a, aMin, aMax);
    projectPolygon(axis, b, bMin, bMax);
    return !(aMax < bMin || bMax < aMin);
}
}

BaseObject::BaseObject(const ax::Vec2& position, float width, float height)
: _position(position)
, _width(width)
, _height(height)
, _rotation(0.0f)
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

void BaseObject::setRotation(float rotation)
{
    _rotation = rotation;
}

float BaseObject::getRotation() const
{
    return _rotation;
}

ax::Size BaseObject::getSize() const
{
    return ax::Size(_width, _height);
}

ax::Rect BaseObject::getBounds() const
{
    const float halfWidth  = _width * 0.5f;
    const float halfHeight = _height * 0.5f;
    float sinA = std::sin(_rotation * static_cast<float>(M_PI) / 180.0f);
    float cosA = std::cos(_rotation * static_cast<float>(M_PI) / 180.0f);

    ax::Vec2 corners[4] = {
        rotateVector(ax::Vec2(-halfWidth, -halfHeight), sinA, cosA) + _position,
        rotateVector(ax::Vec2(halfWidth, -halfHeight), sinA, cosA) + _position,
        rotateVector(ax::Vec2(halfWidth, halfHeight), sinA, cosA) + _position,
        rotateVector(ax::Vec2(-halfWidth, halfHeight), sinA, cosA) + _position,
    };

    float minX = corners[0].x;
    float maxX = corners[0].x;
    float minY = corners[0].y;
    float maxY = corners[0].y;
    for (int i = 1; i < 4; ++i)
    {
        minX = std::min(minX, corners[i].x);
        maxX = std::max(maxX, corners[i].x);
        minY = std::min(minY, corners[i].y);
        maxY = std::max(maxY, corners[i].y);
    }

    return ax::Rect(minX, minY, maxX - minX, maxY - minY);
}

bool BaseObject::containsPoint(const ax::Vec2& point) const
{
    if (_rotation == 0.0f)
    {
        return getBounds().containsPoint(point);
    }

    float sinA = std::sin(-_rotation * static_cast<float>(M_PI) / 180.0f);
    float cosA = std::cos(-_rotation * static_cast<float>(M_PI) / 180.0f);
    ax::Vec2 localPoint = rotateVector(point - _position, sinA, cosA);
    const float halfWidth  = _width * 0.5f;
    const float halfHeight = _height * 0.5f;
    return localPoint.x >= -halfWidth && localPoint.x <= halfWidth && localPoint.y >= -halfHeight && localPoint.y <= halfHeight;
}

bool BaseObject::hitTest(const ax::Vec2& point) const
{
    return _visible && containsPoint(point);
}

void BaseObject::getRotatedCorners(ax::Vec2 corners[4]) const
{
    const float halfWidth  = _width * 0.5f;
    const float halfHeight = _height * 0.5f;
    float sinA = std::sin(_rotation * static_cast<float>(M_PI) / 180.0f);
    float cosA = std::cos(_rotation * static_cast<float>(M_PI) / 180.0f);

    corners[0] = rotateVector(ax::Vec2(-halfWidth, -halfHeight), sinA, cosA) + _position;
    corners[1] = rotateVector(ax::Vec2(halfWidth, -halfHeight), sinA, cosA) + _position;
    corners[2] = rotateVector(ax::Vec2(halfWidth, halfHeight), sinA, cosA) + _position;
    corners[3] = rotateVector(ax::Vec2(-halfWidth, halfHeight), sinA, cosA) + _position;
}

bool BaseObject::intersects(const BaseObject& other) const
{
    ax::Vec2 aCorners[4];
    ax::Vec2 bCorners[4];
    getRotatedCorners(aCorners);
    other.getRotatedCorners(bCorners);

    for (int i = 0; i < 4; ++i)
    {
        ax::Vec2 edge = aCorners[(i + 1) % 4] - aCorners[i];
        ax::Vec2 axis(-edge.y, edge.x);
        if (!overlapOnAxis(axis, aCorners, bCorners))
            return false;
    }

    for (int i = 0; i < 4; ++i)
    {
        ax::Vec2 edge = bCorners[(i + 1) % 4] - bCorners[i];
        ax::Vec2 axis(-edge.y, edge.x);
        if (!overlapOnAxis(axis, aCorners, bCorners))
            return false;
    }

    return true;
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
