#include"BossObject.hpp"

BossObject::BossObject(SDL_Renderer *ren)
{
    rect_.y = -BOSS_OBJECT_HEIGHT -5;
    rect_.x = SCREEN_WIDTH*15/100+ rand()% (SCREEN_WIDTH*7/10);
    rect_.w = BOSS_OBJECT_WIDTH;
    rect_.h = BOSS_OBJECT_HEIGHT;
    // Texture của boss
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

    rectTexture[7].x=506*7;
    rectTexture[7].y=0;
    rectTexture[7].w=506;
    rectTexture[7].h=356;

    rectTexture[8].x=506*8;
    rectTexture[8].y=0;
    rectTexture[8].w=506;
    rectTexture[8].h=356;

    rectTexture[9].x=0;
    rectTexture[9].y=356;
    rectTexture[9].w=506;
    rectTexture[9].h=356;

    rectTexture[10].x=506;
    rectTexture[10].y=356;
    rectTexture[10].w=506;
    rectTexture[10].h=356;

    rectTexture[11].x=506*2;
    rectTexture[11].y=356;
    rectTexture[11].w=506;
    rectTexture[11].h=356;

    rectTexture[12].x=506*3;
    rectTexture[12].y=356;
    rectTexture[12].w=506;
    rectTexture[12].h=356;

    rectTexture[13].x=506*4;
    rectTexture[13].y=356;
    rectTexture[13].w=506;
    rectTexture[13].h=356;

    rectTexture[14].x=506*5;
    rectTexture[14].y=356;
    rectTexture[14].w=506;
    rectTexture[14].h=356;

    rectTexture[15].x=506*6;
    rectTexture[15].y=0;
    rectTexture[15].w=506;
    rectTexture[15].h=356;

    rectTexture[16].x=506*7;
    rectTexture[16].y=0;
    rectTexture[16].w=506;
    rectTexture[16].h=356;

    for (int i=0;i<6;i++)
    {
         p_bullet_list.push_back(new BossBullet);
         p_bullet_list[p_bullet_list.size()-1]->LoadImg("bossbullet.png",ren);
    }

}
void BossObject::Fresh()
{
    SetRect( SCREEN_WIDTH*15/100+ rand()% (SCREEN_WIDTH*7/10), - BOSS_OBJECT_HEIGHT -5);
    is_move = true;
    lives = BOSS_MAX_LIVES ;
    for (int i=0;i<6;i++)
    {
         p_bullet_list[i]->SetIsMove(false);
    }
}

void BossObject::GenerateBullet(SDL_Renderer* ren)
{
    for(int i=0;i<p_bullet_list.size();i++)
    {
        if (!p_bullet_list[i]->GetIsMove())
        {
            if(rect_.y>=-BOSS_OBJECT_HEIGHT+2){
            p_bullet_list[i]->SetIsMove(true);
            p_bullet_list[i]->SetRect( rect_.x + BOSS_OBJECT_WIDTH/2-BOSS_BULLET_WIDTH/2 ,rect_.y + int(BOSS_OBJECT_HEIGHT*4/5)+3 ); //set vị trí khởi đầu đạn boss
            p_bullet_list[i]->ShowAnimation(ren);
            break;
            }
        }
    }
}

void BossObject::ControlBulletAndKillMainObject(int x, int y, SDL_Renderer* ren,
                                                  MainObject &main_object,Mix_Chunk* g_main_injured , GameText &Score) {

    for (int i=0;i <p_bullet_list.size();i++ ) {
        if (p_bullet_list[i]->GetIsMove())
        {
            if (SDL_General::Do_two_objects_overlap( p_bullet_list[i]->GetRect(), main_object.GetRect() ) )
            {
                // update score when injured
                Score.IncreaseValue(GET_INJURED_SCORE) ;
                // Play main_injured music.
                Mix_PlayChannel(-1,g_main_injured,0);

                main_object.SetIsShownInjured(true) ;
                main_object.ShowInjured(ren);
                main_object.DecreaseLives();

                p_bullet_list[i]->SetIsMove(false);
            }
            else
            {
                p_bullet_list[i]->ShowAnimation(ren);
                p_bullet_list[i]->HandleMove(x,y );
            }
        }
    }
}

void BossObject::HandleMove(const int x_border, const int y_border) {
    if ( rect_.y > y_border ) {
        is_move = false;
        }
    rect_.y+= BOSS_OBJECT_HEIGHT/18;
    if(rand()%2==0) rect_.x-=BOSS_OBJECT_WIDTH/11;
    else rect_.x+=BOSS_OBJECT_WIDTH/11;
}
void BossObject::ShowAnimation(SDL_Renderer* ren)
{
    SDL_RenderCopy(ren, full_object_, &rectTexture[frame], &rect_);
    SDL_RenderPresent(ren);
    frame = (frame+1)%17;
}




