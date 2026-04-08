#include "Core/Square.h"

Square::Square(const ax::Vec2& position, float size, const ax::Color4F& color)
: BaseObject(position, size, size)
, _color(color)
, _node(nullptr)
{
}

Square::~Square()
{
    if (_node && _node->getParent())
    {
        _node->removeFromParent();
    }
}

void Square::setPosition(const ax::Vec2& position)
{
    BaseObject::setPosition(position);
    if (_node)
    {
        _node->setPosition(_position);
    }
}

void Square::setColor(const ax::Color4F& color)
{
    _color = color;
    refresh();
}

const ax::Color4F& Square::getColor() const
{
    return _color;
}

void Square::draw(ax::Node* parent)
{
    if (!_node)
    {
        _node = ax::DrawNode::create();
        parent->addChild(_node);
    }
    refresh();
    _node->setPosition(_position);
}

void Square::update(float /*delta*/)
{
}

ax::DrawNode* Square::getDrawNode() const
{
    return _node;
}

void Square::refresh()
{
    if (!_node)
        return;

    _node->clear();
    float halfSize = _width * 0.5f;
    _node->drawSolidRect(ax::Vec2(-halfSize, -halfSize), ax::Vec2(halfSize, halfSize), _color);
    _node->setPosition(_position);
}
