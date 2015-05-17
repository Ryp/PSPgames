#include "Mouse.h"
#include "Ressource.h"
#include "rules.h"

Mouse::Mouse()
{
  mousepic_ = Ressource::GetInstance()->mousepic_;
  mousepic_->x = SCREEN_WIDTH / 2;
  mousepic_->y = SCREEN_HEIGHT / 2;
}

Mouse::~Mouse() {}

int Mouse::getX()
{
  return mousepic_->x;
}

int Mouse::getY()
{
  return mousepic_->y;
}

void Mouse::update(OSL_CONTROLLER* pad)
{
  if (pad->held.circle) {
    mod_ = 2;
  } else {
    mod_ = 1;
  }
  mousepic_->x += (pad->analogX -(pad->analogX % 30)) / (30 / mod_);
  mousepic_->y += (pad->analogY -(pad->analogY % 30)) / (30 / mod_);
  if (pad->pressed.up) {
    mousepic_->y += -ARROW_SPEED * mod_;
  }
  if (pad->pressed.down) {
    mousepic_->y += ARROW_SPEED * mod_;
  }
  if (pad->pressed.left) {
    mousepic_->x += -ARROW_SPEED * mod_;
  }
  if (pad->pressed.right) {
    mousepic_->x += ARROW_SPEED * mod_;
  }
  if (mousepic_->x > 480) {
    mousepic_->x = 480;
  }
  if (mousepic_->x < 0) {
    mousepic_->x = 0;
  }
  if (mousepic_->y > 272) {
    mousepic_->y = 272;
  }
  if (mousepic_->y < 0) {
    mousepic_->y = 0;
  }
}

void Mouse::display()
{
  oslDrawImage(mousepic_);
}
