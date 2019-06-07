
#include <GtServer.h> 
#include <GtWorldLoader.h> 
#include <GtWorlddata.h> 
#include <GtProgress.h> 
#include <GtApp.h> 
#include <GtSplash.h> 

extern "C" {
	int DLL_EXPORT initGtLib () {

		GtServer::init();

		// while (!GtServer::lastVisited().size()) {	
		// }

		return 0;
	}
}

