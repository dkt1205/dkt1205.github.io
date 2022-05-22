#include"BonusObject.hpp"

BonusObject::BonusObject()
{
    rect_.w = BONUS_WIDTH ;
    rect_.h = BONUS_HEIGHT;
}
void BonusObject::SetType (int type)
{
    type_ = type;
    switch(type_)
    {
    case 1 :
        // bonus_basicpoint.png
        BONUS_HEIGHT = 65.34 ;
        BONUS_WIDTH = 66 ;
    break;
    case 2 :
        //Bonus_killboss.png
        BONUS_WIDTH= 98 ;
        BONUS_HEIGHT = 98 ;
    break;
    }
    rect_.w = BONUS_WIDTH ;
    rect_.h = BONUS_HEIGHT;
} ;

void BonusObject::HandleCount()
{
    count_++;
    if (count_ >= MAX_COUNT ) {
        is_shown_ = 0;
    }
} ;
