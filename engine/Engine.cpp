#include "Engine.hpp"

#include <iostream>
#include <boost/bind.hpp>
#include <GL/glu.h>
#include <SDL2/SDL.h>


Engine::Engine(string name, GLuint scrW, GLuint scrH, int flags) :
	cam(Camera(scrW, scrH)),
	running(false),
	scrW(scrW),
	scrH(scrH),
	flags(flags),
	evHandler(EventHandler())
{
	initSDL(name);
	initOpenGL();
	glewInit();
	initEvents();
}

EventHandler& Engine::getEventHandler() {
	return evHandler;
}

void Engine::registerRenderFunc(render_func renderFunc) {
	this->renderFunc = renderFunc;
}

void Engine::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	currentTime = SDL_GetTicks();

	cam.look();

	evHandler.handle();
	renderFunc(currentTime, *this);

	if (flags & engineFlags::SHOW_FPS) {
		fps(currentTime);
	}

	handleErrors();

	SDL_GL_SwapWindow(window);
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

/**
 * Initialize SDL
 *
 */
void Engine::initSDL(string name) {

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS);

	window = SDL_CreateWindow(
			name.c_str(), 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			scrW,
			scrH,
			SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL
	);

	SDL_GL_CreateContext(window);
	atexit(SDL_Quit);
}


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

	glEnable(GL_POLYGON_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
	glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	glViewport(0,0,scrW, scrH);
	glMatrixMode(GL_PROJECTION);

	gluPerspective(45.0f,(GLfloat)scrW/(GLfloat)scrH, 1.0f, 150.0f);
	glMatrixMode(GL_MODELVIEW); // Select The Modelview Matrix
	glLoadIdentity();

	glEnable(GL_DEPTH_TEST);


	cam.positionCamera(0, 0, 20,   0, 0, 0,   0, 1, 0);
}




void Engine::initEvents() {
	evHandler.registerVideoResizeCallback (boost::bind(&Engine::videoResize, this, _1));
	evHandler.registerQuitCallback        (boost::bind(&Engine::quit, this, _1));

	evHandler.registerKey(SDLK_ESCAPE, boost::bind(&Engine::quit, this, _1));
}

void Engine::toggleDebugCamera() {
	
	if (debugCameraActive) {
		evHandler.unregisterKey(SDLK_w);
		evHandler.unregisterKey(SDLK_a);
		evHandler.unregisterKey(SDLK_s);
		evHandler.unregisterKey(SDLK_d);

		evHandler.unregisterMouseMotion();
	} 
	else {
		evHandler.registerMouseMotionCallback (
				boost::bind(&Engine::mouseMotion, this, _1)
		);

		evHandler.registerKey(
				SDLK_w,
				boost::bind(&Engine::cameraForwardMovement, this, _1)
		);

		evHandler.registerKey(
				SDLK_s,
				boost::bind(&Engine::cameraBackwardMovement, this, _1)
		);

		evHandler.registerKey(
				SDLK_a,
				boost::bind(&Engine::cameraLeftMovement, this, _1)
		);

		evHandler.registerKey(
				SDLK_d,
				boost::bind(&Engine::cameraRightMovement, this, _1)
		);
	}

	debugCameraActive = !debugCameraActive;
}

void Engine::cameraForwardMovement(SDL_Event &event) {
	cam.moveCamera(cameraSpeed);
}

void Engine::cameraBackwardMovement(SDL_Event &event) {
	cam.moveCamera(-cameraSpeed);
}

void Engine::cameraLeftMovement(SDL_Event &event) {
	cam.strafeCamera(-cameraSpeed);
}

void Engine::cameraRightMovement(SDL_Event &event) {
	cam.strafeCamera(cameraSpeed);
}

/**
 * Resize event
 */
void Engine::videoResize(SDL_Event &event) {
	scrH = event.window.data1;
	scrW = event.window.data2;

	cam.windowResize(scrH, scrW);
}

/**
 * Mouse motion event
 */
void Engine::mouseMotion(SDL_Event &event) {
	Sint16 mouseX = event.motion.x;
	Sint16 mouseY = event.motion.y;
	cam.update(mouseX, mouseY);
}

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

