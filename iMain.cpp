#include<bits/stdc++.h>
#include<windows.h>
#include<mmsystem.h>
using namespace std;
#include "iGraphics.h"
//Screen-size
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
//object movement poses
#define SPIDER_PHASE 6
#define FIRE_PHASE 5
#define COIN_PHASE 6
#define COMET_PHASE 6
#define SAKURA_RUN_POSE 6
#define SASUKE_FROG_PHASE 4
#define SASUKE_WAKE_PHASE 4
#define GHOST_PHASE 2
#define FW_NUM 10

//Define Modes
#define SCORE_PAGE -2
#define RULE_PAGE -1
#define HOME_PAGE 0
#define START_PAGE 1
#define COMET_MODE 2
#define NIGHT_MODE 3
#define CASTLE_MODE 4
#define FINAL_RESCUE 5
#define NAME_LEN 20


//int Phase=HOME_PAGE;
int Phase=HOME_PAGE;
//int Phase=CASTLE_MODE;
//int Phase=FINAL_RESCUE;

void reset();
bool Pause=true;

//Level change
void next_level();
bool Level=false;
char level_bg[20]="phase-5.bmp";
char level_button[20]="nxtlvl1.bmp";
char arrow[20]="arrow.bmp";

//Home-button related
int HomeX=40;
int HomeY=520;
char Home_button[20]="Home.bmp";
char Game_name[20]="game_name.bmp";
char ScoreButton[20]="scoreboard.bmp";
//bool home_selected=false;

//Start-button related
int startX=1000;
int startY=50;
char start_button[20]="Start.bmp";
//bool start_selected=false;

//Rule-button and Rule-page related
int RuleX=50;
int RuleY=50;
char rule_button[20]="Rules.bmp";
int ruleListX=500;
int ruleListY=40;
char Rule_page[20]="rulepage.bmp";
//char Rule_list[20]="rule_list.bmp";
//bool rule_selected=false;

//Score
char score_button[20]="button.bmp";
char score_bg[20]="score_bg.bmp";
char score_pic[20]="score_sakura.bmp";
char score_word[20]="score_written.bmp";
char filename[20]="Scores.txt";
int scoreX=1075;
int scoreY=530;
int score_textX=1100;
int score_textY=545;
int score=-1;
char name[NAME_LEN]="";
int name_ind=0;
void score_board();
char name1[NAME_LEN], name2[NAME_LEN], name3[NAME_LEN], name4[NAME_LEN];
int score1, score2, score3, score4;
char score1_str[20], score2_str[20], score3_str[20], score4_str[20];
bool scoring=false;
int final_score=0;

//Background related
int bgX=0;
int bgY=0;
char comet_bg[20]="bg_1.bmp";
char home_bg[20]="Menu_bg.bmp";
char castle_bg[20]="castle.bmp";
char rescue_bg[20]="jail.bmp";
char start_bg[20]="start_page.bmp";
char pause_bg[20]="pause.bmp";
char night_bg[20]="cherryblossom.bmp";
char win_bg[20]="win_bg.bmp";

//Sakura movement
//#define JUMP_LIMIT 200
int JUMP_LIMIT=150;
int SakuraWidth=100;
int SakuraHeight=100;
int SakuraX=0;
int SakuraY=140;
int SI=0;
char SakuraRun[SAKURA_RUN_POSE][20]= {"SakuraRun1.bmp","SakuraRun2.bmp","SakuraRun3.bmp","SakuraRun4.bmp","SakuraRun5.bmp","SakuraRun6.bmp"};
void SakuraMove();
char SakuraRunU[SAKURA_RUN_POSE][20]= {"SakuraRun1U.bmp","SakuraRun2U.bmp","SakuraRun3U.bmp","SakuraRun4U.bmp","SakuraRun5U.bmp","SakuraRun6U.bmp"};
char SakuraStandU[20]="SakuraStandingU.bmp";
char SakuraJumpU[2][20]= {"SakuraJumpUpU.bmp","SakuraJumpDownU.bmp"};
char SakuraFallU[20]="fallU.bmp";

//Sakura standing
char SakuraStand[20]="SakuraStanding.bmp";
bool Stand=true;
bool fail=false;

//Sakura jumping
char SakuraJump[2][20]= {"SakuraJumpUp.bmp","SakuraJumpDown.bmp"};
bool jump=false;
bool jumpUp=false;
bool jumpDown=false;
int SakuraJumpY=0;
void jumpChange();

//Sakura lying down
int i_down=0;
bool down=false;
int SakuraDownY=0;
char SakuraDown[20]="down.bmp";
void downChange();

//Sakura dead
char SakuraFall[20]="fall.bmp";
bool Alive=true;
char SakuraCut[20]="cut.bmp";
char SakuraFireDown[20]="fire_down.bmp";
void fall_down_in_the_fire();
bool falling=false; //last level
char SakuraGhostDie[20]="sakuraGhostDie.bmp";

//Finally
bool rescue=false;
char SakuraFinal[20]="sakuraRescue.bmp";

//Sasuke
int sasuke_i=0;
int sasukeX=1120;
int sasukeY=185;
int cageX=1120;
int cageY=sasukeY-10;
char Cage[20]="cage.bmp";
char sasukeFrog[SASUKE_FROG_PHASE][20]= {"sasukeFrog1.bmp","sasukeFrog2.bmp","sasukeFrog3.bmp","sasukeFrog4.bmp"};
void sasuke();
char sasukeWake[SASUKE_WAKE_PHASE][20]= {"sasukeWake1.bmp","sasukeWake2.bmp","sasukeWake3.bmp","sasukeWake4.bmp"};
int sasukeWake_i=0;
void sasukeWakeUp();

//fire-flame related (Comet mode)
int f=0;
char fire[FIRE_PHASE][20]= {"fire1.bmp","fire2.bmp","fire3.bmp","fire4.bmp","fire5.bmp"};
void fire_flow();

//Coin related
int c=0;
char coin[COIN_PHASE][20]= {"coin1.bmp","coin2.bmp","coin3.bmp","coin4.bmp","coin5.bmp","coin6.bmp"};
void coin_spin();
void eat_coin();
bool comet_coin1=true;
bool comet_coin2=true;
bool comet_coin3=true;
char score_str[20];

//Spider related (castle mode)
int spi=0;
int ShuX=1200;
int ShuY=130;
char spider[SPIDER_PHASE][20]= {"spider1.bmp","spider2.bmp","spider3.bmp","spider4.bmp","spider5.bmp","spider6.bmp"};
int spiY[SPIDER_PHASE]= {0,20,40,60,40,20};
void spider_dance();

//Comet related (Comet Mode)
int com_c=0;
int ComX[COMET_PHASE],ComY[COMET_PHASE];
char comet[COMET_PHASE][20]= {"comet.bmp","cometb.bmp","comet.bmp","cometb.bmp","comet.bmp","cometb.bmp"};
void setComet();
void cometChange();
void hitCometCheck();

//extra life
int lifeX,lifeY;
char life_power[20]="life.bmp";
void setLife();
void lifeChange();
void getlife();
int life_count=0;
char life_sym[20]="life_c.bmp";
char life_str[10];
bool lose_life=false;
char dead[20]="die.bmp";
void saved_with_life();
bool again=false;

//Kick related (Night mode)
bool kick=false;
int i_kick=0;
void kickChange();
char sakuraKick[20]="sakuraKick.bmp";
void kickSound();
char kickPower[20]="kickpower.bmp";
bool kicking=false;
void getKickPower();
void changeKickPower();
void setKickPower();
int kickX=0;
int kickY=700;
char kick_button[20]="kick_power.bmp";

