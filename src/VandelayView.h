#ifndef VANDELAY_VIEW_H
#define VANDELAY_VIEW_H

#include <Alert.h>
#include <Box.h>
#include <MenuBar.h>
#include <MenuField.h>
#include <MenuItem.h>
#include <PopUpMenu.h>
#include <TextControl.h>
#include <View.h>


/*------Create-new-BView-class-------------------------------------*/
class VandelayView : public BView 
{
	public:
		VandelayView(BRect frame, const char *name); 
};

/*------Create-new-BMenuBar-class----------------------------------*/
class VanMenuBar : public BMenuBar
{
	public:
		VanMenuBar(BRect frame, const char *name);
};

/*------Create-new-BMenu-class-------------------------------------*/
class VanMenu : public BMenu
{
	public:
		VanMenu(const char *name);
};

/*------Create-new-BBox-class--------------------------------------*/
class VanBox : public BBox
{
	public:
		VanBox(BRect frame, const char *name);
};

/*------Create-new-BAlert-class------------------------------------*/
class VanAlert : public BAlert
{
	public:
		VanAlert(const char *title, const char *text, const char *button0Label, 
			const char *button1Label, const char *button2Label);
};

/*------Create-new-BTextControl-class------------------------------*/
class VanTextControl : public BTextControl
{
	public:
		VanTextControl(BRect frame, const char *name, const char *label, 
			const char *text, BMessage *message);
};

/*------Create-new-BMenuField-class--------------------------------*/
class VanMenuField : public BMenuField
{
	public:
		VanMenuField(BRect frame, const char *name, const char *label, BMenu *menu);
};

#endif // VANDELAY_VIEW_H