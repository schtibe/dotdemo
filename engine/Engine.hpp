#ifndef __ENGINE_HPP_
#define __ENGINE_HPP_

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <SDL2/SDL.h>
#include <string>


#include "EventHandler.hpp"
#include "Camera.hpp"


using namespace std;

enum engineFlags{
	NONE     = 0x01,
	SHOW_FPS = 0x02,
	PRINT_VERSION = 0x04,
	RUN_FULLSCREEN = 0x08
};


class Engine;

typedef boost::function<void (GLuint, Engine)> render_func;

class Engine {
	public:
		//static Engine& inst();
		Engine(string name, GLuint scrW, GLuint scrH, int flags);

		EventHandler& getEventHandler();

		void registerRenderFunc(render_func);
		void run();

		void init(GLuint scrW, GLuint srcH);
		Camera cam;

		void toggleDebugCamera();
	private:

		//static Engine *instance;

		GLboolean running;
		GLuint scrW      = 1280;
		GLuint scrH      = 1024;
		GLuint clrDepth  = 24;
		int flags;

		GLuint currentTime = 0;

		EventHandler evHandler;

		void initSDL(string name);
		void initOpenGL();
		void initEvents();

		void render();

		// events
		void videoResize(SDL_Event &event);
		void mouseMotion(SDL_Event &event);
		void quit(SDL_Event &event);
		void cameraForwardMovement(SDL_Event &event);
		void cameraBackwardMovement(SDL_Event &event);
		void cameraLeftMovement(SDL_Event &event);
		void cameraRightMovement(SDL_Event &event);

		SDL_Window *window;

		void handleErrors();

		bool debugCameraActive       = false;
		GLfloat cameraSpeed          = 0.5;

		render_func renderFunc;

		GLuint frameCounter = 0;
		GLuint lastDraw;
		GLuint timer;
		void fps(GLuint time);
};

#endif
