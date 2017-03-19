#ifndef VANDELAY_WINDOW_H
#define VANDELAY_WINDOW_H


#include <Alert.h>
#include <Box.h>
#include <Button.h>
#include <MenuBar.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <String.h>
#include <StringView.h>
#include <TextControl.h>
#include <View.h>
#include <Window.h>

#include <stdlib.h>


class VandelayWindow : public BWindow 
{
public:
			VandelayWindow();
	virtual void 	MessageReceived(BMessage *message);
	virtual	bool 	QuitRequested();
		
	void 		ClearTextFields();
	void 		ComputeResult();
		
private:
	
	float 		fInputValue;
	float		fResult; 
	int 		fFromValue;
	int		fToValue; 
		
	BView*		fBack;
	BMenuBar*	fMenuBar;
	BMenu*		fAppMenu;
	BMenu*		fMenuFrom;
	BMenu*		fMenuTo;
	BTextControl*	fInputText;
	BMenuField*	fMenuFieldFrom;
	BMenuField*	fMenuFieldTo;
	BTextControl*	fResultText;
	BStringView*	fLabelFrom;
	BStringView*	fLabelTo;
	BButton*	fBtnClear;
	BButton*	fBtnCompute;
};

#endif // VANDELAY_WINDOW_H
