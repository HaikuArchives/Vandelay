#ifndef VANDELAY_H
#define VANDELAY_H

#include <Application.h>

#include "VandelayWindow.h"


class VandelayApp : public BApplication {
public:
		VandelayApp();

	void	AboutRequested();
		
private:
	VandelayWindow*	fMainWindow;
};

#endif // VANDELAY_H
