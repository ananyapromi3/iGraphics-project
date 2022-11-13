#include<bits/stdc++.h>
using namespace std;
#include "iGraphics.h"
#define SCREEN_WIDTH 1200
#define SCREEN_HEIGHT 600
#define JUMP_LIMIT 200
#define NIGHT_MODE 6
//#define INTRO2_PAGE 5
//#define INTERVAL2_PAGE -5


int ruleListX=300;
int ruleListY=40;
int SakuraX=0, SakuraY=50;
int BgX=0,BgY=0;
int SI=0,P=2;
char SakuraRun[6][15]= {"SakuraRun1.bmp","SakuraRun2.bmp","SakuraRun3.bmp","SakuraRun4.bmp","SakuraRun5.bmp","SakuraRun6.bmp"};
char SakuraJump[2][20]= {"SakuraJumpUp.bmp","SakuraJumpDown.bmp"};
char SakuraStand[20]="SakuraStanding.bmp";
char Kickimage[2][20]= {"sakurakick1.bmp","sakurakick2.bmp"};
char Intro2_image[5][20]= {"Intro2_1.bmp","Intro2_2.bmp","Intro2_3.bmp","Intro2_4.bmp","Intro2_5.bmp"};
bool Stand=true;
bool jump=false, jumpUp=false, jumpDown=false, kick=false,jumpG =false;
bool run=false;
int SakuraJumpY=0,SakuraKickX=0;
int Phase=NIGHT_MODE;
bool Alive=true;
bool win=false;

//ghost related
int GhostX[6]= {200,450,650,800,1000,1100};
int GhostY[6]= {10,200,10,200,10,200};
bool ghost_phase1=true,ghost_phase2=true,ghost_phase3=true,ghost_phase4=true,ghost_phase5=true,ghost_phase6=true;

//Coin related
int c=0;
char coin[6][20]= {"coin1.bmp","coin2.bmp","coin3.bmp","coin4.bmp","coin5.bmp","coin6.bmp"};
void coin_spin();
void eat_coin();
int score=0;
bool comet_coin1=true;
bool comet_coin2=true;
bool comet_coin3=true;
bool comet_coin4=true;
bool comet_coin5=true;

//sakura_death
char SakuraDie[4][20]= {"sakuraghostdie1.bmp","sakuraghostdie2.bmp","sakuraghostdie1.bmp","sakuraghostdie4.bmp"};
int l=0;


