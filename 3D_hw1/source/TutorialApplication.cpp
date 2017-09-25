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

BasicTutorial_00::BasicTutorial_00(void) {}

void BasicTutorial_00::chooseSceneManager()
{
	mSceneMgrArr[0] = mRoot
		->createSceneManager(ST_GENERIC, "primary");
	//mSceneMgrArr[1] = mRoot
	//	->createSceneManager(ST_GENERIC, "secondary");
    //
    // add your own stuff
    //
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
	// add your own stuff
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
    // add your own stuff
}

void BasicTutorial_00::createScene_00(void) 
{
	mSceneMgr = mSceneMgrArr[0];

    // add your own stuff

    /*
    Radian angle(3.141952654/2.0);

    Vector3 axis(1.0, 0.0, 0.0);
    mSceneMgr
		->getRootSceneNode()
		->createChildSceneNode(
            Vector3(0.0, 0.0, -750.0),
            Quaternion( angle, axis))
		->attachObject(ent);
    */

	setupAmbient();
	createPlane();
	createCubes();

	Entity *ent = mSceneMgr->createEntity("penguin", "penguin.mesh"); 
	SceneNode *snode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	snode->attachObject(ent);
	snode->setPosition(Ogre::Vector3(0, 50, 0));

	Entity *s_ent = mSceneMgr->createEntity("penguin2", "penguin.mesh"); 
	SceneNode *ss_node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ss_node->attachObject(s_ent);
	ss_node->setPosition(Ogre::Vector3(150, 50, 0));
	ss_node->setOrientation(Ogre::Quaternion(1.0, 0, -1.0, 0));
	ss_node->setScale(Ogre::Vector3(0.5, 0.5, 0.5));
  
	// Point light
	Ogre::Light* pointLight = mSceneMgr->createLight("PointLight");
	pointLight->setType(Ogre::Light::LT_POINT);
	pointLight->setDiffuseColour(.3, .3, .3);
	pointLight->setSpecularColour(.3, .3, .3); 
	pointLight->setPosition(Ogre::Vector3(50, 50, 50));

	// Point light
	Ogre::Light* directionalLight = mSceneMgr->createLight("DirectionalLight");
	directionalLight->setType(Ogre::Light::LT_DIRECTIONAL);
	directionalLight->setDiffuseColour(.4, 0, 0);
	directionalLight->setSpecularColour(.4, 0, 0); 
	

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

	groundEntity->setMaterialName("Examples/BumpyMetal");

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
	//mSceneMgr = mSceneMgrArr[0]; // active SceneManager
	mSceneMgr = mSceneMgrArr[1]; // active SceneManager
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

    if (arg.key == OIS::KC_1 ) {
        mCameraMan->getCamera()
            ->setPosition(Vector3(98.14,	450.69,	964.20));
        mCameraMan->getCamera()
            ->setDirection(Vector3(-0.01,	-0.30,	-0.95));

        //98.14	450.69	964.20
        //-0.01	-0.30	-0.95
    }

    if (arg.key == OIS::KC_2 ) {
        // add your own stuff
        //-1463.00	606.45	-513.24
        //0.88	-0.47	0.10
    }

    if (arg.key == OIS::KC_3 ) {
        // add your own stuff
        //-1356.16	634.32	-964.51
        //0.71	-0.44	0.55
    }

    if (arg.key == OIS::KC_4 ) {
         // add your own stuff
        //40.39	155.23	251.20
        //-0.02	-0.41	-0.91
    }

    if (arg.key == OIS::KC_5 ) {
        // add your own stuff
        //19.94	822.63	30.79
        //0.00	-0.99	-0.11
    }

    if (arg.key == OIS::KC_M ) {
        
       Camera *c_ptr = mCameraArr[0];
       mWindow->removeViewport(mViewportArr[0]->getZOrder());
	Ogre::Viewport* vp = mWindow->addViewport(
        c_ptr,
        0,
        0.15,
        0.55,
        0.45,
        0.3
        );
	vp->setBackgroundColour(Ogre::ColourValue(0,0.5,0.0));
	c_ptr->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
   //delete mViewportArr[0];    // program crashes
    mViewportArr[0] = vp;       // make sure to save the new pointer
    
    }

    if (arg.key == OIS::KC_N ) {
        // add your own stuff
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

bool BasicTutorial_00::frameStarted(const Ogre::FrameEvent& evt)
{
	bool flg = Ogre::FrameListener::frameStarted(evt);
    //
    // add your own stuff
    //
    return flg;
}
int main(int argc, char *argv[]) {
	BasicTutorial_00 app;
	app.go();  
	return 0;
}
