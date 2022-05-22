#include"EnemyDeath.hpp"

EnemyDeath::EnemyDeath(){
    rect_.w = 204;
    rect_.h = 153;
    // 8 Texture enemy death
    rectTexture[0].x = 0;
    rectTexture[0].y = 0;
    rectTexture[0].w = 204;
    rectTexture[0].h = 153;

    rectTexture[1].x = 204;
    rectTexture[1].y = 0;
    rectTexture[1].w = 204;
    rectTexture[1].h = 153;

    rectTexture[2].x = 204*2 ;
    rectTexture[2].y = 0;
    rectTexture[2].w = 204;
    rectTexture[2].h = 153;

    rectTexture[3].x = 204*3;
    rectTexture[3].y = 0;
    rectTexture[3].w = 204;
    rectTexture[3].h = 153;

    rectTexture[4].x = 204*4 ;
    rectTexture[4].y = 0;
    rectTexture[4].w = 204;
    rectTexture[4].h = 153;

    rectTexture[5].x = 204*5 ;
    rectTexture[5].y = 0;
    rectTexture[5].w = 204;
    rectTexture[5].h = 153;

    rectTexture[6].x = 204*6;
    rectTexture[6].y = 0;
    rectTexture[6].w = 204;
    rectTexture[6].h = 153;

    rectTexture[7].x = 204*7;
    rectTexture[7].y = 0;
    rectTexture[7].w = 204;
    rectTexture[7].h = 153;
}
void EnemyDeath::ShowAnimation(SDL_Renderer* ren){
    //đổi vị trí để show lên màn hình cho khớp ( tại ảnh không đồng bộ )
    if (frame_count_==0) {
        rect_.x-=(204-80.2162)/2;
        rect_.y-=(153-140)/2;
        rect_.y+=12;
    }
    SDL_RenderCopy(ren, full_object_, &rectTexture[frame_count_], &rect_);
    SDL_RenderPresent(ren);
};
void EnemyDeath::HandleAnimation()
{
     frame_count_++;
     cout << " frame = " << frame_count_ <<endl;
     if ( frame_count_==9 ){
        is_shown_ = 0;
     }
};
