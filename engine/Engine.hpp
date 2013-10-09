#ifndef __ENGINE_HPP_
#define __ENGINE_HPP_

#include <GL/glew.h>

#include <GL/gl.h>
#include <GL/glx.h>
#include <SDL2/SDL.h>
#include <string>

#include <boost/function.hpp>


#ifdef XSCREENSAVER
#include<X11/X.h>
#include<X11/Xlib.h>
#endif


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

		void registerRenderFunc(render_func);
		void run();



	private:

		GLuint scrW      = 1280;
		GLuint scrH      = 1024;
		//static Engine *instance;

		GLboolean running;
		GLuint clrDepth  = 24;
		int flags;


		void initOpenGL();
		void init(GLuint scrW, GLuint srcH);
		void render();
		void quit(SDL_Event &event);


		// events
#ifndef XSCREENSAVER
		void initSDL(string name);
		void videoResize(SDL_Event &event);
		void initEvents();
#else
		void initXWindow();
#endif

		SDL_Window *window;
		SDL_GLContext  context;

		void handleErrors();


		render_func renderFunc;

		GLuint frameCounter = 0;
		GLuint lastDraw;
		GLuint timer;
		void fps(GLuint time);

#ifdef XSCREENSAVER
		Display     *dpy;
		Window      root;
		Window win;
		GLint       att[5] = {
			GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None
		};
		XVisualInfo *vi;
		GLXContext  glc;
#endif
};

#endif
