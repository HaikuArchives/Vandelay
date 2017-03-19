#include <Alert.h>
#include <Application.h>
#include <LayoutBuilder.h>

#include "Constants.h"
#include "VandelayEngine.h"
#include "VandelayWindow.h"


VandelayWindow::VandelayWindow()
	: 
	BWindow(BRect(0, 0, -1, -1), "Vandelay", B_TITLED_WINDOW, 
		B_AUTO_UPDATE_SIZE_LIMITS)
{
	// Resize and Center Window on Screen
	ResizeTo(400,300);
	CenterOnScreen();
	
	// Assign B_PANEL_BACKGROUND_COLOR to 'bgcolor'
	rgb_color bgcolor = ui_color(B_PANEL_BACKGROUND_COLOR);
	
	// Set up a rectangle and make a new view
	fBack = new BView("Back", B_WILL_DRAW);
	
	// Create new BMenuBar
	fMenuBar = new BMenuBar("MenuBar");
	
	// Create new BMenu
	fAppMenu = new BMenu("App");
	
	// Add menu items to BMenu
	
	BMenuItem * item = new BMenuItem("About" , new BMessage(B_ABOUT_REQUESTED));
	item->SetTarget(be_app);
	fAppMenu->AddItem(item);
	fAppMenu->AddSeparatorItem();
	fAppMenu->AddItem(new BMenuItem("Quit", new 
		BMessage(MENU_APP_QUIT), 'Q', B_COMMAND_KEY));
	
	// Add BMenu to BMenuBar
	fMenuBar->AddItem(fAppMenu);
	
	// Create new BTextControl        
	fInputText = new BTextControl("InputText", NULL, "Enter the value to convert", NULL);
	
	// Create new BMenu
	fMenuFrom = new BMenu("<Select Unit>");
	fMenuTo = new BMenu("<Select Unit>");
				
	// Add menu items to BMenus      
	// Distance
	fMenuFrom->AddItem(new BMenuItem("Foot", new BMessage(CONVERT_FROM_FOOT)));
	fMenuFrom->AddItem(new BMenuItem("Kilometer", new BMessage(CONVERT_FROM_KILOMETER)));
	fMenuFrom->AddItem(new BMenuItem("Meter", new BMessage(CONVERT_FROM_METER)));
	fMenuFrom->AddItem(new BMenuItem("Mile(US)", new BMessage(CONVERT_FROM_MILEUS)));
	fMenuFrom->AddSeparatorItem(); 
	// Power
	fMenuFrom->AddItem(new BMenuItem("Horsepower", new BMessage(CONVERT_FROM_HORSEPOWER)));
	fMenuFrom->AddItem(new BMenuItem("Kilowatt", new BMessage(CONVERT_FROM_KILOWATT)));
	fMenuFrom->AddSeparatorItem(); 
	// Temperature
	fMenuFrom->AddItem(new BMenuItem("Celsius", new BMessage(CONVERT_FROM_CELSIUS)));
	fMenuFrom->AddItem(new BMenuItem("Fahrenheit", new BMessage(CONVERT_FROM_FAHRENHEIT)));
	fMenuFrom->AddSeparatorItem(); 
	// Volume
	fMenuFrom->AddItem(new BMenuItem("Gallon(US)", new BMessage(CONVERT_FROM_GALLONUS)));
	fMenuFrom->AddItem(new BMenuItem("Litre", new BMessage(CONVERT_FROM_LITRE)));
	fMenuFrom->AddSeparatorItem(); 
	// Weight
	fMenuFrom->AddItem(new BMenuItem("Kilogram", new BMessage(CONVERT_FROM_KILOGRAM)));
	fMenuFrom->AddItem(new BMenuItem("Pound", new BMessage(CONVERT_FROM_POUND)));
	
	 // Distance
	fMenuTo->AddItem(new BMenuItem("Foot", new BMessage(CONVERT_TO_FOOT)));
	fMenuTo->AddItem(new BMenuItem("Kilometer", new BMessage(CONVERT_TO_KILOMETER)));
	fMenuTo->AddItem(new BMenuItem("Meter", new BMessage(CONVERT_TO_METER)));
	fMenuTo->AddItem(new BMenuItem("Mile(US)", new BMessage(CONVERT_TO_MILEUS)));
	fMenuTo->AddSeparatorItem(); 
	// Power
	fMenuTo->AddItem(new BMenuItem("Horsepower", new BMessage(CONVERT_TO_HORSEPOWER)));
	fMenuTo->AddItem(new BMenuItem("Kilowatt", new BMessage(CONVERT_TO_KILOWATT)));
	fMenuTo->AddSeparatorItem(); 
	// Temperature
	fMenuTo->AddItem(new BMenuItem("Celsius", new BMessage(CONVERT_TO_CELSIUS)));
	fMenuTo->AddItem(new BMenuItem("Fahrenheit", new BMessage(CONVERT_TO_FAHRENHEIT)));
	fMenuTo->AddSeparatorItem(); 
	// Volume
	fMenuTo->AddItem(new BMenuItem("Gallon(US)", new BMessage(CONVERT_TO_GALLONUS)));
	fMenuTo->AddItem(new BMenuItem("Litre", new BMessage(CONVERT_TO_LITRE)));
	fMenuTo->AddSeparatorItem(); 
	// Weight
	fMenuTo->AddItem(new BMenuItem("Kilogram", new BMessage(CONVERT_TO_KILOGRAM)));
	fMenuTo->AddItem(new BMenuItem("Pound", new BMessage(CONVERT_TO_POUND)));
		
	// Create new BMenuField
	fMenuFieldFrom = new BMenuField("MenuFieldFrom", NULL, fMenuFrom);
	fMenuFieldFrom->Menu()->SetLabelFromMarked(true);
	
	fMenuFieldTo = new BMenuField("MenuFieldTo", NULL, fMenuTo);
	fMenuFieldTo->SetAlignment(B_ALIGN_RIGHT);	
	fMenuFieldTo->Menu()->SetLabelFromMarked(true);
	
	fLabelFrom = new BStringView("InputLabel", "Convert From");
	fLabelTo = new BStringView("OutputLabel", "Convert To");
	
	// Create a result view
	fResultText = new BTextControl("ResultText", NULL, NULL, NULL);
	
	// Create a Button
	fBtnClear = new BButton("ClearButton", "Clear", new BMessage(BTN_CLEAR_PRESSED));
		
	fBtnCompute = new BButton("ComputeButton", "Compute", new BMessage(BTN_COMPUTE_PRESSED));
	
	// Set view's background color
	fBack->SetViewColor(bgcolor);
	

	BLayoutBuilder::Group<>(fBack, B_VERTICAL)
		.SetInsets(20)
		.AddGrid()
			.Add(fLabelFrom, 0, 0)	
			.Add(fMenuFieldFrom, 1, 0)
			.Add(fInputText, 0, 1, 2, 1)
			.Add(fLabelTo, 0, 2)	
			.Add(fMenuFieldTo, 1, 2)
			.Add(fResultText, 0, 3, 2, 1)
		.End()
		.AddStrut(0)
		.AddGroup(B_HORIZONTAL)
			.AddGlue()
			.Add(fBtnCompute)
			.Add(fBtnClear)
		.End()
	.End();
	
	
	BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
		.Add(fMenuBar)
		.AddGlue()
		.Add(fBack)
		.AddGlue()
	.End();

}