//Ghost -Night Mode
void ghost();
int gh=0;
char ghosts[GHOST_PHASE][20]= {"ghost1.bmp","ghost2.bmp"};
void hitGhostCheck();
int g1=10, g2=10, g3=10;
void ghost_fly();
bool ghost1=true, ghost2=true, ghost3=true;

//Shuriken related (Castle mode)
int shurikenSpeed=15;
char shuriken[20]="shuriken.bmp";
void shurikenChange();
void hitShurikenCheck();
void eat_shuriken();

//Key
int num_keys=0;
void key_fall();
void take_key();
struct key
{
    int kx;
    int ky;
    char key_pic[20];
    bool taken;
};
struct key k1= {60,530,"key1.bmp",false};
struct key k2= {690,340,"key2.bmp",false};
struct key k3= {750,330,"key3.bmp",false};
struct key k4= {970,380,"key4.bmp",false};

//Win case
bool win=false;
int winX=830;
int winY=300;
//char winBanner[20]="win.bmp";
void afterWin();

//Lost
int gOverX=300;
int gOverY=150;
char gOver[20]="gameoverSakura.bmp";
void gameOver();
bool over=false;
char gOp[20]="gameoverpic.bmp";
char failed[20]="fail.bmp";

//Sounds
char Jump_Sound[20]="jump_sound.wav";
char Bg_Sound[20]="bg_sound.wav";
char Game_Over[20]="lose_life.wav";
char coin_sound[20]="coin_sound.wav";
char Win[20]="win.wav";
char ghostFly[20]="ghost_fly.wav";
char kick_sound[20]="kick.wav";
bool sound=true;
int sound_i=0;
char soundButton[2][20]= {"sound_yes.bmp", "sound_no.bmp"};
char keySound[20]="Key.wav";
char loseLife[20]="loseLife.wav";
char shurikenFlow[20]="flow.wav";
char getLifeSound[20]="getlife.wav";
char getKickPowerSound[20]="kickpower.wav";

//Die ways
bool die_comet=false;
bool die_fire=false;
bool die_firefall=false;
bool die_ghost=false;
bool die_shuriken=false;

//fireworks
char fw1[FW_NUM][20]= {"fw1_1.bmp","fw1_2.bmp","fw1_3.bmp","fw1_4.bmp","fw1_5.bmp","fw1_6.bmp","fw1_7.bmp","fw1_8.bmp","fw1_9.bmp","fw1_10.bmp"};
char fw2[FW_NUM][20]= {"fw2_1.bmp","fw2_2.bmp","fw2_3.bmp","fw2_4.bmp","fw2_5.bmp","fw2_6.bmp","fw2_7.bmp","fw2_8.bmp","fw2_9.bmp","fw2_10.bmp"};
char fw3[FW_NUM][20]= {"fw3_1.bmp","fw3_2.bmp","fw3_3.bmp","fw3_4.bmp","fw3_5.bmp","fw3_6.bmp","fw3_7.bmp","fw3_8.bmp","fw3_9.bmp","fw3_10.bmp"};
int fw1x,fw1y;
int fw2x,fw2y;
int fw3x,fw3y;
int fw_i=FW_NUM;
void fwSet();

//iSetTimer issue
void time_10();
void time_20();
void time_100();
void time_200();
void time_300();
void time_400();

