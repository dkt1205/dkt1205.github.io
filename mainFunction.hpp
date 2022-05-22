#ifndef MAINFUNCTION_H_
#define MAINFUNCTION_H_

#include"General_Function.hpp"
#include"LTexture.hpp"
#include"MainObject.hpp"
#include"BulletObject.hpp"
#include"ThreatObject.hpp"
#include"EnemyBullet.hpp"
#include"EnemyDeath.hpp"
#include"BonusObject.hpp"
#include"BossObject.hpp"
#include"BossDeath.hpp"
#include"BossBullet.hpp"
#include"GameText.hpp"

#include<thread>
#include<chrono>

bool init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		g_Window = SDL_CreateWindow("Combat Flight Simulator", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
		g_renderer = SDL_CreateRenderer(g_Window, -1, SDL_RENDERER_ACCELERATED );

		if (g_renderer!= NULL)
		{
			SDL_SetRenderDrawColor(g_renderer, 255 , 255, 255, 255);
			int imgFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imgFlags) & imgFlags))
			{
				cout<<"SDL_image could not initialize! SDL_image Error: "<< IMG_GetError()<<endl;
				return 0;
			}
			if ( Mix_OpenAudio(22050,MIX_DEFAULT_FORMAT,2,4096) == -1 ){
                cout<< " Mix_OpenAudio didn't work !! " <<endl;
                return 0;
			}

            g_deploy_missile = Mix_LoadMUS("m_deploy_missile.mp3");
            g_main_injured = Mix_LoadWAV("m_main_injured.mp3");
            g_end_music = Mix_LoadWAV("game_over.mp3");
            g_enemy_death = Mix_LoadWAV("m_enemydeath.mp3");
            g_bk_music = Mix_LoadWAV("background_music.mp3");
            g_through_gate = Mix_LoadWAV("intro_music.mp3");
            g_get_item = Mix_LoadWAV("m_get_item.mp3");
            g_success_get_item = Mix_LoadWAV("success_elegant.mp3");
            g_main_death = Mix_LoadWAV("main_death.mp3");
            g_bonus_boss = Mix_LoadWAV("bonus_boss.mp3");
            g_success_killboss=Mix_LoadWAV("success_killboss.mp3");
            g_boss_appear=Mix_LoadWAV("boss_appear.mp3");
            g_boss_death=Mix_LoadWAV("boss_death.mp3");
            if ( g_deploy_missile == NULL || g_enemy_death == NULL || g_main_injured == NULL || g_end_music== NULL || g_main_death==NULL || g_boss_appear==NULL || g_boss_death==NULL||
                g_bk_music == NULL || g_get_item == NULL || g_success_get_item == NULL || g_through_gate == NULL ||g_bonus_boss==NULL ||g_success_killboss==NULL) {
                cout << Mix_GetError() << endl;
                return 0;
            }

            // Init TTF and load TTF (gFont)
            if( TTF_Init() == -1 )
            {
                printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
            gFont = TTF_OpenFont( "JosefinSans-SemiBold.ttf", 33 ); //33 la font chu

            if( gFont == NULL )
            {
                printf( "Failed to load JosefinSans font (TTF)! SDL_ttf Error: %s\n", TTF_GetError() );
                return false;
            }
			return 1;
		}
		else
			return 0;
	}
	else
        return 0;
}

void InitIntroAndEnd(LTexture &intro, LTexture &pressS, LTexture &gModulatedTexture)
{
    intro.loadFromFile("intro.png");
	pressS.loadFromFile("pressStoPlay.png") ;
	gModulatedTexture.loadFromFile( "game_over.png" ) ;
    gModulatedTexture.setColor(0,0,0);
    intro.setColor(255,255,255);
    pressS.setColor(255,255,255);
}

void ShowThreatsList(vector<ThreatObject*> ThreatsList)
{
    for(int i=0;i<ThreatsList.size();i++)
    {
        if (ThreatsList[i]->GetIsMove())
        {
            ThreatsList[i]->ShowAnimation(g_renderer);
        }
    }
}
;

