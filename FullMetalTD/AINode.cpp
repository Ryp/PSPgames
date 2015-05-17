#include "AINode.h"

AINode::AINode()
{
  _is_blocked = false;
  _cost = NODE_DEFAULT_COST;
}

bool AINode::isBlocked() const
{
  return (_is_blocked);
}

void AINode::setBlocked(bool val)
{
  _is_blocked = val;
}

int AINode::getCost() const
{
  return (_cost);
}

void AINode::setCost(int val)
{
  _cost = val;
}
