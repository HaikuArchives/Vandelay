#ifndef VANDELAY_WINDOW_H
#define VANDELAY_WINDOW_H

#include <Window.h>
#include <String.h>
#include <stdlib.h>
#include <Alert.h>
#include <Box.h>
#include <MenuBar.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <TextControl.h>
#include <StringView.h>
#include <View.h>


/*------Create-new-BWindow-class--------------------------------*/
class VandelayWindow : public BWindow 
{
	public:
		VandelayWindow();
		virtual void MessageReceived(BMessage *message);
		virtual	bool QuitRequested();
		
		
	private:
	
		float 			InputValue, Result; // Store Input And Result value
		int 			FromValue, ToValue; // Store From and To number
		
		BView*			VanView;
		BMenuBar*		vanmenubar;
		BMenu*			filemenu;
		BMenu*			vanmenufrom;
		BMenu*			vanmenuto;
		BTextControl*		vantextcontrol;
		BMenuField*		vanmenufieldfrom;
		BMenuField*		vanmenufieldto;
		BTextControl*		vanresultcontrol;
		BStringView*		vanfromtext;
		BStringView*		vantotext;
	
};

#endif // VANDELAY_WINDOW_H