bool 
VandelayWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return true;
}


void 
VandelayWindow::MessageReceived(BMessage *message)
{
	switch(message->what) {

		case MENU_APP_QUIT:
			be_app->PostMessage(B_QUIT_REQUESTED);
			break;

		// Convert From
		case CONVERT_FROM_FOOT:
			fFromValue = 0;
			break;
		
		case CONVERT_FROM_KILOMETER:
			fFromValue = 1;
			break;
		
		case CONVERT_FROM_METER:
			fFromValue = 2;
			break;

		case CONVERT_FROM_MILEUS:
			fFromValue = 3;
			break;
		
		case CONVERT_FROM_HORSEPOWER:
			fFromValue = 4;
			break;
		
		case CONVERT_FROM_KILOWATT:
			fFromValue = 5;
			break;
		
		case CONVERT_FROM_CELSIUS:
			fFromValue = 6;
			break;
	;
		case CONVERT_FROM_FAHRENHEIT:
			fFromValue = 7;
			break;
		
		case CONVERT_FROM_GALLONUS:
			fFromValue = 8;
			break;
		
		case CONVERT_FROM_LITRE:
			fFromValue = 9;
			break;
		
		case CONVERT_FROM_KILOGRAM:
			fFromValue = 10;
			break;
	
		case CONVERT_FROM_POUND:
			fFromValue = 11;
			break;
		
		// Convert To
		case CONVERT_TO_FOOT:
			fToValue = 0;
			break;
		
		case CONVERT_TO_KILOMETER:
			fToValue = 1;
			break;
		
		case CONVERT_TO_METER:
			fToValue = 2;
			break;
		
		case CONVERT_TO_MILEUS:
			fToValue = 3;
			break;
		
		case CONVERT_TO_HORSEPOWER:
			fToValue = 4;
			break;
		
		case CONVERT_TO_KILOWATT:
			fToValue = 5;
			break;
		
		case CONVERT_TO_CELSIUS:
			fToValue = 6;
			break;
		
		case CONVERT_TO_FAHRENHEIT:
			fToValue = 7;
			break;

		case CONVERT_TO_GALLONUS:
			fToValue = 8;
			break;
		
		case CONVERT_TO_LITRE:
			fToValue = 9;
			break;
		
		case CONVERT_TO_KILOGRAM:
			fToValue = 10;
			break;
		
		case CONVERT_TO_POUND:
			fToValue = 11;
			break;
		
		case BTN_COMPUTE_PRESSED:
			ComputeResult();
			break;
		
		case BTN_CLEAR_PRESSED:
			ClearTextFields();
			break;
		
		default:
			BWindow::MessageReceived(message);
			break;
	}
}


void 
VandelayWindow::ComputeResult(void)
{
	BString line;
	fInputValue = atof(fInputText->Text());
	fResult = VanConvert(fInputValue, fFromValue, fToValue);
	line << fResult;
	fResultText->SetText(line.String());

}


void 
VandelayWindow::ClearTextFields(void)
{
	fInputText->SetText("");
	fResultText->SetText("");
	
}

