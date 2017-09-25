////////////////////////////////////////
//
// 3D Game Programming
// NCTU
// Instructor: SAI-KEUNG WONG
//
////////////////////////////////////////
// Student Name:
// Student ID:
// Student Email:
//
////////////////////////////////////////
// You can delete everything and start from scratch.
////////////////////////////////////////

#include "TutorialApplication.h"
#include "BasicTools.h"

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>

using namespace Ogre;

const float PI = 3.141592654;

BasicTutorial_00::BasicTutorial_00(void) {
	ZOrderReversed = animateFlag = false;
	position = Ogre::Vector3(0, 0, 0);
	velocity =  Ogre::Vector3(0, 0, 0);
	acceleration = Ogre::Vector3(0.0, -50.8, 0.0);
	y = 0.0;
	frame = 0;
}

void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	mSceneMgrArr[1] = mRoot
		->createSceneManager(ST_GENERIC, "secondary");
}

void BasicTutorial_00::createCamera_00(void)
{
	mSceneMgr = mSceneMgrArr[0];
	mCamera = mCameraArr[0] = mSceneMgr->createCamera("PlayerCam");
	mCamera->setPosition(Ogre::Vector3(120,300,600));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[0] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createCamera_01(void)
{
	mSceneMgr = mSceneMgrArr[1];
	mCamera = mCameraArr[1] = mSceneMgr->createCamera("PlayerCam2");
	mCamera->setPosition(Ogre::Vector3(0,350,0.001));
	mCamera->lookAt(Ogre::Vector3(0,0,0));
	mCamera->setNearClipDistance(5);
	mCameraManArr[1] = new OgreBites::SdkCameraMan(mCamera);   // create a default camera controller
}

void BasicTutorial_00::createViewport_00(void)
{
	mCamera = mCameraArr[0];
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	vp->setBackgroundColour(Ogre::ColourValue(0,0.0,1.0));
	//vp->setBackgroundColour(Ogre::ColourValue(0,0.0,0.0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

    mViewportArr[0] = vp;
}

void BasicTutorial_00::createViewport_01(void)
{
	mCamera = mCameraArr[1];
	Ogre::Viewport* vp = mWindow->addViewport(mCamera, 1, 0.75, 0, 0.25, 0.25);
	vp->setBackgroundColour(Ogre::ColourValue(0,0.0,0.0));
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	
	mViewportArr[1] = vp;
	vp->setOverlaysEnabled(false);
}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];
	
	setupAmbient();
	createPlane();
	createCubes();
	createLight();
	createPengiun();

	mSceneMgr = mSceneMgrArr[1];

	mSceneMgr->setAmbientLight(Ogre::ColourValue(0, 0, 0));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

	Plane plane(Vector3::UNIT_Y, 0);
	MeshPtr mPlane = MeshManager::getSingleton().createPlane(
		"ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500,1500, // width, height
		20,20, // x- and y-segments
		true, // normal
		1, // num texture sets
		5,5, // x- and y-tiles
		Vector3::UNIT_Z // upward vector
	);

	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);

	groundEntity->setMaterialName("Examples/Green");

	// Point light
	Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
	pointLight->setType(Light::LT_POINT);
	pointLight->setPosition(Vector3(100, 150, 250));
	pointLight->setDiffuseColour(0.0, 0.0, 1.0); //blue
	pointLight->setSpecularColour(0.0,0.0, 1.0); //blue

	Ogre::Entity* ballEntity = mSceneMgr->createEntity("mySphere", Ogre::SceneManager::PT_SPHERE);
	SceneNode* ballNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ballNode->attachObject(ballEntity);
	ballNode->setPosition(Ogre::Vector3(50,0,50));
	ballNode->setScale(Ogre::Vector3(.5, .5, .5));

	Ogre::Entity* cubelEntity = mSceneMgr->createEntity("myCube", Ogre::SceneManager::PT_CUBE);
	SceneNode* cubeNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	cubeNode->attachObject(cubelEntity);
	cubeNode->setPosition(Ogre::Vector3(0, 0, 0));
	cubeNode->setScale(Ogre::Vector3(.3, .2, .5));


	groundEntity->setMaterialName("Examples/Green");
}

