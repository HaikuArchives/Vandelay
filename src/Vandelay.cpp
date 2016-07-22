#include "VandelayWindow.h"
#include "Vandelay.h"


int main(int, char**)
{	
	VandelayApp VanApp;

	VanApp.Run();

	return(0);
}

VandelayApp::VandelayApp()
		: BApplication("application/x-vnd.Blum-Vandelay")
{
	VandelayWindow *VanWindow;
	BRect WindowRect;

	// Set up a rectangle and make a new window
	WindowRect.Set(100, 100, 400, 300);
	VanWindow = new VandelayWindow(WindowRect);
			
	// make window visible
	VanWindow->Show();
}