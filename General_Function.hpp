#ifndef General_Function_H_
#define General_Function_H_

#include<Windows.h>
#include<string>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>
#include<iostream>
#include<vector>
#include<cmath>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include"LTexture.hpp"

using namespace std;

const int BKGROUND_WIDTH = 1920;
const int BKGROUND_HEIGHT = 3240;
const int SCREEN_WIDTH = 1216;
const int SCREEN_HEIGHT = 684;
const int SCREEN_BPP = 32;
const int PIXEL = 6 ; // 6 la so PIXEL screen bi day xuong .
const int PIXEL_LIM = (2*BKGROUND_HEIGHT/3)%PIXEL ;
const int PIXEL_START = BKGROUND_HEIGHT/3 + (2*BKGROUND_HEIGHT/3)%PIXEL - PIXEL ;
static int MAX_NUMBER_OF_ENEMY = 4; // giới hạn max 4 địch
const int MAX_NUMBER_OF_BOSS = 1;
const SDL_Color textColor = {241, 117, 11};
const int KILL_ENEMY_SCORE = 5 ;
const int KILL_BOSS_SCORE = 20 ;
const int GET_BONUS_SCORE = 5 ;
const int GET_BONUS_STAR_SCORE = 10 ;
const int GET_INJURED_SCORE = -3 ;
const int SCORE_WHICH_BOSS_SHOWN =  100 ;
const int LIVES_PLUS_FOR_KILL_BOSS = 1;
const int LIVES_PLUS_FOR_GET_STAR = 1 ;

static SDL_Window* g_Window = NULL;
static SDL_Renderer *g_renderer = NULL;
static SDL_Texture *g_background = NULL;
static SDL_Texture *g_gameover = NULL;
static SDL_Texture *g_bkpicture = NULL;
static SDL_Texture *g_intro = NULL;
static SDL_Event g_even;
static SDL_Rect rect_background ;
static SDL_Rect rect_screen ;

//Globally used font
static TTF_Font *gFont = NULL;

static Mix_Music* g_deploy_missile = NULL;
static Mix_Chunk* g_enemy_death = NULL;
static Mix_Chunk* g_bk_music = NULL;
static Mix_Chunk* g_through_gate = NULL;
static Mix_Chunk* g_end_music = NULL;
static Mix_Chunk* g_enemy_bullet = NULL;
static Mix_Chunk* g_get_item  = NULL;
static Mix_Chunk* g_success_get_item = NULL ;
static Mix_Chunk* g_main_injured = NULL;
static Mix_Chunk* g_main_death = NULL;
static Mix_Chunk* g_bonus_boss = NULL;
static Mix_Chunk* g_success_killboss = NULL;
static Mix_Chunk* g_boss_appear = NULL;
static Mix_Chunk* g_boss_death = NULL;
namespace SDL_General
{
	SDL_Texture * LoadImage (string path, SDL_Renderer *ren);
	void ApplySurface(SDL_Renderer *renderer, SDL_Texture *src, int x, int y, int w, int h);
    void LoadIntro(SDL_Renderer* ren);
    void ShowIntro(SDL_Renderer* ren);
	void CleanUp();
	void LoadBackGround(SDL_Renderer* ren);
	void ShowBackGround(SDL_Renderer* ren);
	bool Do_main_bullet_overlap_enemy(SDL_Rect ob1, SDL_Rect ob2);
	bool Do_enemy_bullet_overlap_main_object(SDL_Rect ob1, SDL_Rect ob2);
	bool Do_two_objects_overlap(SDL_Rect ob1, SDL_Rect ob2);
}

#endif