void iDraw()
{
    iClear();

//     if(Phase==INTERVAL2_PAGE)
//     {
//        iShowBMP(BgX,BgY,"phase-5.bmp");
//        iShowBMP(840,500,"nxtlvl1.bmp");
//     }
//
//     if(Phase==INTRO2_PAGE)
//    {
//
//        iShowBMP(BgX,BgY,Intro2_image[P]);
//        iShowBMP(BgX,BgY,Intro2_image[(P+2)%5]);
//        iShowBMP(BgX,BgY,Intro2_image[(P+4)%5]);
//        iShowBMP(BgX,BgY,Intro2_image[(P+6)%5]);
//        iShowBMP(BgX,BgY,Intro2_image[(P+8)%5]);
//
//        iShowBMP2(50,50,"Rules.bmp",0);
//        Alive=true;
//        Stand=true;
//    }

    if(Phase==NIGHT_MODE)
    {
        iShowBMP(BgX,BgY,"cherryblossom.bmp");
        if(Alive && !win)
        {
            if(jump) //in jump phase
            {
                if(jumpUp)
                {
                    if (kick&&SakuraJumpY>170) //jump+kick-phase
                        iShowBMP2(SakuraX,JUMP_LIMIT,Kickimage[0],0);

                    else
                        iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJump[0],0);
                }
                else
                {
                    kick =false;
                    iShowBMP2(SakuraX,SakuraY+SakuraJumpY,SakuraJump[0],0);
                }

            }
            else if (kick) //kick-phase
            {
                iShowBMP2(SakuraX,SakuraY,Kickimage[0],0);


            }
            else //non-jump phase
            {
                if(!Stand)
                {
                    kick=false;
                    iShowBMP2(SakuraX,SakuraY,SakuraRun[SI],0);//Running phase
                }

                else
                {
                    iShowBMP2(SakuraX,SakuraY,SakuraStand,0); //Stand phase
                    run=false;
                }
            }
            //ghost
            if(ghost_phase1)
            {
                iShowBMP2(GhostX[0],GhostY[0],"ghostimages.bmp",0);

            }
            if(ghost_phase2)
            {
                iShowBMP2(GhostX[1],GhostY[1],"ghostimages.bmp",0);

            }
            if(ghost_phase3)
            {
                iShowBMP2(GhostX[2],GhostY[2],"ghostimages.bmp",0);

            }
            if(ghost_phase4)
            {
                iShowBMP2(GhostX[3],GhostY[3],"ghostimages.bmp",0);

            }
            if(ghost_phase5)
            {
                iShowBMP2(GhostX[4],GhostY[4],"ghostimages.bmp",0);

            }
            if(ghost_phase6)
            {
                iShowBMP2(GhostX[5],GhostY[5],"ghostimages.bmp",0);

            }
            //coin
            if(comet_coin1)
                iShowBMP2(100,240,coin[c],0); //for coin spin


            if(comet_coin2)
                iShowBMP2(345,120,coin[c],0);
            if(comet_coin3)
                iShowBMP2(322,180,coin[c],0);
            if(comet_coin4)
                iShowBMP2(310,120,coin[c],0);


            if(comet_coin5)
                iShowBMP2(910,240,coin[c],0); //for coin spin

        }

        else
        {
            if(!Alive)
            {
                iShowBMP2(SakuraX,SakuraY=0,SakuraDie[l],0);
                Stand=false;


            }
        }
        if(win)
        {
            Stand=true;
            Alive=true;
            iShowBMP2(SakuraX,SakuraY,SakuraStand,0);
            win=true;
        }
        iShowBMP2(40,520,"Home.bmp",0);
    }

}




/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/


