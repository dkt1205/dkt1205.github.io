#include"BulletObject.hpp"

BulletObject::BulletObject() {
	x_val_ = y_val_ = 0;
	is_move_ = 0;
	rect_.x = rect_.y = 0;
	rect_.w = 29.1;
	rect_.h = 50;
}
BulletObject::~BulletObject() {

}

void BulletObject::HandleInputAction(SDL_Event events, SDL_Renderer *ren) {}

void BulletObject::HandleMove(const int x_border, const int y_border) {
    rect_.y-=22;
    if (rect_.y < y_border - rect_.h ){
        is_move_ = false;
    }
}



