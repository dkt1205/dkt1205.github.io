#ifndef ENEMY_BULLET_H_
#define ENEMY_BULLET_H_

#include "BaseObject.hpp"

const double ENEMY_BULLET_WIDTH  = 12;
const double ENEMY_BULLET_HEIGHT = 12;

class EnemyBullet : public BaseObject
{
public:
	EnemyBullet();
	~EnemyBullet();
	void HandleMove( const int x_border, const int y_border );
	bool GetIsMove() { return is_move_; };
    void SetBulletType(int type){ bullet_type_ = type ;} ; // there are 3 bullet types: straight, left, right
    int GetBulletType(){ return bullet_type_;  } ;
private:
	bool is_move_=1 ;
	int bullet_type_= 0;
};
#endif // ENEMY_BULLET_H_