void InitializeMainObject(MainObject &mainObj)
{
    mainObj.LoadDeathImg("mainDeath.png", g_renderer);
	mainObj.LoadImg("aircraftSpriteSheet.png", g_renderer);
	mainObj.LoadInjuredImg("main_injured.png",g_renderer);
	mainObj.ShowAnimation(g_renderer);
} ;

void InitializeBossAndBossDeathList( vector<BossObject*> &BossList, vector <BossDeath*> &BossDeathList)
{
    for(int i=0;i<MAX_NUMBER_OF_BOSS ;i++)
    {
        BossList.push_back(new BossObject(g_renderer));
        BossList[BossList.size()-1]->LoadImg("boss.png",g_renderer);
        BossDeathList.push_back(new BossDeath);
        BossDeathList[BossDeathList.size()-1]->LoadImg("bossdeath.png",g_renderer);
    }
} ;

void MakeABossDeath(vector<BossDeath*> BossDeathList,BossObject *&boss)
{
    for (int i=0;i<BossDeathList.size();i++)
    {
        if ( !BossDeathList[i]->GetIsShown() )
        {
            cout << "Boss Death made!" << endl;
            BossDeathList[i]->SetIsShown(true);
            BossDeathList[i]->SetRect(boss->GetRect().x + -30 , boss->GetRect().y + -35 );
            BossDeathList[i]->ShowAnimation(g_renderer);
            break;
        }
    }
}

void CreateAndInitAndPutThreatInList(vector<ThreatObject*> &ThreatsList)
{
    ThreatsList.push_back(new ThreatObject);
    ThreatsList[ThreatsList.size()-1]->LoadImg("enemySpriteSheet.png",g_renderer);
    ThreatsList[ThreatsList.size()-1]->ShowAnimation(g_renderer);
    ThreatsList[ThreatsList.size()-1]->GenerateBullet(g_renderer);
} ;

void CreateAndInitAndPutEnemyDeathInList( vector<EnemyDeath*> &EnemyDeathList,ThreatObject* threat )
{
    EnemyDeathList.push_back(new EnemyDeath);
    EnemyDeathList[EnemyDeathList.size()-1]->LoadImg("enemydeath.png",g_renderer);
    EnemyDeathList[EnemyDeathList.size()-1]->SetRect( threat->GetRect().x , threat->GetRect().y );
    EnemyDeathList[EnemyDeathList.size()-1]->ShowAnimation(g_renderer);
}

void MakeABoss(vector<BossObject*> &BossList,GameText &Score)
{
    for (int i=0;i<BossList.size();i++)
    {
        if ( !BossList[i]->GetIsMove() )
            if (Score.GetValue()>= SCORE_WHICH_BOSS_SHOWN && rand()%50 == 1 ) {
                Mix_PlayChannel(-1,g_boss_appear,0);
                MAX_NUMBER_OF_ENEMY=12;
                BossList[i]->Fresh();
                break;
            }
            else MAX_NUMBER_OF_ENEMY=8;
    }
};

void ShowBossList(const vector<BossObject*> &BossList)
{
    for (int i=0;i<BossList.size();i++)
        if (BossList[i]->GetIsMove())
            BossList[i]->ShowAnimation(g_renderer);
}

