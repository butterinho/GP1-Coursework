#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one


#include <windows.h>
#include <mmsystem.h>
#include "windowOGL.h"
#include "GameConstants.h"
#include "cWNDManager.h"
#include "cInputMgr.h"
#include "cSprite.h"
#include "asteroidsGame.h"

int WINAPI WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR cmdLine,
	int cmdShow)
{

	//Set our window settings
	const int windowWidth = 1024;
	const int windowHeight = 768;
	const int windowBPP = 16;



	//This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	//The example OpenGL code
	windowOGL theOGLWnd;

	//Attach our the OpenGL window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);

	// Cube

	//Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
	{
		//If it fails

		MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
	{
		MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		return 1;
	}

	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	/* initialize random seed: */
	srand((unsigned int)time(NULL));

	// Create vector array of textures
	LPCSTR texturesToUse[] = { "Images\\asteroid1.png", "Images\\asteroid2.png", "Images\\asteroid3.png", "Images\\asteroid4.png", "Images\\bullet.png" };
	for (int tCount = 0; tCount < 5; tCount++)
	{
		theGameTextures.push_back(new cTexture());
		theGameTextures[tCount]->createTexture(texturesToUse[tCount]);
	}





	PlaySound("Audio\\Music.wav", NULL, SND_ASYNC); //Plays Start-up Music
	
	// Create vector array of textures











		cTexture textureBkgd;
		textureBkgd.createTexture("Images\\Road-Straight.png"); // Renders BackGround
		cBkGround spriteBkgd;
		spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
		spriteBkgd.setTexture(textureBkgd.getTexture());
		spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());
		
		

		cTexture rocketTxt;
		rocketTxt.createTexture("Images\\Car.png");
		cRocket rocketSprite;
		rocketSprite.attachInputMgr(theInputMgr); // Attach the input manager to the sprite
		rocketSprite.setSpritePos(glm::vec2(512.0f, 380.0f));
		rocketSprite.setTexture(rocketTxt.getTexture());
		rocketSprite.setTextureDimensions(rocketTxt.getTWidth(), rocketTxt.getTHeight());
		rocketSprite.setSpriteCentre();
		rocketSprite.setRocketVelocity(glm::vec2(0.0f, 0.0f));





		for (int astro = 0; astro < 10; astro++) //renders in car sprites 

		{
			theAsteroids.push_back(new cAsteroid);
			theAsteroids[astro]->setSpritePos(glm::vec2(windowWidth / (rand() % 5 + 1), 0));
			theAsteroids[astro]->setSpriteTranslation(glm::vec2(0.0f, 15.0f));
			theAsteroids[astro]->setTexture(theGameTextures[rand() % 4]->getTexture());
			theAsteroids[astro]->setTextureDimensions(theGameTextures[rand() % 4]->getTWidth(), theGameTextures[rand() % 4]->getTHeight());
			theAsteroids[astro]->setSpriteCentre();
			theAsteroids[astro]->setAsteroidVelocity(glm::vec2(glm::vec2(0.0f, 0.0f)));
			theAsteroids[astro]->setActive(true);
			theAsteroids[astro]->setMdlRadius();

		}

	


		
		int Left = 5;

		//This is the mainloop, we render frames until isRunning returns false
		while (pgmWNDMgr->isWNDRunning())
		{
			pgmWNDMgr->processWNDEvents(); //Process any window events

			//We get the time that passed since the last frame
			float elapsedTime = pgmWNDMgr->getElapsedSeconds();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


			{
				spriteBkgd.render();
				
				
				vector<cAsteroid*>::iterator index = theAsteroids.begin();
				while (index != theAsteroids.end())
				{
					if ((*index)->isActive() == false)
					{
						Left = (Left - 1);
						index = theAsteroids.erase(index);
						PlaySound("Audio\\Explosion2.wav", NULL, SND_ASYNC); //Plays Start-up Music
						if (Left == 0)
						{
							/*cTexture teTexture;
							textureBkgd.createTexture("Images\\Menu.png");
							cBkGround endbk;
							endbk.setSpritePos(glm::vec2(0.0f, 0.0f));
							endbk.setTexture(endTexture.getTexture());
							endbk.setTextureDimensions(endTexture.getTWidth(), endTexture.getTHeight());*/

							cTexture textureBkgd;
							textureBkgd.createTexture("Images\\Menu.png"); // Renders BackGround
							cBkGround spriteBkgd;
							spriteBkgd.setSpritePos(glm::vec2(0.0f, 0.0f));
							spriteBkgd.setTexture(textureBkgd.getTexture());
							spriteBkgd.setTextureDimensions(textureBkgd.getTWidth(), textureBkgd.getTHeight());

						}
					}
					else
					{
						(*index)->update(elapsedTime);
						(*index)->render();
						++index;


					}
				}

				rocketSprite.update(elapsedTime);
				rocketSprite.render();
			}
			pgmWNDMgr->swapBuffers();
			theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);




		}

		theOGLWnd.shutdown(); //Free any resources
		pgmWNDMgr->destroyWND(); //Destroy the program window



		return 0; //Return success


		







	}

	