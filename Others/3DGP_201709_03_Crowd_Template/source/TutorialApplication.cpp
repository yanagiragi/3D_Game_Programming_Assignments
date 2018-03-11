//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
#include "TutorialApplication.h"
#include "BasicTools.h"
#include "read_data.h"

using namespace Ogre;
BasicTutorial_00::BasicTutorial_00(void) {
	mFlgMotion = true;
	mToggle = 2.5;
	mKeyPressed = false;
	//
	mMainChar = 0;
	mCameraDistance = 0;
	mKeyPressedZoomMode = 0;
mCameraDistanceAdjustSpeed = 0;
mCameraDistanceSlowDownSpeed = 0;
}

//
//handle the mouse motion (passive) event
//
bool BasicTutorial_00::mouseMoved( const OIS::MouseEvent &arg )
{
	bool flg = BaseApplication::mouseMoved(arg);
	//mMainChar->updateViewDirection();
	return flg;
}

//handle the key pressed event
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
	//bool flg = BaseApplication::keyPressed(arg);
	bool flg = true;
	
	if (arg.key == OIS::KC_W) {
		//mMainChar->setWalkForward();
	}
	

	if (arg.key == OIS::KC_SPACE)
	{
		//mMainChar->setFireAction_Normal();
	}

	return flg;
}

//handle the key released event
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
	bool flg = true;

	if (arg.key == OIS::KC_ESCAPE)
	{
		mShutDown = true;
	}
	return flg;
}
void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(
	ST_EXTERIOR_CLOSE, "primary");
	mSceneMgrArr[1] =mSceneMgrArr[0];

}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(0,100,0));
	mCamera->lookAt(Ogre::Vector3(0,50,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam2");
	mCamera->setPosition(Ogre::Vector3(750,100,750));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
	//mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller

}



void BasicTutorial_00::createViewport_00(void)
{
	mCamera = mCameraArr[0];
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0,1));
    mCamera->setAspectRatio( 4.0 / 1.0 );
}

void BasicTutorial_00::createViewport_01(void)
{
	mCamera = mCameraArr[1];

	Ogre::Viewport* vp = mWindow->addViewport(
		mCamera,
		1,
		0.25,
		0.25,
		0.25,
		0.25
		);
	vp->setBackgroundColour(Ogre::ColourValue(0,1,0));
	mCamera->setAspectRatio(1.0/4.0);

}



void BasicTutorial_00::createScene_00(void) 
{
    /////////////////////////////////////
	DATA_READER::readData(); //Read the data file here.
	bt_Init(mTrayMgr, mSceneMgrArr[0], mCameraArr[0]); //Set the pointers of the objects so that the other functions can use the objects.
    /////////////////////////////////////

	mSceneMgr = mSceneMgrArr[0];
	
	ColourValue fadeColour(0.9, 0.9, 0.9); 

	Vector3 org = Vector3(750, 51, 750);
    mSceneMgr->setAmbientLight( ColourValue( 0.7, 0.7, 0.7 ) ); 


	initParticleSystemForExplosion();
	Vector3 pos;
	setOffParticleSystem(fNode, "explosion", pos);

	Light *light;
	light = mSceneMgr->createLight("Light1"); 
	light->setType(Light::LT_POINT);
	//light->setType(Light::LT_DIRECTIONAL);
	light->setPosition(Vector3(0, 450, 250)+org); 
	light->setDiffuseColour(0.7, 0.7, 0.7);		
	light->setSpecularColour(1.0, 1.0, 1.0);	
	light->setDirection(Vector3(1, 1, 1));
	mLight0 = light;

	mMainChar = new MAIN_CHAR(mSceneMgrArr[0]);
	mMainChar->createGameObj("m", "robot.mesh");

	mMainChar->attachCamera(mCameraArr[0]);

	mMainChar->setMaxBulletsNum(DATA_READER::getMaxBulletsNum());

mMonsterMgr = new MONSTER_MANAGER(mSceneMgrArr[0]);

mMonsterMgr->setTargetForMonsters(mMainChar);
mMonsterMgr->setMaxMonstersNum(DATA_READER::getMaxMonstersNum());

}

void BasicTutorial_00::createScene_01(void) 
{
	return;
}

/*
Implement the game logic in this function.
*/
bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
	mToggle += evt.timeSinceLastFrame;
    //
	
	mMainChar->update(evt);	
    mMonsterMgr->update(evt);
	return flg;
}

void BasicTutorial_00::createViewports(void)
{
	createViewport_00();
	createViewport_01();
	mCamera = mCameraArr[0];
}

void BasicTutorial_00::createCamera(void) {
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
	mCamera = mCameraArr[0];
}

void BasicTutorial_00::createScene( void ) {
	createScene_00();
	createScene_01();
	//mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	mSceneMgr = mSceneMgrArr[1]; // active SceneManager
}

void BasicTutorial_00::initParticleSystemForExplosion() {
	fNode = static_cast<SceneNode*>(
		mSceneMgr->getRootSceneNode()->createChild());
	//ParticleSystem* p = mSceneMgr->createParticleSystem(
	//		"explosion", "Examples/JetEngine1");
	ParticleSystem* p = mSceneMgr->createParticleSystem(
		"explosion", "Examples/Smoke");

	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(false);
	fNode->attachObject(p);
	fNode->setPosition(Vector3::ZERO);
	fNode->setVisible(false);
}

void BasicTutorial_00::setOffParticleSystem(
	Ogre::SceneNode *fNode, const Ogre::String &pname, const Ogre::Vector3 &pos) 
{
	fNode->setPosition(pos);
	fNode->setVisible(true);
	MovableObject *s = fNode->getAttachedObject(pname);
	ParticleSystem* p =static_cast<ParticleSystem*>(s);
	if (p == NULL) return;
	p->setVisible(true);
	ParticleEmitter *e = p->getEmitter(0);
	e->setEnabled(true);
}

int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
