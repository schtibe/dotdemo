#ifndef __EVENT_HANDLER_H
#define __EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <boost/function.hpp>
#include <map>
#include <boost/container/map.hpp>

//using std::map;
using boost::container::map;

typedef boost::function<void (SDL_Event&)> callback;

class EventHandler {
	public:
		EventHandler();

		void handle();

		void registerVideoResizeCallback(callback);
		void registerMouseMotionCallback(callback);
		void registerQuitCallback(callback);


		void registerKey(SDL_Keycode key        , callback);
		void registerKeyOnce(SDL_Keycode key    , callback);
		void registerKeyRelease(SDL_Keycode key , callback);

		void unregisterKey(SDL_Keycode key);

		void unregisterMouseMotion();


	private:
		static const unsigned int sdlKeyAmount = 1000;

		SDL_Event event;

		void actualHandle(SDL_Event &);
		void handleKeys(SDL_Event &event);
		void cycle();
		void keyDown(SDL_Keycode &);
		void keyUp(SDL_Keycode &);

		map<SDL_Keycode, bool> keysHeld;

		callback videoResize;
		callback mouseMotion;
		callback quit;

		map<SDL_Keycode, callback> keyFunc;
		map<SDL_Keycode, callback> keyReleaseFunc;
		map<SDL_Keycode, callback> keyFuncOnce;


};



#endif
