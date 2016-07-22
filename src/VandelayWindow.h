#ifndef VANDELAY_WINDOW_H
#define VANDELAY_WINDOW_H

#include <Window.h>
#include <String.h>
#include <stdlib.h>


/*------Create-new-BWindow-class--------------------------------*/
class VandelayWindow : public BWindow 
{
	public:
		VandelayWindow(BRect frame);
		virtual void MessageReceived(BMessage *message);
		virtual	bool QuitRequested();
};

#endif // VANDELAY_WINDOW_H