//code starts here
void iDraw()
{
    iClear();
    if(Phase==SCORE_PAGE)
    {
        iShowBMP(bgX, bgY, score_bg);
//        iShowBMP2(bgX, bgY, score_pic, 0);
        iShowBMP2(HomeX,HomeY,Home_button,0);
        iShowBMP2(ruleListX-25, ruleListY+300, score_word, 0);
        iSetColor(255,255,255);
        iText(ruleListX, ruleListY+200, name1, GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(score1, score1_str, 10);
        iText(ruleListX+350, ruleListY+200, score1_str, GLUT_BITMAP_TIMES_ROMAN_24);
        iText(ruleListX, ruleListY+150, name2, GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(score2, score2_str, 10);
        iText(ruleListX+350, ruleListY+150, score2_str, GLUT_BITMAP_TIMES_ROMAN_24);
        iText(ruleListX, ruleListY+100, name3, GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(score3, score3_str, 10);
        iText(ruleListX+350, ruleListY+100, score3_str, GLUT_BITMAP_TIMES_ROMAN_24);
        iText(ruleListX, ruleListY+50, name4, GLUT_BITMAP_TIMES_ROMAN_24);
        itoa(score4, score4_str, 10);
        iText(ruleListX+350, ruleListY+50, score4_str, GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if(Phase==RULE_PAGE)
    {
        iShowBMP(bgX,bgY,Rule_page); //Rule Page Background
        iShowBMP(HomeX,HomeY,Home_button);
//        iShowBMP2(ruleListX,ruleListY,Rule_list,0);
        iSetColor(215,215,215);
        iText(ruleListX, ruleListY+510, "Rules:", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(ruleListX, ruleListY+470, "Read Carefully!", GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP(ruleListX, ruleListY+385,"r.bmp");
        iText(ruleListX, ruleListY+400, "        >> Resume", GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP(ruleListX, ruleListY+335,"p.bmp");
        iText(ruleListX, ruleListY+350, "        >> Pause", GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP(ruleListX, ruleListY+285,"RA.bmp");
        iText(ruleListX, ruleListY+300, "        >> Move forward", GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP(ruleListX, ruleListY+235,"UA.bmp");
        iText(ruleListX, ruleListY+250, "        >> Jump", GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP(ruleListX, ruleListY+185,"DA.bmp");
        iText(ruleListX, ruleListY+200, "        >> Lie down", GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP(ruleListX, ruleListY+135,"k.bmp");
        iText(ruleListX, ruleListY+150, "        >> Kick", GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP(ruleListX, ruleListY+85,"end.bmp");
        iText(ruleListX, ruleListY+100, "        >> Exit", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(ruleListX, ruleListY+35, "Remember, you cannot turn back", GLUT_BITMAP_TIMES_ROMAN_24);
        iText(ruleListX, ruleListY, "If you get killed, and run out of extra life,the game is over.", GLUT_BITMAP_TIMES_ROMAN_24);
//        iText(ruleListX, ruleListY+50, "9. You can restart a level with an extra life, but with some cost", GLUT_BITMAP_TIMES_ROMAN_24);
//        iText(ruleListX, ruleListY+40, "10. Extra life will cost you no more than 2000 points.", GLUT_BITMAP_TIMES_ROMAN_24);
//        iShowBMP(ruleListX+85, ruleListY-10,"end.bmp");
//        iText(ruleListX, ruleListY, "9. Press         to exit", GLUT_BITMAP_TIMES_ROMAN_24);
    }
    if(Phase==HOME_PAGE)
    {
        iShowBMP(bgX,bgY,home_bg);
        iShowBMP(startX,startY+460,ScoreButton);
        iShowBMP(RuleX,RuleY,rule_button);
        iShowBMP(startX,startY,start_button);
//        Alive=true;
//        Stand=true;
        iShowBMP2(RuleX-30,startY+450,soundButton[sound_i],0);
    }
    if(Phase==START_PAGE)
    {
        iShowBMP(0,0,start_bg);
        iSetColor(189,183,107);
        iText(400, 470, "Enter Your name here:", GLUT_BITMAP_TIMES_ROMAN_24);
        iFilledRectangle(400, 400, 400, 50);
        iSetColor(0,0,0);
        iText(410, 415, name, GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP(HomeX,HomeY,Home_button);
        iShowBMP2(startX,startY,start_button,0);
    }
    if(Phase==COMET_MODE)
    {
        iShowBMP(bgX,bgY,comet_bg); //for background image
        if(Alive && !win)
        {
            if(jump) //in jump phase
            {
//                if(jumpUp) iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJump[0],0);
//                else iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJump[1],0);
                if(!kicking)
                {
                    if(jumpUp)

                    {
                        iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJump[0],0);
                    }
                    else
                    {
                        iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJump[1],0);

                    }
                }
                else
                {
                    if(jumpUp)
                    {
                        iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJumpU[0],0);
                    }
                    else
                    {
                        iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJumpU[1],0);
                    }
                }
            }
            else //non-jump phase
            {
                if(!Stand && SakuraX+SakuraWidth<SCREEN_WIDTH)
                {
                    if(!kicking)
                    {
                        iShowBMP2(SakuraX,SakuraY,SakuraRun[SI],0); //Running phase
                    }
                    else
                    {
                        iShowBMP2(SakuraX,SakuraY,SakuraRunU[SI],0);
                    }
                }
                else
                {
                    if(!kicking)
                    {
                        iShowBMP2(SakuraX,SakuraY,SakuraStand,0); //Stand phase
                    }
                    else
                    {
                        iShowBMP2(SakuraX,SakuraY,SakuraStandU,0); //Stand phase
                    }
                }
            }
//            iShowBMP2(ComX[com_c],ComY[com_c],comet[com_c],0); //Comets
        }
        else
        {
            if(!win)
            {
                if(!kicking)
                {
                    iShowBMP2(SakuraX,SakuraY-20,SakuraFall,0);
                }
                else
                {
                    iShowBMP2(SakuraX,SakuraY-20,SakuraFallU,0);
                }
//                iShowBMP2(gOverX,gOverY,gOver,0);
//                gameOver();
            }
            Stand=false;
        }
        iShowBMP2(ComX[com_c],ComY[com_c],comet[com_c],0); //Comets
        if(!kicking)
        {
            iShowBMP2(kickX,kickY, kickPower,0); //kickPower
        }
        if(win)
        {
            Stand=true;
            Alive=true;
            if(!kicking)
            {
                iShowBMP2(SakuraX,SakuraY,SakuraStand,0); //Stand phase
            }
            else
            {
                iShowBMP2(SakuraX,SakuraY,SakuraStandU,0); //Stand phase
            }
//            iShowBMP2(winX,winY,winBanner,0);
            win=true;
        }
        iShowBMP2(200,40,fire[f],0); //for fire flame
        iShowBMP2(560,40,fire[(f+2)%5],0); //for fire flame
        iShowBMP2(930,40,fire[(f+4)%5],0); //for fire flame
        if(comet_coin1)
        {
            iShowBMP2(200,240,coin[c],0); //for coin spin
        }
        if(comet_coin2)
        {
            iShowBMP2(560,240,coin[c],0); //for coin spin
        }
        if(comet_coin3)
        {
            iShowBMP2(930,240,coin[c],0); //for coin spin
        }
        if((win || !Alive)&&!lose_life)
        {
            itoa(final_score, score_str, 10);
        }
        else
        {
            itoa(score, score_str, 10);
        }
        iShowBMP2(scoreX, scoreY, score_button, 0);
        if(kicking)
        {
            iShowBMP2(scoreX-50, scoreY+10, kick_button, 0);
        }
        iSetColor(0,0,0);
        iText(score_textX,score_textY, score_str, GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(scoreX+10,scoreY-50,life_sym,0); //life
        itoa(life_count, life_str, 10); //life
        iSetColor(255,255,255); //life
        iText(scoreX+60,scoreY-40, life_str, GLUT_BITMAP_TIMES_ROMAN_24); //life
        iShowBMP(HomeX,HomeY,Home_button);
    }
    if(Phase==NIGHT_MODE)
    {
        iShowBMP(bgX,bgY,night_bg); //for background image
        iShowBMP2(200,g1,ghosts[gh],0); //for ghost
        iShowBMP2(560,g2,ghosts[gh],0); //for ghost
        iShowBMP2(930,g3,ghosts[gh],0); //for ghost
        if(Alive && !win)
        {
            if(jump) //in jump phase
            {
                if(jumpUp) iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJump[0],0);
                else iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJump[1],0);
            }
            else if(kick) //in down phase
            {
                iShowBMP2(SakuraX,50,sakuraKick,0);
            }
            else //non-jump phase
            {
                if(!Stand && SakuraX+SakuraWidth<SCREEN_WIDTH)
                {
                    iShowBMP2(SakuraX,SakuraY,SakuraRun[SI],0); //Running phase
                }
                else
                {
                    iShowBMP2(SakuraX,SakuraY,SakuraStand,0); //Stand phase
                }
            }
        }
        else
        {
            if(!win)
            {
                iShowBMP2(SakuraX,SakuraY,SakuraGhostDie,0);
//                iShowBMP2(gOverX,gOverY,gOver,0);
//                gameOver();
            }
            Stand=false;
        }
        iShowBMP2(lifeX,lifeY,life_power,0); //lives
        if(win)
        {
            Stand=true;
            Alive=true;
            iShowBMP2(SakuraX,SakuraY,SakuraStand,0);
//            iShowBMP2(winX,winY,winBanner,0);
            win=true;
        }
//        iShowBMP2(HomeX,HomeY,Home_button,0);
        iShowBMP2(scoreX, scoreY, score_button, 0);
        if(kicking)
        {
            iShowBMP2(scoreX-50, scoreY+10, kick_button, 0);
        }
        if((win || !Alive)&&!lose_life)
        {
            itoa(final_score, score_str, 10);
        }
        else
        {
            itoa(score, score_str, 10);
        }
        iSetColor(0,0,0);
        iText(score_textX,score_textY, score_str, GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(scoreX+10,scoreY-50,life_sym,0); //life
        itoa(life_count, life_str, 10); //life
        iSetColor(255,255,255); //life
        iText(scoreX+60,scoreY-40, life_str, GLUT_BITMAP_TIMES_ROMAN_24); //life
        iShowBMP(HomeX,HomeY,Home_button);
    }
    if(Phase==CASTLE_MODE)
    {
        iShowBMP(bgX,bgY,castle_bg); //for background image
        if(Alive && !win)
        {
            if(down) //in down phase
            {
                iShowBMP2(SakuraX,100,SakuraDown,0);
            }
            else //non-down phase
            {
                if(!Stand && SakuraX+100<SCREEN_WIDTH)
                {
                    iShowBMP2(SakuraX,100,SakuraRun[SI],0); //Running phase
                }
                else
                {
                    iShowBMP2(SakuraX,100,SakuraStand,0); //Stand phase
                }
            }
            iShowBMP2(ShuX,ShuY,shuriken,0);
        }
        else
        {
            if(!win)
            {
                iShowBMP2(SakuraX,100,SakuraCut,0);
                iShowBMP2(ShuX,ShuY,shuriken,0);
//                iShowBMP2(gOverX,gOverY,gOver,0);
            }
            Stand=false;
        }
        if(win)
        {
            Stand=true;
            Alive=true;
            iShowBMP2(SakuraX,100,SakuraStand,0);
//            iShowBMP2(winX,winY,winBanner,0);
            win=true;
        }
        iShowBMP2(60,330+spiY[spi],spider[spi],0); //spiders
        iShowBMP2(690,340+spiY[spi],spider[spi],0); //spiders
        iShowBMP2(750,330+spiY[(spi+4)%6],spider[(spi+4)%6],0); //spiders
        iShowBMP2(970,180+spiY[(spi+2)%6],spider[(spi+2)%6],0); //spiders
//        iShowBMP2(k1.kx,k1.ky,k1.key_pic,0); //key1
        if(!k2.taken)
        {

            iShowBMP2(k2.kx,k2.ky,k2.key_pic,0); //ke2
        }
        else
        {
            iShowBMP2(scoreX,scoreY-100,k2.key_pic,0); //ke2 taken
        }
//        iShowBMP2(k3.kx,k3.ky,k3.key_pic,0); //key3
        if(!k4.taken)
        {
            iShowBMP2(k4.kx,k4.ky,k4.key_pic,0); //key4
        }
        else
        {
            iShowBMP2(scoreX+50,scoreY-100,k4.key_pic,0); //key4
        }
//        iShowBMP2(HomeX,HomeY,Home_button,0);
        iShowBMP2(scoreX, scoreY, score_button, 0);
        if((win || !Alive)&&!lose_life)
        {
            itoa(final_score, score_str, 10);
        }
        else
        {
            itoa(score, score_str, 10);
        }
        iSetColor(0,0,0);
        iText(score_textX,score_textY, score_str, GLUT_BITMAP_TIMES_ROMAN_24);
        iShowBMP2(scoreX+10,scoreY-50,life_sym,0); //life
        itoa(life_count, life_str, 10); //life
        iSetColor(255,255,255); //life
        iText(scoreX+60,scoreY-40, life_str, GLUT_BITMAP_TIMES_ROMAN_24); //life
        iShowBMP(HomeX,HomeY,Home_button);
    }
    if(Phase==FINAL_RESCUE)
    {
        iShowBMP(bgX,bgY,rescue_bg); //for background image
        if(Alive && !win && !rescue)
        {
            if(jump) //in jump phase
            {
                if(jumpUp) iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJump[0],0);
                else iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJump[1],0);
            }
//            else if(down) //in down phase
//            {
//                iShowBMP2(SakuraX,SakuraY,SakuraDown,0);
//            }
            else if(falling)
            {
                iShowBMP2(SakuraX,SakuraY,SakuraFall,0);
            }
            else //non-down phase
            {
                if(!Stand && SakuraX+100<SCREEN_WIDTH)
                {
                    iShowBMP2(SakuraX,SakuraY,SakuraRun[SI],0); //Running phase
                }
                else
                {
                    iShowBMP2(SakuraX,SakuraY,SakuraStand,0); //Stand phase
                }
            }
            iShowBMP2(sasukeX,sasukeY,sasukeFrog[sasuke_i],0);
            iShowBMP2(cageX,cageY,Cage,0);
            if(k2.taken)
            {
                iShowBMP2(scoreX,scoreY-100,k2.key_pic,0); //ke2 taken
            }
//        iShowBMP2(k3.kx,k3.ky,k3.key_pic,0); //key3
            if(k4.taken)
            {
                iShowBMP2(scoreX+50,scoreY-100,k4.key_pic,0); //key4
            }
        }
        else if(rescue)
        {
            if (!win)
            {
                iShowBMP2(SakuraX,SakuraY,SakuraFinal,0);
                iShowBMP2(cageX,cageY,Cage,0);
            }
            if(sasukeWake_i==3)
            {
                iShowBMP2(cageX,cageY,Cage,0);
            }
            iShowBMP2(sasukeX-20,sasukeY-10,sasukeWake[sasukeWake_i],0);
            if(sasukeWake_i<3)
            {
                iShowBMP2(cageX,cageY,Cage,0);
            }
        }
        else
        {
            if(!win)
            {
                if(fail)
                {
                    iShowBMP2(SakuraX,SakuraY,SakuraStand,0);
                }
                else
                {
                    iShowBMP2(SakuraX,SakuraY,SakuraFireDown,0);
                }
//                iShowBMP2(gOverX,gOverY,gOver,0);
                iShowBMP2(sasukeX,sasukeY,sasukeFrog[sasuke_i],0);
                iShowBMP2(cageX,cageY,Cage,0);
            }
            Stand=false;
        }
        if(win)
        {
            Stand=true;
            Alive=true;
            iShowBMP2(SakuraX,SakuraY,SakuraStand,0);
            iShowBMP(300,150,win_bg);
//            iShowBMP2(winX,winY,winBanner,0);
            win=true;
        }
//        iShowBMP2(HomeX,HomeY,Home_button,0);
        score_str[0]='\0';
//        if((win || !Alive || rescue)&& !lose_life)
//        {
//            if(final_score>0)
//            {
//                itoa(final_score, score_str, 10);
//            }
//        }
//        else
//        {
//            if(score>0)
//            {
//                itoa(score, score_str, 10);
//            }
//        }
        if(score>=0)
        {
            itoa(score, score_str, 10);
        }
        else
        {
            itoa(final_score, score_str, 10);
        }
        if(!win)
        {
            iShowBMP2(scoreX, scoreY, score_button, 0);
            iSetColor(0,0,0);
            iText(score_textX,score_textY, score_str, GLUT_BITMAP_TIMES_ROMAN_24);
            iShowBMP2(scoreX+10,scoreY-50,life_sym,0); //life
            itoa(life_count, life_str, 10); //life
            iSetColor(255,255,255); //life
            iText(scoreX+60,scoreY-40, life_str, GLUT_BITMAP_TIMES_ROMAN_24); //life
        }
        else
        {
            iShowBMP2(scoreX, scoreY, score_button, 0);
            iSetColor(0,0,0);
            iText(score_textX,score_textY, score_str, GLUT_BITMAP_TIMES_ROMAN_24);
//            iSetColor(195,195,195);
//            iText(860,50, "Your Score:", GLUT_BITMAP_TIMES_ROMAN_24);
//            iText(980,50, score_str, GLUT_BITMAP_TIMES_ROMAN_24);
        }
        iShowBMP(HomeX,HomeY,Home_button);
    }
    if(Pause && Phase>=2 && !Level)
    {
//        iSetColor(255,255,255);
//        iFilledRectangle(480, 330, 230, 100);
        iShowBMP2(450, 50, pause_bg,0);
//        iSetColor(0,0,0);
//        iText(525,400, "Game Paused", GLUT_BITMAP_TIMES_ROMAN_24);
//        iText(500,350, "Press R to continue", GLUT_BITMAP_TIMES_ROMAN_24);
//        iShowBMP(HomeX,HomeY,Home_button);
    }
    if(Phase!=HOME_PAGE)
    {
        if(Level)
        {
            iShowBMP(bgX,bgY,level_bg);
            if(Phase==COMET_MODE)
            {
                iSetColor(195,195,195);
//                iFilledRectangle(950,200,200,450);
                iText(900, 400, "Avoid the comets.", GLUT_BITMAP_TIMES_ROMAN_24);
                iText(900, 350, "Jump to avoid fire.", GLUT_BITMAP_TIMES_ROMAN_24);
                iText(900, 300, "Catch the coins", GLUT_BITMAP_TIMES_ROMAN_24);
                iText(900, 270, "to increase your point.", GLUT_BITMAP_TIMES_ROMAN_24);
                iText(900, 220, "Catch the power-key.", GLUT_BITMAP_TIMES_ROMAN_24);
            }
            else
            {
                if(!again)
                {
                    iShowBMP2(875,475,level_button,0);
                }
                if(Phase==NIGHT_MODE)
                {
                    iSetColor(195,195,195);
                    if(kicking)
                    {
                        iText(900, 400, "Kick the ghosts", GLUT_BITMAP_TIMES_ROMAN_24);
                        iText(900, 350, "You may jump over them", GLUT_BITMAP_TIMES_ROMAN_24);
                        iText(900, 320, "but you won't get score", GLUT_BITMAP_TIMES_ROMAN_24);
                    }
                    else
                    {
                        iText(900, 400, "You don't have kick power", GLUT_BITMAP_TIMES_ROMAN_24);
                        iText(900, 350, "So, jump over the ghosts", GLUT_BITMAP_TIMES_ROMAN_24);
                        iText(900, 320, "but you won't get score", GLUT_BITMAP_TIMES_ROMAN_24);
                    }
                    iText(900, 270, "Catch extra lives", GLUT_BITMAP_TIMES_ROMAN_24);
                }
                if(Phase==CASTLE_MODE)
                {
                    iSetColor(195,195,195);
                    iText(900, 400, "Get down to avoid shurikens", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(900, 350, "Get at least one key", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(900, 320, "to save your friend", GLUT_BITMAP_TIMES_ROMAN_24);
                }
                if(Phase==FINAL_RESCUE)
                {
                    iSetColor(195,195,195);
                    iText(900, 400, "Jump over the obstacles", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(900, 350, "Do not fall into the fire", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(900, 300, "Reach your friend", GLUT_BITMAP_TIMES_ROMAN_24);
                    iText(900, 270, "to unlock the cage", GLUT_BITMAP_TIMES_ROMAN_24);
                }
            }

            iShowBMP2(1000,50,arrow,0);
            iShowBMP(HomeX,HomeY,Home_button);
        }
        if(over)
        {
            if(lose_life)
            {
                iShowBMP(gOverX, gOverY, dead);
            }
            else if(fail)
            {
                iShowBMP(gOverX,gOverY,failed);
                iSetColor(0,0,0);
                iText(score_textX,score_textY, "0", GLUT_BITMAP_TIMES_ROMAN_24);
            }
            else
            {
                iShowBMP(gOverX,gOverY,gOver);
//        iShowBMP(30,200,gOp);
            }
            iShowBMP(HomeX,HomeY,Home_button);
//        iSetColor(0,0,0);
//        iText(150,50, "Your Score:", GLUT_BITMAP_TIMES_ROMAN_24);
//        iText(275,50, score_str, GLUT_BITMAP_TIMES_ROMAN_24);
        }
//    if(lose_life)
//    {
//        iShowBMP(300, 150, dead);
//    }
    }
    if(win)
    {
        iShowBMP2(fw1x-(fw_i+1)*10,fw1y-(fw_i+1)*10,fw1[fw_i],0);
        iShowBMP2(fw2x-(fw_i+1)*10,fw2y-(fw_i+1)*10,fw2[fw_i],0);
        iShowBMP2(fw3x-(fw_i+1)*10,fw3y-(fw_i+1)*10,fw3[fw_i],0);
    }
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);
        if(Phase!=HOME_PAGE && mx>40 && mx<140 && my>520 && my<558)
        {
            Phase=HOME_PAGE;
            reset();
        }
        else if(Level && mx>1000 && mx<1150 && my>50 && my<125)
        {
            Level=false;
            again=false;
//            lose_life=false;
//            Pause=true;
//            Pause=false;
        }
        else if(lose_life && mx>300+445 && mx<300+510 && my>150+38 && my<150+54)
        {
            Level=true;
//            lose_life=false;
            Pause=true;
            next_level();
            life_count--;
            if(score>2000)
            {
                score-=2000;
            }
            else
            {
                score=0;
            }
//            Pause=false;
        }
        else if(Phase==HOME_PAGE && mx>1000 && mx<1150 && my>50 && my<105)
        {
            Phase=START_PAGE;
        }
        else if(Phase==START_PAGE && mx>1000 && mx<1150 && my>50 && my<105)
        {
            if(name[0])
            {
                Phase=COMET_MODE;
                Level=true;
            }
        }
        else if(Phase==HOME_PAGE && mx>50 && mx<200 && my>50 && my<105)
        {
            Phase=RULE_PAGE;
        }
        else if(Phase==HOME_PAGE && mx>RuleX-30 && mx<RuleX+40 && my>startY+450 && my<startY+520)
        {
            sound_i=(sound_i+1)%2;
            if(sound)
            {
                sound=false;
            }
            else
            {
                sound=true;
            }
        }
//        iShowBMP(startX,startY+460,ScoreButton);
        else if(Phase==HOME_PAGE && mx>startX && mx<startX+150 && my>startY+460 && my<startY+520)
        {
            Phase=SCORE_PAGE;
        }
    }
    if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
    }
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
    if(Phase==START_PAGE)
    {
        if(name_ind<NAME_LEN-1)
        {
            if(key=='\b')
            {
                if(name_ind>0)
                {
                    name_ind--;
                }
                name[name_ind]='\0';
            }
            else if (key==' '||(key>='a'&&key<='z')||(key>='A'&&key<='Z'))
            {
                name[name_ind]=key;
                name[++name_ind]='\0';

            }
        }
        else
        {
            if(key=='\b')
            {
                if(name_ind>0)
                {
                    name_ind--;
                }
                name[name_ind]='\0';
            }
        }
    }
    if(Phase>=COMET_MODE && Alive && !win)
    {
        if(key=='r' || key=='R')
        {
            if(!Level)
            {
                Pause=false;
            }
        }
        else if(key=='p' || key=='P')
        {
            Pause=true;
        }
    }
    if(Phase==NIGHT_MODE && Alive && !win && kicking)
    {
        if(key=='k' || key=='K')
        {
            kick=true;
        }
    }
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

    if(key==GLUT_KEY_END)
    {
        exit(0);
    }
    if(key==GLUT_KEY_LEFT)
    {
        Stand=true;
    }
    if(key==GLUT_KEY_RIGHT) //Sakura runs
    {
        SakuraMove();
    }
    if(key==GLUT_KEY_UP) //Sakura jumps
    {
        if(!jump && !Pause)
        {
            jump=true;
            jumpUp=true;
        }
    }
    if(key==GLUT_KEY_DOWN)
    {
        if(!down && !Pause)
        {
            down=true;
        }
    }
}


//My functions

void fwSet()
{
    if(fw_i<FW_NUM-1)
    {
        fw_i++;
    }
    else
    {
        fw1x=rand()%1000+100;
        fw1y=rand()%500+50;
        fw2x=rand()%1000+100;
        fw2y=rand()%500+50;
        fw3x=rand()%1000+100;
        fw3y=rand()%500+50;
        fw_i=0;
    }
}

void reset()
{
    score_board();
    SakuraX=0;
    SakuraY=50;
    JUMP_LIMIT=150;
    win=false;
    Alive=true;
    jump=false;
    down=false;
    rescue=false;
    name[0]='\0';
    name_ind=0;
    score=0;
    over=false;
    Stand=true;
    falling=false;
    comet_coin1=true;
    comet_coin2=true;
    comet_coin3=true;
    Pause=true;
    ShuX=1200;
    ShuY=130;
    kick=false;
    g1=10;
    g2=10;
    g3=10;
    ghost1=true;
    ghost2=true;
    ghost3=true;
    num_keys=0;
    setComet();
    k1.ky=330;
    k2.ky=530;
    k3.ky=330;
    k4.ky=380;
    k2.taken=false;
    k4.taken=false;
    life_count=1;
    setLife();
    lose_life=false;
    again=false;
    kicking=false;
    setKickPower();
}

//Next level
void next_level()
{
    Pause=true;
    Level=true;
    SakuraX=0;
    if(Phase==FINAL_RESCUE)
    {
        SakuraY=140;
    }
    else
    {
        SakuraY=50;
    }
    if(Phase!=COMET_MODE)
    {
        JUMP_LIMIT=200;
    }
    else
    {
        JUMP_LIMIT=150;
    }
    Stand=true;
    win=false;
    Alive=true;
    jump=false;
    down=false;
    rescue=false;
    over=false;
    falling=false;
    if(!lose_life)
    {
        score+=1000;
    }
    kick=false;
    setComet();
    setLife();
    setKickPower();
    ShuY=130;
    ShuX=1200;
    ghost1=true;
    ghost2=true;
    ghost3=true;
    comet_coin1=true;
    comet_coin2=true;
    comet_coin3=true;
    g1=10;
    g2=10;
    g3=10;
    if(lose_life && Phase==CASTLE_MODE)
    {
        k1.ky=330;
        k2.ky=530;
        k3.ky=330;
        k4.ky=380;
        k2.taken=false;
        k4.taken=false;
    }
    lose_life=false;
    if(Phase==COMET_MODE)
    {
        kicking=false;
    }
}

void SakuraMove()
{
    if(Alive && (Phase==CASTLE_MODE || Phase==COMET_MODE || Phase==NIGHT_MODE) && !Pause)
    {
        if(SakuraX+100<SCREEN_WIDTH)
        {
            hitCometCheck();
            Stand=false;
            SakuraX+=10;
            SI++;
            if(SI>=SAKURA_RUN_POSE)
            {
                SI=0;
            }
        }
        else
        {
            Phase++;
            next_level();
        }
    }
    if(Alive && Phase==FINAL_RESCUE && !Pause)
    {
        if (SakuraX>=110 && SakuraY+SakuraJumpY<215 && SakuraX<120) //cage on the floor
        {
            Stand=true;
        }
        else if(SakuraX>=210 && SakuraY+SakuraJumpY<250 && SakuraX<220) //first brick wall
        {
            Stand=true;
        }
        else if(SakuraX+150<SCREEN_WIDTH && Alive && !falling)
        {
            Stand=false;
            SakuraX+=10;
            SI=(SI+1)%SAKURA_RUN_POSE;
        }
        else if(SCREEN_WIDTH-SakuraX<=150 && SakuraY==175)
        {
            if(k2.taken || k4.taken)
            {
                rescue=true;
            }
            else
            {
                gameOver();
            }
        }
    }
}

void jumpChange()
{
    if(jump && Phase>=COMET_MODE && !Pause) //in jump phase
    {
        if(jumpUp) //when jumps up
        {
            SakuraJumpY+=5;
            if(SakuraJumpY<=5)
            {
                if(sound)
                {
                    PlaySound(Jump_Sound, NULL, SND_ASYNC);
                }
            }
            if(SakuraJumpY>=JUMP_LIMIT) //Cannot jump up beyond the limit
            {
                jumpUp=false;
            }
        }
        else //now jumps down
        {
            SakuraJumpY-=5;
            if(Phase==FINAL_RESCUE)
            {
                if(SakuraX>110)
                {
                    if(SakuraJumpY<80)
                    {
                        jump=false;
                        SakuraY=215;
                        if(SakuraX<160)
                        {
                            SakuraX=160;
                        }
                        Stand=true;
                        SakuraJumpY=0;
                    }
                }
                if(SakuraX>210)
                {
                    if(SakuraJumpY<110)
                    {
                        jump=false;
                        SakuraY=250;
                        if(SakuraX<260)
                        {
                            SakuraX=260;
                        }
                        Stand=true;
                        SakuraJumpY=0;
                    }
                }
                if(SakuraX>640)
                {
                    if(SakuraJumpY<10)
                    {
                        jump=false;
                        SakuraY=215;
                        if(SakuraX<670)
                        {
                            SakuraX=670;
                        }
                        Stand=true;
                        SakuraJumpY=0;
                    }
                }
                if(SakuraX>840)
                {
                    if(SakuraJumpY<10)
                    {
                        jump=false;
                        SakuraY=140;
                        if(SakuraX<860)
                        {
                            SakuraX=860;
                        }
                        Stand=true;
                        SakuraJumpY=0;
                    }
                }
                if(SakuraX>990)
                {
                    if(SakuraJumpY<10)
                    {
                        jump=false;
                        SakuraY=175;
                        if(SakuraX<970)
                        {
                            SakuraX=970;
                        }
                        Stand=true;
                        SakuraJumpY=0;
                    }
                }
                else
                {
                    if(SakuraJumpY<0)
                    {
                        jump=false;
                        SakuraJumpY=0;
                    }
                }
            }
            if(SakuraJumpY<0)
            {
                jump=false;
                SakuraJumpY=0;
            }
        }
    }
}

void fall_down_in_the_fire()
{
    if(Phase==FINAL_RESCUE)
    {
        if(SakuraX>=520 && SakuraY+SakuraJumpY<=250 && SakuraX<=640)
        {
            SakuraY-=10;
            jump=false;
            falling=true;
            if(SakuraX<560)
            {
                SakuraX+=10;
            }
            if(SakuraY<40)
            {
                if(life_count>0)
                {
                    lose_life=true;
                    saved_with_life();
                    Phase==FINAL_RESCUE;
//                    SakuraY=140;
                }
                else
                {
                    Alive=false;
                    falling=false;
                    SakuraY=30;
                    gameOver();
                }
            }
        }
        else if(SakuraX>=770 && SakuraY+SakuraJumpY<=215 && SakuraX<=840)
        {
            SakuraY-=10;
            jump=false;
            falling=true;
            if(SakuraX<560)
            {
                SakuraX+=10;
            }
            if(SakuraY<40)
            {
                if(life_count>0)
                {
                    lose_life=true;
                    saved_with_life();
                    Phase==FINAL_RESCUE;
//                    SakuraY=140;
                }
                else
                {
                    Alive=false;
                    falling=false;
                    SakuraY=30;
                    gameOver();
                }
            }
        }
        else if(SakuraX>=920 && SakuraY+SakuraJumpY<=215 && SakuraX<=990)
        {
            SakuraY-=10;
            jump=false;
            falling=true;
            if(SakuraX<560)
            {
                SakuraX+=10;
            }
            if(SakuraY<40)
            {
                if(life_count>0)
                {
                    lose_life=true;
                    saved_with_life();
                    Phase==FINAL_RESCUE;
//                    SakuraY=140;
                }
                else
                {
                    Alive=false;
                    falling=false;
                    SakuraY=30;
                    gameOver();
                }
            }
        }
    }
}

void downChange()
{
    if(down)
    {
//        if(i_down<=5 && sound)
//        {
//            kickSound();
//        }
        i_down++;
        if(i_down>25)
        {
//            kickSound();
            down=false;
            i_down=0;
        }
    }
}

void kickChange()
{
    if(kick)
    {
        i_kick++;
        if(i_kick>25)
        {
            kick=false;
            i_kick=0;
        }
    }
}

void cometChange()
{
    if(Phase==COMET_MODE)
    {
        if(ComY[com_c]>-100)
        {
            if(!Pause && Alive)
            {
                ComY[com_c]-=20;
            }
        }
        else
        {
            ComY[com_c]=700;
            com_c=(com_c+1)%COMET_PHASE;
            ComX[com_c]=rand()%1000+100;
        }
    }
}

void setComet()
{
    for(int i=0; i<COMET_PHASE; i++)
    {
        ComX[i]=rand()%1000+200;
        ComY[i]=700;
    }

}

void hitCometCheck()
{
    if(Phase==COMET_MODE)
    {
        if(abs(SakuraX-ComX[com_c])<30 && abs(ComY[com_c]-(SakuraY+SakuraJumpY))<=100)
        {
            if(life_count>0)
            {
                lose_life=true;
                saved_with_life();
//                next_level();
                Phase==COMET_MODE;
            }
            else
            {
                Alive=false;
                SakuraY=50;
                setComet();;
                gameOver();
            }
        }
        else if((SakuraJumpY<50)&&((SakuraX>=150&&SakuraX<225)||(SakuraX>=510&&SakuraX<585)||(SakuraX>=880&&SakuraX<955)))
        {
            if(life_count>0)
            {
                lose_life=true;
//                next_level();
                saved_with_life();
                Phase==COMET_MODE;
            }
            else
            {
                Alive=false;
                SakuraY=50;
                gameOver();
            }
        }
    }
}

void setLife()
{
    lifeX=rand()%1000+100;
    lifeY=700;
}

void lifeChange()
{
    if(Phase==NIGHT_MODE)
    {
        if(lifeY>-50)
        {
            if(!Pause && Alive)
            {
                lifeY-=10;
            }
        }
        else
        {
            lifeY=700;
            lifeX=rand()%1000+100;
        }
    }
}

void getlife()
{
    if(Phase==NIGHT_MODE && Alive)
    {
        if(abs(SakuraX-lifeX)<50 && abs(lifeY-(SakuraY+SakuraJumpY))<50)
        {
            life_count++;
            setLife();
            if(sound)
            {
                PlaySound(getLifeSound, NULL, SND_ASYNC);
            }
        }
    }
}

void setKickPower()
{
    kickX=rand()%1000+100;
    kickY=700;
}

void changeKickPower()
{
    if(Phase==COMET_MODE)
    {
        if(kickY>=0)
        {
            if(!Pause && Alive && !kicking)
            {
                kickY-=15;
            }
        }
        else
        {
            kickY=700;
            kickX=rand()%1000+100;
        }
    }
}

void getKickPower()
{
    if(Phase==COMET_MODE && Alive)
    {
        if(abs(SakuraX-kickX)<50 && abs(kickY-(SakuraY+SakuraJumpY))<50)
        {
            kicking=true;
            JUMP_LIMIT=200;
            setKickPower();
            if(sound)
            {
                PlaySound(getKickPowerSound, NULL, SND_ASYNC);
            }
        }
    }
}

void hitGhostCheck()
{
    if(Phase==NIGHT_MODE && !Pause)
    {
        if(SakuraJumpY<140)
        {
            if(SakuraX>=190&&SakuraX<225 && ghost1)
            {
                if(life_count>0)
                {
                    SakuraY=10;
                    lose_life=true;
                    saved_with_life();
                    Phase==NIGHT_MODE;
                }
                else
                {
                    Alive=false;
                    SakuraY=10;
                    gameOver();
                }
            }
            if (SakuraX>=550&&SakuraX<585 && ghost2)
            {
                if(life_count>0)
                {
                    SakuraY=10;
                    lose_life=true;
                    saved_with_life();
                    Phase==NIGHT_MODE;
                }
                else
                {
                    Alive=false;
                    SakuraY=10;
                    gameOver();
                }
            }
            if(SakuraX>=920&&SakuraX<955 && ghost3)
            {
                if(life_count>0)
                {
                    SakuraY=10;
                    lose_life=true;
                    saved_with_life();
                    Phase==NIGHT_MODE;
                }
                else
                {
                    Alive=false;
                    SakuraY=10;
                    gameOver();
                }
            }
        }
    }
}

void kick_ghost()
{
    if(Phase==NIGHT_MODE && kick)
    {
        if(SakuraY+SakuraJumpY<140)
        {
            if(SakuraX>=140 && SakuraX<225)
            {
                if(ghost1)
                {
                    ghost1=false;
                    score+=100;
                }
                if(sound)
                {
                    PlaySound(ghostFly, NULL, SND_ASYNC);
                }
            }
            else if(SakuraX>=500 && SakuraX<585)
            {
                if(ghost2)
                {
                    ghost2=false;
                    score+=100;
                }
                if(sound)
                {
                    PlaySound(ghostFly, NULL, SND_ASYNC);
                }
            }
            else if(SakuraX>=870 && SakuraX<955)
            {
                if(ghost3)
                {
                    ghost3=false;
                    score+=100;
                }
                if(sound)
                {
                    PlaySound(ghostFly, NULL, SND_ASYNC);
                }
            }
        }
    }
}

void eat_coin()
{
    if(Phase==COMET_MODE)
    {
        if(SakuraY+SakuraJumpY>150 && SakuraY+SakuraJumpY<240)
        {
            if(SakuraX>100 && SakuraX<200)
            {
                if(comet_coin1)
                {
                    if(sound)
                    {
                        PlaySound(coin_sound, NULL, SND_ASYNC);
                    }
                    score+=100;
                    comet_coin1=false;
                }
            }
            else if(SakuraX>510 && SakuraX<610)
            {
                if(comet_coin2)
                {
                    if(sound)
                    {
                        PlaySound(coin_sound, NULL, SND_ASYNC);
                    }
                    score+=100;
                    comet_coin2=false;
                }
            }
            else if(SakuraX>880 && SakuraX<980)
            {
                if(comet_coin3)
                {
                    if(sound)
                    {
                        PlaySound(coin_sound, NULL, SND_ASYNC);
                    }
                    score+=100;
                    comet_coin3=false;
                }
            }
        }
    }
}

void key_fall()
{
//    if(!k1.taken)
//    {
//        if(k1.kx-SakuraX<100 && k1.ky>=50)
//        {
//            k1.ky-=10;
//        }
//    }
    if(!k2.taken && Phase==CASTLE_MODE)
    {
        if(k2.kx-SakuraX<100 && k2.ky>=100)
        {
            k2.ky-=10;
        }
    }
//    if(!k3.taken)
//    {
//        if(k3.kx-SakuraX<100 && k3.ky>=50)
//        {
//            k3.ky-=10;
//        }
//    }
    if(!k4.taken && Phase==CASTLE_MODE)
    {
        if(k4.kx-SakuraX<100 && k4.ky>=100)
        {
            k4.ky-=10;
        }
    }
}

void take_key()
{
    if(abs(k2.kx-SakuraX)<=25 && abs(k2.ky-SakuraY)<=50 && !k2.taken && Phase==CASTLE_MODE)
    {
        k2.taken=true;
        score+=500;
        num_keys++;
        if(sound)
        {
            PlaySound(keySound, NULL, SND_ASYNC);
        }
    }
    else if(abs(k4.kx-SakuraX)<=25 && abs(k4.ky-SakuraY)<=50 && !k4.taken && Phase==CASTLE_MODE)
    {
        k4.taken=true;
        score+=500;
        num_keys++;
        if(sound)
        {
            PlaySound(keySound, NULL, SND_ASYNC);
        }
    }
}

void shurikenChange()
{
    if(Phase==CASTLE_MODE && !Pause)
    {
        if(ShuX-SakuraX<50 && ShuX>SakuraX && !down) //Sakura dies by shuriken
        {
//            Alive=false;
//            down=false;
        }
        else if(ShuX>0 && ShuX>0 && Alive)
        {
            ShuX-=shurikenSpeed;
        }
        else
        {
            if(Alive)
            {
                ShuY=130;
                ShuX=1200;
            }
        }
    }
}

void hitShurikenCheck()
{
    if(Phase==CASTLE_MODE && ShuX-SakuraX<50 && ShuX>SakuraX && !down)
    {
        if(life_count>0)
        {
            lose_life=true;
            saved_with_life();
            Phase==CASTLE_MODE;
        }
        else
        {
            Alive=false;
            down=false;
            gameOver();
        }
//        PlaySound(Game_Over, NULL, SND_ASYNC);
    }
}

//spiders are for attraction
void spider_dance()
{
    if(Phase==CASTLE_MODE)
    {
        spi=(spi+1)%SPIDER_PHASE;
    }
}

//Avoid fire, or die
void fire_flow()
{
    if(Phase==COMET_MODE)
    {
        f=(f+1)%FIRE_PHASE;
    }
}

void ghost()
{
    if(Phase==NIGHT_MODE)
    {
        gh=(gh+1)%GHOST_PHASE;
    }
}

//sasuke frog jump
void sasuke()
{
    if(Phase==FINAL_RESCUE)
    {
        sasuke_i=(sasuke_i+1)%SASUKE_FROG_PHASE;
    }
}

//Coin spins
void coin_spin()
{
    c=(c+1)%COIN_PHASE;
}

//Sasuke Wakes up gradually
void sasukeWakeUp()
{
    if(Alive && rescue && !win)
    {
        if(sasukeWake_i<3)
        {
            sasukeWake_i++;
        }
        else
        {
//            sasukeWake_i=0;
            afterWin();
        }
    }
}

void afterWin()
{
    if(!win)
    {
        if(k2.taken==false && k4.taken==false)
        {
            rescue==false;
            gameOver;
        }
        else
        {
            if(sound)
            {
                PlaySound(Win, NULL, SND_ASYNC);
            }
            win=true;
            score+=1500;
        }
        score_board();
    }
}

void ghost_fly()
{
    if(!ghost1)
    {
        g1+=10;
    }
    if(!ghost2)
    {
        g2+=10;
    }
    if(!ghost3)
    {
        g3+=10;
    }
}

void finalRescue()
{
    if(Phase==HOME_PAGE)
    {
        SakuraY=140;
    }
}

void gameOver()
{
    if(!Alive && !over)
    {
        if(sound)
        {
            PlaySound(Game_Over, NULL, SND_ASYNC);
        }
        over=true;
        score_board();
    }
    else if (Alive)
    {
        score=0;
        if(sound)
        {
            PlaySound(Game_Over, NULL, SND_ASYNC);
        }
        over=true;
        score_board();
        Alive=false;
        fail=true;
    }
}

void saved_with_life()
{
    if(!over)
    {
        over=true;
        lose_life=true;
        Alive=false;
//        life_count--;
//        if(score>2000)
//        {
//            score-=2000;
//        }
//        else
//        {
//            score=0;
//        }
        again=true;
        if(sound)
        {
            PlaySound(loseLife, NULL, SND_ASYNC);
        }
    }
}

void eat_shuriken()
{
    if(abs(ShuX-SakuraX)<20 && Alive)
    {
        score+=50;
        if(sound)
        {
            PlaySound(shurikenFlow, NULL, SND_ASYNC);
        }
    }
}

void time_10() //Because there is a limit of using timers
{
    if(Alive)
    {
        fall_down_in_the_fire();
        hitCometCheck();
        hitGhostCheck();
        getKickPower();
        getlife();
    }
    downChange();
    kick_ghost();
    kickChange();
    eat_coin();
    take_key();
}

void time_20()
{
    key_fall();
    cometChange();
    lifeChange();
    jumpChange();
    changeKickPower();
    shurikenChange();
    if(Alive)
    {
        hitShurikenCheck();
        eat_shuriken();
    }
    ghost_fly();
}

void time_100()
{
    fire_flow();
    if(!Pause && Alive && !win)
    {
        if(score>0)
        {
            score--;
        }
    }
}

void time_200()
{
    spider_dance();
    coin_spin();
    ghost();
    fwSet();
}

void time_300() //Because there is a limit of using timers
{
    sasuke();
    sasukeWakeUp();
}

void time_400()
{
    //code
}

int main()
{
    fwSet();
//    score_board();
    reset();
//    PlaySound("bg_sound.wav", NULL, SND_LOOP | SND_ASYNC);
//    setComet();
//    iSetTimer(10,fall_down_in_the_fire);
//    iSetTimer(10,hitCometCheck);
//    iSetTimer(10,downChange);
    iSetTimer(10,time_10);
//    iSetTimer(20,cometChange);
//    iSetTimer(20,jumpChange);
//    iSetTimer(20,shurikenChange);
//    iSetTimer(20,hitShurikenCheck);
    iSetTimer(20,time_20);
//    iSetTimer(100,fire_flow);
    iSetTimer(100,time_100);
//    iSetTimer(200,spider_dance);
    iSetTimer(200,time_200);
//    iSetTimer(300,sasuke);
//    iSetTimer(300,sasukeWakeUp);
    iSetTimer(300,time_300);
//    iSetTimer(400,time_400);
//    }
    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Mission: Extreme");
    return 0;
}

void score_board()
{
//    FILE *fp;
//    fp=freopen(filename, "w", stdout);
//    cout<<name<<"\n"<<score<<"\n";
//    fclose(fp);
    FILE *fp;
    fp=freopen(filename, "r", stdin);
    char ch, temp_name1[NAME_LEN], temp_name2[NAME_LEN];
    int i=0, temp_score1, temp_score2, name_len, name1_len, name2_len, name3_len, temp_len;
    while((ch=fgetchar())!='\n') name1[i++]=ch;
    name1[i]='\0';
    cin>>score1;
    getchar();
//    name1_len=strlen(name1);
    i=0;
    while((ch=fgetchar())!='\n') name2[i++]=ch;
    name2[i]='\0';
    cin>>score2;
    getchar();
//    name2_len=strlen(name2);
    i=0;
    while((ch=fgetchar())!='\n') name3[i++]=ch;
    name3[i]='\0';
    cin>>score3;
    getchar();
//    name3_len=strlen(name3);
    i=0;
    while((ch=fgetchar())!='\n') name4[i++]=ch;
    name4[i]='\0';
    cin>>score4;
    fclose(fp);

//    cout<<name<<"\n"<<score<<"\n";
//    cout<<name1<<"\n"<<score1<<"\n";
//    cout<<name2<<"\n"<<score2<<"\n";
//    cout<<name3<<"\n"<<score3<<"\n";

//    name_len=strlen(name);
    fp=freopen(filename, "w", stdout);
    if(score>score1)
    {
//        temp_score1=score1;
//        score1=score;
//        strncpy(temp_name1, name1, name1_len);
//        strncpy(name1, name, name_len);
//        temp_score2=score2;
//        score2=temp_score1;
//        strncpy(temp_name2, name2, name2_len);
//        temp_len=strlen(temp_name1);
//        strncpy(name2, temp_name1, temp_len);
//        score3=temp_score2;
//        temp_len=strlen(temp_name2);
//        strncpy(name3, temp_name2, temp_len);
        cout<<name<<"\n"<<score<<"\n";
        cout<<name1<<"\n"<<score1<<"\n";
        cout<<name2<<"\n"<<score2<<"\n";
        cout<<name3<<"\n"<<score3<<"\n";
    }
    else if (score>score2)
    {
//        temp_score2=score2;
//        score2=score;
//        strncpy(temp_name2, name2, name2_len);
//        strncpy(name2, name, name_len);
//        score3=temp_score2;
//        temp_len=strlen(temp_name2);
//        strncpy(name3, temp_name2, temp_len);
        cout<<name1<<"\n"<<score1<<"\n";
        cout<<name<<"\n"<<score<<"\n";
        cout<<name2<<"\n"<<score2<<"\n";
        cout<<name3<<"\n"<<score3<<"\n";
    }
    else if (score>score3)
    {
//        score3=score;
//        strncpy(name3, name, name_len);
        cout<<name1<<"\n"<<score1<<"\n";
        cout<<name2<<"\n"<<score2<<"\n";
        cout<<name<<"\n"<<score<<"\n";
        cout<<name3<<"\n"<<score3<<"\n";
    }
    else if (score>score4)
    {
        cout<<name1<<"\n"<<score1<<"\n";
        cout<<name2<<"\n"<<score2<<"\n";
        cout<<name3<<"\n"<<score3<<"\n";
        cout<<name<<"\n"<<score<<"\n";
    }
    else
    {
//        cout<<name<<"\n"<<score<<"\n";
        cout<<name1<<"\n"<<score1<<"\n";
        cout<<name2<<"\n"<<score2<<"\n";
        cout<<name3<<"\n"<<score3<<"\n";
        cout<<name4<<"\n"<<score4<<"\n";
    }
    fclose(fp);
    scoring=true;
    final_score=score;
    score=-1;
}
