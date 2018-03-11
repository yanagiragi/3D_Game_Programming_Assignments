#include "monsters.h"
#include "BasicTools.h"

MONSTER::MONSTER(SceneManager *a_SceneMgr) : GAME_OBJ(a_SceneMgr)
{
}

/*
Update the view direction of the monster.
*/
void MONSTER::updateViewDirection()
{
    
}

/*
Update the position and view direction of the monster.
*/
void MONSTER::update(const Ogre::FrameEvent& evt)
{
    //compute the position of the monster
    //call updateViewDirection( )
}