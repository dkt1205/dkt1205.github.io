#include"BossDeath.hpp"
#include"BossObject.hpp"
BossDeath::BossDeath(){
    rect_.w = BOSS_OBJECT_WIDTH;
    rect_.h = BOSS_OBJECT_HEIGHT;
    // 7 Texture của boss death
     rectTexture[0].x=0;
    rectTexture[0].y=0;
    rectTexture[0].w=506;
    rectTexture[0].h=356;

    rectTexture[1].x=506;
    rectTexture[1].y=0;
    rectTexture[1].w=506;
    rectTexture[1].h=356;

    rectTexture[2].x=506*2;
    rectTexture[2].y=0;
    rectTexture[2].w=506;
    rectTexture[2].h=356;

    rectTexture[3].x=506*3;
    rectTexture[3].y=0;
    rectTexture[3].w=506;
    rectTexture[3].h=356;

    rectTexture[4].x=506*4;
    rectTexture[4].y=0;
    rectTexture[4].w=506;
    rectTexture[4].h=356;

    rectTexture[5].x=506*5;
    rectTexture[5].y=0;
    rectTexture[5].w=506;
    rectTexture[5].h=356;

    rectTexture[6].x=506*6;
    rectTexture[6].y=0;
    rectTexture[6].w=506;
    rectTexture[6].h=356;
}
void BossDeath::ShowAnimation(SDL_Renderer* ren){
    SDL_RenderCopy(ren, full_object_, &rectTexture[frame_count_], &rect_);
    SDL_RenderPresent(ren);
};
bool BossDeath::ShowEnough() {
    return (frame_count_ >= 7) ;
}
void BossDeath::HandleAnimation()
{
     frame_count_++;
     if ( frame_count_== 8 ){
        is_shown_ = 0 ;
        frame_count_ = 0;
     }
};