void ManageBossListWithMainOjectAndBossDeathList(vector<BossObject*> &BossList, MainObject &MyAirPlane,
                                                  vector <BossDeath*> &BossDeathList, GameText &Score )
{
    for (int i=0;i< BossList.size() ;i++)
    {
        if (BossList[i]->GetIsMove())
        {
            vector <BulletObject*> main_bullet_list;
            main_bullet_list = MyAirPlane.GetBulletList();

            if (rand()%10 == 1)  BossList[i]->HandleMove(SCREEN_WIDTH , SCREEN_HEIGHT );
            if (rand()%5  == 1)  BossList[i]->GenerateBullet(g_renderer);

            if (SDL_General::Do_two_objects_overlap(BossList[i]->GetRect(),MyAirPlane.GetRect())) {
                MyAirPlane.DecreaseLives();
                Mix_PlayChannel(-1,g_enemy_death,0);
            }
            BossList[i]->ControlBulletAndKillMainObject(SCREEN_WIDTH , SCREEN_HEIGHT,
                                                        g_renderer , MyAirPlane, g_main_injured, Score);

            // Tim xem co enemy nao chet ko ?
            for (int j=0; j < main_bullet_list.size() ; j++ ) {
                // Neu co vien dan  nao ban trung dich thi: xoa dich, xoa dan cua minh, hien thi vu no
                if ( SDL_General::Do_two_objects_overlap( main_bullet_list[j]->GetRect() , BossList[i]->GetRect() ) )
                {
                    BossList[i]->DecreaseLives();
                    if (BossList[i]->GetLives()<= 0) {
                        // update score :
                        Score.IncreaseValue(KILL_BOSS_SCORE) ;
                        MyAirPlane.IncreaseLives(LIVES_PLUS_FOR_KILL_BOSS);
                        // phat am thanh boss no: boss nổ
                        Mix_PlayChannel(-1,g_boss_death,0);
                        // tao ra 1 enemy death = vu no.
                        MakeABossDeath(BossDeathList,BossList[i]);
                        BossList[i]->SetIsMove(false);
                    }
                    delete main_bullet_list[j];
                    main_bullet_list.erase(main_bullet_list.begin()+j);
                    MyAirPlane.SetBulletList(main_bullet_list);
                }
            }
        }
    }
}
void ManageThreatsListWithMainOjectAndEnemyDeathList(vector<ThreatObject*> &ThreatsList, MainObject &MyAirPlane,
                                                     vector <EnemyDeath*> &EnemyDeathList, GameText &Score)

{
    for (int i=0;i< ThreatsList.size() ;i++)
    {
        if (ThreatsList[i]->GetIsMove())
        {
            vector <BulletObject*> main_bullet_list;
            main_bullet_list = MyAirPlane.GetBulletList();

            if (rand()%3 == 1)  ThreatsList[i]->HandleMove(SCREEN_WIDTH , SCREEN_HEIGHT );
            if (rand()%15 == 1) ThreatsList[i]->GenerateBullet(g_renderer);
            if (SDL_General::Do_two_objects_overlap(ThreatsList[i]->GetRect(),MyAirPlane.GetRect())) {
                MyAirPlane.DecreaseLives();
                Mix_PlayChannel(-1,g_enemy_death,0);
                CreateAndInitAndPutEnemyDeathInList(EnemyDeathList,ThreatsList[i]);
                delete ThreatsList[i];
                ThreatsList.erase(ThreatsList.begin()+i);
                break;
            }
            ThreatsList[i]->ControlBulletAndKillMainObject(SCREEN_WIDTH , SCREEN_HEIGHT,
                                                           g_renderer , MyAirPlane, g_main_injured, Score );
            // Tim xem co enemy nao chet ko ?
            for (int j=0; j < main_bullet_list.size() ; j++ ) { // xet tat ca cac vien dan cua nhan vat chinh
                // Neu co vien dan  nao ban trung dich thi: xoa dich, xoa dan cua minh, show vu no cua dich
                if ( SDL_General::Do_main_bullet_overlap_enemy( main_bullet_list[j]->GetRect() , ThreatsList[i]->GetRect() ) )
                {
                    // phat am thanh enemy no:
                    Mix_PlayChannel(-1,g_enemy_death,0);
                    // update score :
                    Score.IncreaseValue(KILL_ENEMY_SCORE) ;
                    // tao ra 1 enemy death = vu no
                    CreateAndInitAndPutEnemyDeathInList(EnemyDeathList,ThreatsList[i]);
                    delete ThreatsList[i];
                    ThreatsList.erase(ThreatsList.begin()+i);
                    delete main_bullet_list[j];
                    main_bullet_list.erase(main_bullet_list.begin()+j);
                    MyAirPlane.SetBulletList(main_bullet_list);
                }
            }
        }
        else {
            delete ThreatsList[i];
            ThreatsList.erase(ThreatsList.begin()+i);
            cout << " Threats number #" << i << " is deleted !" <<endl;
            cout << " ThreatsList.size() = " << ThreatsList.size() <<endl<<endl ;
        }
    }
}

