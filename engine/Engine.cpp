#include "Engine.hpp"

#include <iostream>
#include <boost/bind.hpp>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include "Camera.hpp"

#include "EventHandler.hpp"


#ifdef XSCREENSAVER
#include "vroot.h"
#endif


Engine::Engine(string name, GLuint scrW, GLuint scrH, int flags) :
	scrW(scrW),
	scrH(scrH),
	running(false),
	flags(flags)
{
#ifdef XSCREENSAVER
	initXWindow();
#else
	initSDL(name);
#endif
	initOpenGL();
	glewInit();
#ifndef XSCREENSAVER
	initEvents();
#endif

	Camera::inst()->setRes(scrW, scrH);


	EventHandler::inst()->registerMouseMotionCallback(
			boost::bind(&Camera::mouseMotion, Camera::inst(), _1)
		);
}


void Engine::registerRenderFunc(render_func renderFunc) {
	this->renderFunc = renderFunc;
}

void Engine::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	GLuint currentTime = SDL_GetTicks();

	EventHandler::inst()->handle();
	renderFunc(currentTime, *this);

	if (flags & engineFlags::SHOW_FPS) {
		fps(currentTime);
	}

	handleErrors();

#ifdef XSCREENSAVER
	glXSwapBuffers(dpy, root);
#else
	SDL_GL_SwapWindow(window);
#endif
}

void Engine::fps(GLuint time) {
	frameCounter++;

	timer += time - lastDraw;

	if (timer > 1000) {
		cout << frameCounter << " frames per second" << endl;
		timer = 0;
		frameCounter = 0;
	}
	lastDraw = time;
}

void Engine::run() {
	running = true;

	while (running) {
		render();
	}

	// cleanup
	SDL_Quit();
}

#ifdef XSCREENSAVER
void Engine::initXWindow() {

	// we still need this for the time
	SDL_Init(SDL_INIT_EVENTS);

	if ( ! (dpy = XOpenDisplay("unix:0")) ) {
		cerr << "cannot connect to X server\n\n" << endl;
		exit(1);
	}

	/* get root window */
	root = VirtualRootWindowOfScreen(DefaultScreenOfDisplay(dpy));

	XWindowAttributes attrs;
	XGetWindowAttributes(dpy, root, &attrs);

	scrW = attrs.width;
	scrH = attrs.height;

	Camera::inst()->setRes(scrW, scrH);
	
	/* get visual matching attr */
	if( ! (vi = glXChooseVisual(dpy, 0, att)) ) {
		cerr <<  "no appropriate visual found\n\n" << endl;
		exit(1);
	}

		/* create a context using the root window */
	if ( ! (glc = glXCreateContext(dpy, vi, NULL, GL_TRUE)) ){
			cerr << "failed to create context\n\n" << endl;
			exit(1);
	}

	glXMakeCurrent(dpy, root, glc);
}
#else

/**
 * Initialize SDL
 *
 */
void Engine::initSDL(string name) {

	SDL_Init(SDL_INIT_EVENTS);

	int sdlFlags = SDL_WINDOW_OPENGL;

	if (flags & RUN_FULLSCREEN) {
		SDL_DisplayMode mode;
		SDL_GetCurrentDisplayMode(0, &mode);

		scrW = mode.w;
		scrH = mode.h;

		sdlFlags = sdlFlags | SDL_WINDOW_FULLSCREEN;
	}
	else {
		sdlFlags = sdlFlags | SDL_WINDOW_RESIZABLE;
	}

	window = SDL_CreateWindow(
			name.c_str(), 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			scrW,
			scrH,
			sdlFlags
	);

	context = SDL_GL_CreateContext(window);
	atexit(SDL_Quit);
}

#endif


/**
 * Initialize OpenGL
 */
void Engine::initOpenGL() {
	if (flags & PRINT_VERSION) {
		cout << "Renderer: " << glGetString(GL_RENDERER) << endl;
		cout << "Vendor: " << glGetString(GL_VENDOR) << endl;
		cout << "Version: " << glGetString(GL_VERSION) << endl;
	}

	glShadeModel(GL_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glMatrixMode(GL_PROJECTION);

	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);
}



#ifndef XSCREENSAVER
void Engine::initEvents() {
	EventHandler::inst()->registerVideoResizeCallback (boost::bind(&Engine::videoResize, this, _1));
	EventHandler::inst()->registerQuitCallback        (boost::bind(&Engine::quit, this, _1));

	EventHandler::inst()->registerKey(SDL_SCANCODE_ESCAPE, boost::bind(&Engine::quit, this, _1));

	EventHandler::inst()->registerKey(SDL_SCANCODE_D, boost::bind(&Camera::stride, Camera::inst(), _1));
	EventHandler::inst()->registerKey(SDL_SCANCODE_A, boost::bind(&Camera::stride, Camera::inst(), _1));
}


/**
 * Resize event
 */
void Engine::videoResize(SDL_Event &event) {
	scrW = event.window.data1;
	scrH = event.window.data2;

	Camera::inst()->setRes(scrW, scrH);
}
#endif


void Engine::quit(SDL_Event &event) {
	running = false;
}

void Engine::handleErrors() {
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		errString = gluErrorString(errCode);
		cerr << "OpenGL Error: " << errString << endl;
	}
}

