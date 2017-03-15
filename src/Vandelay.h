#ifndef VANDELAY_H
#define VANDELAY_H

#include <Application.h>
#include "VandelayWindow.h"


/*------Create-new-BApplication-class-----------------*/
class VandelayApp : public BApplication 
{
	public:
		VandelayApp();
		void AboutRequested();
		
	
	private:
		VandelayWindow * VanWindow;
};

#endif // VANDELAY_H