void ManageBossDeathListAndMakeBonus( vector<BossDeath*> &BossDeathList , vector<BonusObject*> &BonusObjectList )
{
    for (int i=0; i<BossDeathList.size();i++ )
    {
        if (BossDeathList[i]->GetIsShown())
        {
            BossDeathList[i]->HandleAnimation();
        }
        if (BossDeathList[i]->ShowEnough())
        {
            Mix_PlayChannel(-1,g_success_killboss,0);
            BonusObjectList.push_back(new BonusObject);
            BonusObjectList[BonusObjectList.size()-1]->SetType(2);
            BonusObjectList[BonusObjectList.size()-1]->SetType(2);
            BonusObjectList[BonusObjectList.size()-1]->LoadImg("Bonus_killboss.png",g_renderer);
            BonusObjectList[BonusObjectList.size()-1]->SetRect(BossDeathList[i]->GetRect().x + BOSS_OBJECT_WIDTH/2 ,
                                                                BossDeathList[i]->GetRect().y + BOSS_OBJECT_HEIGHT/2);
        }
    }
}
void ManageEnemyDeathListAndMakeBonus(vector<EnemyDeath*> &EnemyDeathList,vector<BonusObject*> &BonusObjectList) {
    for ( int i=0 ;i < EnemyDeathList.size() ;i++ )
    {
        if ( EnemyDeathList[i]->GetIsShown() ){
            EnemyDeathList[i]->HandleAnimation();
        } else {
            if (rand()% 100 > 10) // ngẫu nhiên xuất hiện basic bonus khi tiêu diệt enemy
            {

                Mix_PlayChannel(-1,g_get_item,0);
                BonusObjectList.push_back(new BonusObject);
                BonusObjectList[BonusObjectList.size()-1]->SetType(1);
                srand(time(0));
                if(rand()%3==0) BonusObjectList[BonusObjectList.size()-1]->LoadImg("bonus_basicpoint0.png",g_renderer);
                else if(rand()%3==1) BonusObjectList[BonusObjectList.size()-1]->LoadImg("bonus_basicpoint1.png",g_renderer);
                else BonusObjectList[BonusObjectList.size()-1]->LoadImg("bonus_basicpoint.png",g_renderer);

                BonusObjectList[BonusObjectList.size()-1]->SetRect(EnemyDeathList[i]->GetRect().x + THREAT_OBJECT_WIDTH/2 ,
                                                                    EnemyDeathList[i]->GetRect().y + THREAT_OBJECT_HEIGHT/2);
                BonusObjectList[BonusObjectList.size()-1]->Show(g_renderer);
            }

            delete EnemyDeathList[i] ;
            EnemyDeathList.erase ( EnemyDeathList.begin() + i );
        }
    }
}