void BasicTutorial_00::createPengiun()
{
	Entity *ent = mSceneMgr->createEntity("penguin", "penguin.mesh"); 
	SceneNode *snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->attachObject(ent);
	position = Ogre::Vector3(0, 50, 0);
	snode->setPosition(position);
	mPenguinSceneNode = snode;
	velocity =  Ogre::Vector3(0, 0, 0);
	

	Entity *s_ent = mSceneMgr->createEntity("penguin2", "penguin.mesh"); 
	SceneNode *ss_node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ss_node->attachObject(s_ent);
	ss_node->setPosition(Ogre::Vector3(150, 50, 0));
	ss_node->setOrientation(Ogre::Quaternion(1.0, 0, -1.0, 0));
	ss_node->setScale(Ogre::Vector3(0.5, 0.5, 0.5));
}

void BasicTutorial_00::toggleViewPort()
{
		mWindow->removeViewport(mViewportArr[0]->getZOrder());
		mWindow->removeViewport(mViewportArr[1]->getZOrder());

		if(!ZOrderReversed){
			Ogre::Viewport* vp;

			mCamera = mCameraArr[1];
			vp = mWindow->addViewport(mCamera);
			vp->setBackgroundColour(Ogre::ColourValue(0,0.0,0.0));
			mCamera->setAspectRatio(
				Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	
			mViewportArr[1] = vp;
			vp->setOverlaysEnabled(false);

			mCamera = mCameraArr[0];
			vp = mWindow->addViewport(mCamera, 1, 0.5, 0, 0.5, 0.25);
			vp->setBackgroundColour(Ogre::ColourValue(0,0.0,1.0));
			//vp->setBackgroundColour(Ogre::ColourValue(0,0.0,0.0));
			mCamera->setAspectRatio(
				Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

			mViewportArr[0] = vp;
			vp->setOverlaysEnabled(true);
		}
		else{
			Ogre::Viewport* vp;

			mCamera = mCameraArr[0];
			vp = mWindow->addViewport(mCamera);
			vp->setBackgroundColour(Ogre::ColourValue(0,0.0,1.0));
			//vp->setBackgroundColour(Ogre::ColourValue(0,0.0,0.0));
			mCamera->setAspectRatio(
				Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

			mViewportArr[0] = vp;
			vp->setOverlaysEnabled(true);

			mCamera = mCameraArr[1];
			vp = mWindow->addViewport(mCamera, 1, 0.75, 0.5, 0.25, 0.25);
			vp->setBackgroundColour(Ogre::ColourValue(0,0.0,0.0));
			mCamera->setAspectRatio(
				Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	
			mViewportArr[1] = vp;
			vp->setOverlaysEnabled(false);

			
		}
}

void BasicTutorial_00::createLight()
{
	// Point light
	Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setDiffuseColour(0, 1, 0);
	pointLight->setSpecularColour(0, 1, 0); 
	pointLight->setPosition(Ogre::Vector3(150, 250, 100));

	// Point light
	Ogre::Light* pointLight2 = mSceneMgr->createLight("PointLight2");
	pointLight2->setType(Ogre::Light::LT_POINT);
	pointLight2->setPosition(Ogre::Vector3(150, 300, 250));
	pointLight2->setDiffuseColour(.5, .5, .5);
	pointLight2->setSpecularColour(.5, .5, .5); 
}

void BasicTutorial_00::createCubes()
{
	int numCubes = 72; 
	int L = 255;

	float cubeSize, x, y, z, fx, h, x1, z1, unitF, circle_radius;
	for (int i = 0; i < numCubes; ++i) {
		
		String name;  
		
		genNameUsingIndex("c", i, name); 
		
		Entity *ent = mSceneMgr->createEntity(name, "cube.mesh"); 
		ent->setMaterialName("Examples/SphereMappedRustySteel");  
		
		AxisAlignedBox bb = ent->getBoundingBox();		
		cubeSize = bb.getMaximum().x - bb.getMinimum().x;  
		x = 0, y = 0, z = -125;  
		
		SceneNode *snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		snode->attachObject(ent);  
		
		// in range [0,1]  
		fx = i / (double)(numCubes - 1); 
		
		// height
		h = (1+sin(fx*PI*4))*50; 
		
		circle_radius = 100;
		x1 = circle_radius*cos(fx*PI*2);
		z1 = circle_radius*sin(fx*PI*2);
		unitF = 1.0/cubeSize/numCubes*L*0.8;
		
		snode->scale(unitF, h/cubeSize, unitF);
		snode->setPosition(x1, 50, z1); 
	} 

	for (int i = 0; i < numCubes; ++i) {

		String name;

		genNameUsingIndex("c_a", i, name);

		Entity *ent = mSceneMgr->createEntity(name, "cube.mesh");
		ent->setMaterialName("Examples/Chrome");

		AxisAlignedBox bb = ent->getBoundingBox();
		cubeSize = bb.getMaximum().x - bb.getMinimum().x;
		x = 0, y = 0, z = -125;

		SceneNode *snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
		snode->attachObject(ent);

		fx = 2 * i / (double)(numCubes - 1); 
		
		//i from 0 to numCubes-1 
		
		x = fx*L - L/2.0; 
		h = (1+cos(fx*3.1415*2.0))*20; 
		
		// height 
		
		Real unitF = 1.0/cubeSize/numCubes*L*0.8; 
		
		snode->scale(unitF, h/cubeSize, unitF); 
		
		snode->setPosition(x, 20, z + 300);
	}
}

void BasicTutorial_00::setupAmbient()
{
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);

}

void BasicTutorial_00::createPlane()
{
	Plane plane(Vector3::UNIT_Y, 0);
	MeshPtr mPlane = MeshManager::getSingleton().createPlane(
		"ground",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500,1500, // width, height
		20,20, // x- and y-segments
		true, // normal
		1, // num texture sets
		5,5, // x- and y-tiles
		Vector3::UNIT_Z // upward vector
	);

	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);

	groundEntity->setMaterialName("Examples/Green");

	Plane plane2(Vector3::UNIT_Z, 0);

	MeshPtr mPlane2 = MeshManager::getSingleton().createPlane(
		"wall",
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane2,
		1500, 1500, // width, height
		20, 20, // x- and y-segments
		true, // normal
		1, // num texture sets
		5, 5, // x- and y-tiles
		Vector3::UNIT_Y // upward vector
	);

	Ogre::Entity* wallEntity = mSceneMgr->createEntity("wall");
	
	SceneNode *nPlane2 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	
	nPlane2->attachObject(wallEntity);
	nPlane2->setPosition(0, 750, -750);

	wallEntity->setMaterialName("Examples/Rockwall");
}

void BasicTutorial_00::createScene_01(void) 
{
    // add your own stuff
}

void BasicTutorial_00::createViewports(void)
{
	//Do not modify
	createViewport_00();
	createViewport_01();
}

void BasicTutorial_00::createCamera(void) {
    //Do not modify
	createCamera_00();
	createCamera_01();
	mCameraMan = mCameraManArr[0];
	//mCameraMan = mCameraManArr[1];
}

void BasicTutorial_00::createScene( void ) {
    //Do not modify
	createScene_00();
	createScene_01();
	mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	//mSceneMgr = mSceneMgrArr[1]; // active SceneManager
    //
    mCamera = mCameraArr[0];
    //mCamera = mCameraArr[1];
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
//
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyPressed( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyPressed ***\n";
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    
    if (arg.key == OIS::KC_C ) {
        
        //How to clear ss?
        ss.str("");
        ss.clear();
        
        //stringstream ss; // Second way

        // Third way?
        //=============

        // How to get camerea position?
        //-----------------------------
        //This is incorrect.
        //Vector3 pos = mCamera->getPosition();
        //-----------------------------
        Vector3 pos = mCameraMan->getCamera()->getPosition(); //Correct
        ss << std::fixed << std::setprecision(2) 
            << "CameraPosition:" 
            << pos.x << "\t" 
            << pos.y << "\t" 
            << pos.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
        ss.str("");
        ss.clear();
        Vector3 dir = mCameraMan->getCamera()->getDirection();
        ss << std::fixed << std::setprecision(2) 
            << "CameraDirection:" 
            << dir.x << "\t" 
            << dir.y << "\t" 
            << dir.z << "\n";
        Ogre::LogManager::getSingletonPtr()
            ->logMessage( ss.str() );
        //
    }
	if (arg.key == OIS::KC_O ) {
		animateFlag = !animateFlag;
	}

    if (arg.key == OIS::KC_1 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(98.14,	450.69,	964.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.01,	-0.30,	-0.95));

        //98.14	450.69	964.20
        //-0.01	-0.30	-0.95
    }

    if (arg.key == OIS::KC_2 ) {
		mCameraMan->getCamera()
            ->setPosition(Vector3(-1463.00, 606.45,	-513.24));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.88, -0.47,	0.10));
    }

    if (arg.key == OIS::KC_3 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(-1356.16,634.32,-964.51));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0.71, -0.44, 0.55));
        //
        //0.71	-0.44	0.55
    }

    if (arg.key == OIS::KC_4 ) {
         mCameraMan->getCamera()
            ->setPosition(Vector3(40.39, 155.23, 251.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.02, -0.41, -0.91));
        //40.39	155.23	251.20
        //-0.02	-0.41	-0.91
    }

    if (arg.key == OIS::KC_5 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(19.94, 822.63, 30.79));
        mCameraMan->getCamera()
            ->setDirection(Vector3(0, -0.99, -0.11));
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
    }

    if (arg.key == OIS::KC_M ) {
		ZOrderReversed = false;
		toggleViewPort();
    }

    if (arg.key == OIS::KC_N ) {
        ZOrderReversed = true;
		toggleViewPort();
    }

	
    // Do not delete this line
    BaseApplication::keyPressed(arg);

    return flg;
}