void iMouseMove(int mx, int my)
{
    //printf("x = %d, y= %d\n",mx,my);
    //place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        //place your codes here
        //printf("x = %d, y= %d\n",mx,my);
        if(Phase==5&& mx>1000 && mx<1150 && my>70 && my<150)
        {
            Phase=6;
        }
        //if(Phase==0 && mx>50 && mx<200 && my>50 && my<105)
        //{
        //Phase=-1;
        //}
        if(mx>40 && mx<140 && my>520 && my<558)
        {
            Phase=6;
        }
        if(Phase==-5&& mx>840 && mx<1200 && my>500 && my<550)
        {
            Phase=5;
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
    if(key==' ')
    {
        kick=false;
        Stand=true;
    }
    if(key=='k')
    {
        kick=true;
        run=false;
        Stand=false;

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

    if(key == GLUT_KEY_END)
    {
        exit(0);
    }
    if(key==GLUT_KEY_LEFT)
    {
        kick=false;
        Stand=true;
    }
    if(key==GLUT_KEY_RIGHT) //Sakura runs
    {
        if(Phase==NIGHT_MODE)
        {
            if(SakuraX+100<SCREEN_WIDTH)
            {
                run= true;
                Stand=false;
                SakuraX+=10;

                SI++;
                if(SI>5)
                {
                    SI=0;
                    kick=false;
                }

            }

            else
                Stand =true;
        }
    }
    if(key==GLUT_KEY_UP) //Sakura jumps
    {

        if(!jump)
        {
            jump=true;
            jumpUp=true;

        }
    }
}

void jumpChange()
{
    if(jump) //in jump phase
    {
        if(jumpUp) //when jumps up
        {
            SakuraJumpY+=5;
            if(SakuraJumpY>=JUMP_LIMIT) //Cannot jump up beyond the limit
            {
                jumpUp=false;
            }
        }
        else //now jumps down
        {
            SakuraJumpY-=5;
            if(SakuraJumpY<0)
            {
                jump=false;
                SakuraJumpY=0;
            }
            Stand=true;
        }
    }
}

void ghostCheck()
{
    if(Phase==NIGHT_MODE)

        if((SakuraX>130)&&(SakuraX<=140))
        {
            Alive=(kick==true)?true:false;
            if(Alive==true)
                ghost_phase1=false;
        }

    if ((SakuraX<=430) &&(SakuraX>420))
    {
        if(jump==false)
            Alive=false;
        else
        {
            if((SakuraY>160)&&(SakuraY<=200))
                Alive=(kick==true)?true:false;
        }
        if(Alive==true)
            ghost_phase2=false;
    }


    if((SakuraX>580) &&(SakuraX<=590))
    {
        Alive=(kick==true)?true:false;
        if(Alive==true)
            ghost_phase3=false;
    }


    if ((SakuraX<=775) &&(SakuraX>765))
    {
        if(jump==false)
            Alive=false;
        else
        {
            if((SakuraY>180)&&(SakuraY<=200))
                Alive=(kick==true)?true:false;
            else
                Alive==false;
        }
        if(Alive==true)
            ghost_phase4=false;

    }



    if((SakuraX>930) &&(SakuraX<=940))
    {
        Alive= (kick==true)?true:false;
        if(Alive==true)
            ghost_phase5=false;
    }


    if ((SakuraX<=1050) &&(SakuraX>1040))
    {
        if(jump==false)
            Alive=false;
        else
        {
            if((SakuraY>160)&&(SakuraY<=200))
                Alive=(kick==true)?true:false;
        }
        if(Alive==true)
            ghost_phase6=false;
    }

}


//Coin spins
void coin_spin()
{
    c=(c+1)%6;
}
//intro2 change
//void intro2Change()
//{
//        if(Phase==INTRO2_PAGE)
//        {   if(P!=1)
//            P=(P+1)%5;
//        }
//}

void eat_coin()
{
    if(Phase==NIGHT_MODE)
    {
        if(SakuraY+SakuraJumpY>150 && SakuraY+SakuraJumpY<240)
        {
            if(SakuraX>50 && SakuraX<200)
            {
                if(comet_coin1)
                {
                    //PlaySound(coin_sound, NULL, SND_ASYNC);
                    //score+=100;
                    comet_coin1=false;
                }
            }
        }
        if(SakuraX>300 && SakuraX <350 && SakuraY+SakuraJumpY>70 && SakuraY+SakuraJumpY<130)
        {
            if(comet_coin2)
            {
                //PlaySound(coin_sound, NULL, SND_ASYNC);
                //score+=100;
                comet_coin2=false;
            }
        }
        if(SakuraX>270 && SakuraX <350 && SakuraY+SakuraJumpY>140 && SakuraY+SakuraJumpY<240)
        {
            if(comet_coin3)
            {
                //PlaySound(coin_sound, NULL, SND_ASYNC);
                //score+=100;
                comet_coin3=false;
            }
        }
        if(SakuraX>270 && SakuraX <330 && SakuraY+SakuraJumpY>70 && SakuraY+SakuraJumpY<130)
            if(comet_coin4)
            {
                //PlaySound(coin_sound, NULL, SND_ASYNC);
                //score+=100;
                comet_coin4=false;
            }

        if(SakuraX>880 && SakuraX<980 &&SakuraY+SakuraJumpY>150 && SakuraY+SakuraJumpY<240)
        {
            if(comet_coin5)
            {
                //PlaySound(coin_sound, NULL, SND_ASYNC);
                //score+=100;
                comet_coin5=false;
            }
        }
    }
}
void sakura_Die()
{
    if(l!=3)
        l=(l+1)%4;
}


int main()
{
    if(Alive)
    {
        ghostCheck;
        eat_coin;
//            iSetTimer(2000,intro2Change);
        iSetTimer(20, jumpChange);
        iSetTimer(500,coin_spin);
        iSetTimer(10,ghostCheck);
        iSetTimer(50,eat_coin);
        iSetTimer(1600,sakura_Die);

    }
    iInitialize(SCREEN_WIDTH, SCREEN_HEIGHT, "Sakura Go!");
    return 0;
}