void ManageBonusObjectList( vector<BonusObject*> &BonusObjectList, MainObject &MyAirPlane, GameText &Score) {
    for (int i=0;i<BonusObjectList.size();i++)
    {
        if( BonusObjectList[i]->GetIsShown() ){
            // if main gets bonus object then it disappears
            if ( SDL_General::Do_two_objects_overlap(BonusObjectList[i]->GetRect(), MyAirPlane.GetRect()) )
            {
                //update score
                switch (BonusObjectList[i]->GetType())
                {
                    case 1:
                        Score.IncreaseValue(GET_BONUS_SCORE);
                        Mix_PlayChannel(-1,g_success_get_item,0); //bat am thanh khi an bonus thuong
                    break;
                    case 2:
                        Score.IncreaseValue(GET_BONUS_STAR_SCORE);
                        MyAirPlane.IncreaseLives(LIVES_PLUS_FOR_GET_STAR);
                        Mix_PlayChannel(-1,g_bonus_boss,0);       //bat am thanh khi an bonus boss
                    break;
                }
                delete BonusObjectList[i];
                BonusObjectList.erase(BonusObjectList.begin()+i);
            }
            else
            {
                BonusObjectList[i]->HandleCount();
            }
        } else {
            delete BonusObjectList[i];
            BonusObjectList.erase(BonusObjectList.begin()+i);
        }
    }
}
void ShowBossListThreatsListBonusListBossDeathThreatsDeath( vector<BossObject*> BossList,vector<ThreatObject*> ThreatsList,
                                                            vector<BonusObject*> BonusObjectList,vector<BossDeath*> BossDeathList,
                                                            vector<EnemyDeath*> EnemyDeathList)
{
    ShowBossList(BossList);
    ShowThreatsList(ThreatsList);
    for (int i=0;i<BonusObjectList.size();i++)
    {
        if( BonusObjectList[i]->GetIsShown() ){
                BonusObjectList[i]->Show(g_renderer);
        }
    }
    for (int i=0;i<BossDeathList.size();i++)
    {
        if(BossDeathList[i]->GetIsShown()) {
            BossDeathList[i]->ShowAnimation(g_renderer);
        }
    }
        for (int i=0;i<EnemyDeathList.size();i++)
    {
        if(EnemyDeathList[i]->GetIsShown()) {
            EnemyDeathList[i]->ShowAnimation(g_renderer);
        }
    }
}