//
// What is stored in the file for arg.key?
// ASCII code? If no, what is it?
// 
// To find out the answer:
// Go to see the definition of KeyEvent
//
bool BasicTutorial_00::keyReleased( const OIS::KeyEvent &arg )
{
    bool flg = true;
    stringstream ss;
    ss << arg.key;
    String msg;
    ss >> msg;
    msg += ":*** keyReleased ***\n";
    
    Ogre::LogManager::getSingletonPtr()->logMessage( msg );

    BaseApplication::keyReleased(arg);

    return flg;
}

void BasicTutorial_00::animatePenguin(int frame)
{
	if(!animateFlag){
		return ;
	}

	Real time_step = 1.0 / 200.0;

	velocity += acceleration * time_step;
	position += velocity * time_step;
	y += velocity.y * time_step;

	if(position.y < 15.0){
		position.y = 15.0;
		acceleration = Vector3(0.0, 20.8, 0.0);
	}
	else if (position.y >= 280){
		acceleration = Vector3(0.0, -50.8, 0.0);
	}

	mPenguinSceneNode->setPosition(position);

	/*
		Vector3 acceleration = Vector3(0.0, -50.8, 0.0);
		velocity += acceleration*time_step
		position += velocity*time_step
		If position.y < 0.0 then position.y = 0.0
		To move up, we have
		Vector3 acceleration = Vector3(0.0, 20.8, 0.0);
		The maximum height is 280.
		The maximum speed is 80
	*/
}

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
	++frame;
	animatePenguin(frame);
    return flg;
}
int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
