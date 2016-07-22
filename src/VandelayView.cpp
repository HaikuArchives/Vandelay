#include "VandelayView.h"


/*------Create-new-BView-class-------------------------------------*/
VandelayView::VandelayView(BRect rect, const char *name)
		: BView(rect, name, B_FOLLOW_ALL, B_WILL_DRAW) {
	}

/*------Create-new-BMenuBar-class----------------------------------*/
VanMenuBar::VanMenuBar(BRect rect, const char *name)
		: BMenuBar(rect, name, B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP, B_ITEMS_IN_ROW, true) {
	}

/*------Create-new-BMenu-class-------------------------------------*/
VanMenu::VanMenu(const char *name)
		: BMenu(name, B_ITEMS_IN_COLUMN) {
	}

/*------Create-new-BBox-class--------------------------------------*/
VanBox::VanBox(BRect rect, const char *name)
		: BBox(rect, name, B_FOLLOW_ALL, B_WILL_DRAW) {
	}

/*------Create-new-BAlert-class------------------------------------*/
VanAlert::VanAlert(const char *title, const char *text, const char *button0Label, 
			const char *button1Label, const char *button2Label)
		: BAlert(title, text, button0Label, button1Label, button2Label, 
			B_WIDTH_FROM_LABEL, B_EVEN_SPACING, B_INFO_ALERT) {
	}

/*------Create-new-BTextControl-class------------------------------*/
VanTextControl::VanTextControl(BRect rect, const char *name, const char *label, 
			const char *text, BMessage *message)
		: BTextControl(rect, name, label, text, message, B_FOLLOW_ALL, B_WILL_DRAW 
			| B_NAVIGABLE) {
	}

/*------Create-new-BMenuField-class--------------------------------*/
VanMenuField::VanMenuField(BRect rect, const char *name, const char *label, BMenu *menu)
		: BMenuField(rect, name, label, menu, B_FOLLOW_ALL, B_WILL_DRAW | B_NAVIGABLE) {
	}