bool PlayGame(){
    srand(time(0));
    bool is_quit = false;
    if (!init()){
        cout << "can't initialize SDL ! " << endl;
        return false;
    }
    rect_background.x = rect_background.y = 0; rect_background.w = SCREEN_WIDTH;  rect_background.h = SCREEN_HEIGHT;
	SDL_General::LoadBackGround(g_renderer) ;
    static SDL_Rect rectPress { rectPress.x = 35 ,  rectPress.y = 125 ,   rectPress.w = 480 , rectPress.h = 63.85  }  ; // vị trí, kích thước của Press_S
    static LTexture gModulatedTexture(g_renderer,rect_background), intro(g_renderer,rect_background), pressS(g_renderer, rectPress) ;

     // Introduce game : Game's name, rules.
    InitIntroAndEnd(intro,pressS,gModulatedTexture);

    int temp = 0,temp1=0;
    Mix_PlayChannel( -1,g_through_gate , 100 );
    while(!is_quit)
    {
            while (SDL_PollEvent(&g_even)!=0) {
                if (g_even.key.keysym.sym == SDLK_s)
                {
                    is_quit = true;
                }
            };
            if (is_quit) break;
            temp++;
            SDL_RenderClear(g_renderer) ;
            intro.setAlpha(temp);
            intro.render();
            SDL_RenderPresent( g_renderer );
            pressS.setAlpha(temp);
            pressS.render();
            SDL_RenderPresent( g_renderer );
            SDL_Delay(45);
            if(temp==255) break;
    };
    temp = 0;
     while(!is_quit)
    {
            while (SDL_PollEvent(&g_even)!=0) {
                if (g_even.key.keysym.sym == SDLK_s) {
                    is_quit = true;
                    break;
                }
            }
            if (is_quit) break;

            if (temp>=255) temp = -1;
            intro.render();
            SDL_RenderPresent( g_renderer );
            pressS.setAlpha(++temp);
            pressS.render();
            SDL_RenderPresent( g_renderer );
            SDL_Delay(25);
    };
    // declare objects in game :
	MainObject  MyAirPlane;
    vector<EnemyDeath*> EnemyDeathList ;
    vector<BonusObject*> BonusObjectList ;
    vector<ThreatObject*> ThreatsList ;
    vector<BossObject*> BossList ;
    vector<BossDeath*> BossDeathList ;
    GameText PlayerLives,Score;
    SDL_General::LoadBackGround(g_renderer);

    InitializeBossAndBossDeathList(BossList,BossDeathList);
	InitializeMainObject(MyAirPlane) ;
	PlayerLives.SetValue(LIVES);

	PlayerLives.SetRect(SCREEN_WIDTH-135,10);
	Score.SetRect(10,10);

    is_quit = false;
    Mix_HaltChannel(-1);
    Mix_PlayChannel( -1,g_bk_music , 100 );
	while (!is_quit)
    {
		while (SDL_PollEvent(&g_even)) {
			if (g_even.type == SDL_QUIT) {
				is_quit = true;
				break;
			}
			MyAirPlane.HandleInputAction(g_even, g_renderer, g_deploy_missile);
        }
        SDL_RenderClear(g_renderer) ;
        SDL_General::ShowBackGround(g_renderer);

        if (MyAirPlane.GetLives()>0 ) {MyAirPlane.ShowAnimation(g_renderer);
        ShowBossListThreatsListBonusListBossDeathThreatsDeath(BossList,ThreatsList,
                                                              BonusObjectList,BossDeathList,EnemyDeathList);
        }
        PlayerLives.ShowNum2(gFont,textColor,g_renderer);
        Score.ShowNum(gFont,textColor,g_renderer) ;

        if (MyAirPlane.GetLives()<=0)
        {
            if(temp1==0) {
                Mix_PlayChannel(-1,g_main_death,0);
                temp1++;
            }
            MyAirPlane.ShowDeath(g_renderer,is_quit);
            if (is_quit) break;
        }
        PlayerLives.SetValue(MyAirPlane.GetLives());
        if (MyAirPlane.GetLives()>0){
                MyAirPlane.HandleMove();
                MyAirPlane.ControlBullet(g_renderer);

            // Handle bonus object appear or disappear
            ManageBonusObjectList(BonusObjectList,MyAirPlane,Score);
            if ( rand()%50 == 1 ) CreateAndInitAndPutThreatInList(ThreatsList);
            MakeABoss(BossList,Score);
            // Handle main object vs threats list
            ManageThreatsListWithMainOjectAndEnemyDeathList(ThreatsList,MyAirPlane,EnemyDeathList,Score );
            ManageBossListWithMainOjectAndBossDeathList(BossList,MyAirPlane,BossDeathList,Score );
            // Handle EnemyDeathList : if there is an enemydeath which appeared enough then erasing it.
            ManageEnemyDeathListAndMakeBonus(EnemyDeathList,BonusObjectList);
            ManageBossDeathListAndMakeBonus(BossDeathList,BonusObjectList);
        }
        if (MyAirPlane.GetLives()<=0)
           SDL_Delay(94);
        else  SDL_Delay(29);
	}

	// End Game Information : Showing Game Over 3 times and shut down Game
    Mix_HaltChannel(-1);
    Mix_PlayChannel(-1, g_end_music ,0);
    int i=0,times=0;
    is_quit = false ;
    gModulatedTexture.setColor(161,44,27);
    Score.SetRect(400,75);
    while(times!=3)
    {
            while (SDL_PollEvent(&g_even)!=0) {
                    if (g_even.type == SDL_QUIT) is_quit = true;
            };
            if (is_quit) break;
            i=(i+1)%256;
            SDL_General::ShowBackGround(g_renderer);
            Score.ShowNum3(gFont,textColor,g_renderer);
            gModulatedTexture.setAlpha(i);
            gModulatedTexture.render();
            SDL_RenderPresent(g_renderer );
            SDL_Delay(30);
            if(i==255)times++;
    };
	SDL_General::CleanUp();
	SDL_Quit();
	return true;
}
;

#endif // MAINFUNCTION_H_
