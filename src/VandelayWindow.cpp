#include <Application.h>
#include <LayoutBuilder.h>
#include <Alert.h>
#include "VandelayWindow.h"
#include "Constants.h"
#include "VandelayEngine.h"



/*------Create-new-BWindow-class--------------------------------------*/
VandelayWindow::VandelayWindow()
		: BWindow(BRect(0,0,-1,-1), "Vandelay", B_TITLED_WINDOW, B_NOT_RESIZABLE | B_NOT_ZOOMABLE)
{
	
	// Resize and Center Window on Screen
	ResizeTo(400,300);
	CenterOnScreen();
	
	// Assign B_PANEL_BACKGROUND_COLOR to 'bgcolor'
	rgb_color bgcolor = ui_color(B_PANEL_BACKGROUND_COLOR);
	
	// Set up a rectangle and make a new view
	VanView = new BView("VandelayView", B_WILL_DRAW);
	
	// Create new BMenuBar
	vanmenubar = new BMenuBar("VanMenuBar");
	
	// Create new BMenu
	filemenu = new BMenu("File");
	
	// Add menu items to BMenu
	
	BMenuItem * item = new BMenuItem("About" , new BMessage(B_ABOUT_REQUESTED));
	item->SetTarget(be_app);
	filemenu->AddItem(item);
	filemenu->AddSeparatorItem();
	filemenu->AddItem(new BMenuItem("Quit", new BMessage(MENU_FILE_QUIT), 'Q', B_COMMAND_KEY));
	
	// Add BMenu to BMenuBar
	vanmenubar->AddItem(filemenu);
	
	
	// Create new BTextControl        
	vantextcontrol = new BTextControl("InputBox", NULL, "Enter #", new BMessage(CONVERT_FROM_VALUE));
	vantextcontrol->SetDivider(45.0);
	vantextcontrol->SetModificationMessage(new BMessage(CONVERT_FROM_VALUE_MODMSG));
	
	
	/*------Create-new-BMenuField-----------------------------*/
	// Create new BMenu
	vanmenufrom = new BMenu("<Select Unit>");
	vanmenuto = new BMenu("<Select Unit>");
				
	// Add menu items to BMenus      // Distance
	vanmenufrom->AddItem(new BMenuItem("Foot", new BMessage(CONVERT_FROM_FOOT)));
	vanmenufrom->AddItem(new BMenuItem("Kilometer", new BMessage(CONVERT_FROM_KILOMETER)));
	vanmenufrom->AddItem(new BMenuItem("Meter", new BMessage(CONVERT_FROM_METER)));
	vanmenufrom->AddItem(new BMenuItem("Mile(US)", new BMessage(CONVERT_FROM_MILEUS)));
	vanmenufrom->AddSeparatorItem(); // Power
	vanmenufrom->AddItem(new BMenuItem("Horsepower", new BMessage(CONVERT_FROM_HORSEPOWER)));
	vanmenufrom->AddItem(new BMenuItem("Kilowatt", new BMessage(CONVERT_FROM_KILOWATT)));
	vanmenufrom->AddSeparatorItem(); // Temperature
	vanmenufrom->AddItem(new BMenuItem("Celsius", new BMessage(CONVERT_FROM_CELSIUS)));
	vanmenufrom->AddItem(new BMenuItem("Fahrenheit", new BMessage(CONVERT_FROM_FAHRENHEIT)));
	vanmenufrom->AddSeparatorItem(); // Volume
	vanmenufrom->AddItem(new BMenuItem("Gallon(US)", new BMessage(CONVERT_FROM_GALLONUS)));
	vanmenufrom->AddItem(new BMenuItem("Litre", new BMessage(CONVERT_FROM_LITRE)));
	vanmenufrom->AddSeparatorItem(); // Weight
	vanmenufrom->AddItem(new BMenuItem("Kilogram", new BMessage(CONVERT_FROM_KILOGRAM)));
	vanmenufrom->AddItem(new BMenuItem("Pound", new BMessage(CONVERT_FROM_POUND)));
	
									 // Distance
	vanmenuto->AddItem(new BMenuItem("Foot", new BMessage(CONVERT_TO_FOOT)));
	vanmenuto->AddItem(new BMenuItem("Kilometer", new BMessage(CONVERT_TO_KILOMETER)));
	vanmenuto->AddItem(new BMenuItem("Meter", new BMessage(CONVERT_TO_METER)));
	vanmenuto->AddItem(new BMenuItem("Mile(US)", new BMessage(CONVERT_TO_MILEUS)));
	vanmenuto->AddSeparatorItem(); // Power
	vanmenuto->AddItem(new BMenuItem("Horsepower", new BMessage(CONVERT_TO_HORSEPOWER)));
	vanmenuto->AddItem(new BMenuItem("Kilowatt", new BMessage(CONVERT_TO_KILOWATT)));
	vanmenuto->AddSeparatorItem(); // Temperature
	vanmenuto->AddItem(new BMenuItem("Celsius", new BMessage(CONVERT_TO_CELSIUS)));
	vanmenuto->AddItem(new BMenuItem("Fahrenheit", new BMessage(CONVERT_TO_FAHRENHEIT)));
	vanmenuto->AddSeparatorItem(); // Volume
	vanmenuto->AddItem(new BMenuItem("Gallon(US)", new BMessage(CONVERT_TO_GALLONUS)));
	vanmenuto->AddItem(new BMenuItem("Litre", new BMessage(CONVERT_TO_LITRE)));
	vanmenuto->AddSeparatorItem(); // Weight
	vanmenuto->AddItem(new BMenuItem("Kilogram", new BMessage(CONVERT_TO_KILOGRAM)));
	vanmenuto->AddItem(new BMenuItem("Pound", new BMessage(CONVERT_TO_POUND)));
		
	// Create new BMenuField
	vanmenufieldfrom = new BMenuField("VanMenuFieldFrom", NULL, vanmenufrom);
	vanmenufieldfrom->SetDivider(32.0);
	vanmenufieldfrom->Menu()->SetLabelFromMarked(true);
	vanmenufieldfrom->SetEnabled(false);
	
	vanmenufieldto = new BMenuField("VanMenuFieldTo", NULL, vanmenuto);
	vanmenufieldto->SetDivider(32.0);
	vanmenufieldto->SetAlignment(B_ALIGN_RIGHT);	
	vanmenufieldto->Menu()->SetLabelFromMarked(true);
	vanmenufieldto->SetEnabled(false);
	
	vanfromtext= new BStringView( "input_label", "Convert From");
	vantotext= new BStringView("output_label", "Convert To");
	
	/*------Create-a-result-view------------------------------*/
	vanresultcontrol = new BTextControl("VanResultControl", NULL, NULL, NULL);
	vanresultcontrol->SetDivider(35.0);
	
	
	/*------Set-views-background-colors-----------------------*/
	VanView->SetViewColor(bgcolor);
	vanbox->SetViewColor(bgcolor);
	
	
	BLayoutBuilder::Group<>(VanView, B_VERTICAL)
		.SetInsets(20)
		.AddGrid()
			.Add(vanfromtext,0,0)	
			.Add(vanmenufieldfrom,1,0)
			.Add(vantextcontrol,0,1,2,1)
			.Add(vantotext,0,2)	
			.Add(vanmenufieldto,1,2)
			.Add(vanresultcontrol,0,3,2,1)
		.End()
	.End();
	
	
	BLayoutBuilder::Group<>(this, B_VERTICAL, B_USE_WINDOW_SPACING)
		.SetInsets(0)
		.Add(vanmenubar)
		.AddGlue()
		.Add(VanView)
		.AddGlue()
    .End();

}


/*------MUST-HAVE-for-closing-app-with-close-box------------------------*/
bool VandelayWindow::QuitRequested()
{
	be_app->PostMessage(B_QUIT_REQUESTED);
	return(true);
}


/*------VandelayWindow-BMessage-Switch----------------------------------*/
void VandelayWindow::MessageReceived(BMessage *message)
{
	switch(message->what)
	{

		case MENU_FILE_QUIT:
			be_app->PostMessage(B_QUIT_REQUESTED);
		break;
		
		// Convert value modification message
		case CONVERT_FROM_VALUE_MODMSG:
			vanmenufieldfrom->SetEnabled(true);
		break;
		
		// Convert Value
		case CONVERT_FROM_VALUE:
			InputValue = atof(vantextcontrol->TextView()->Text());
		break;
		
		// Convert From
		case CONVERT_FROM_FOOT:
		{
			FromValue = 0;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_KILOMETER:
		{
			FromValue = 1;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_METER:
		{
			FromValue = 2;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_MILEUS:
		{
			FromValue = 3;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_HORSEPOWER:
		{
			FromValue = 4;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_KILOWATT:
		{
			FromValue = 5;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_CELSIUS:
		{
			FromValue = 6;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_FAHRENHEIT:
		{
			FromValue = 7;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_GALLONUS:
		{
			FromValue = 8;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_LITRE:
		{
			FromValue = 9;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_KILOGRAM:
		{
			FromValue = 10;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		case CONVERT_FROM_POUND:
		{
			FromValue = 11;
			vanmenufieldto->SetEnabled(true);
		}
		break;
		
		// Convert To
		case CONVERT_TO_FOOT:
		{
			BString line;
			ToValue = 0;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_KILOMETER:
		{
			BString line;
			ToValue = 1;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_METER:
		{
			BString line;
			ToValue = 2;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_MILEUS:
		{
			BString line;
			ToValue = 3;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_HORSEPOWER:
		{
			BString line;
			ToValue = 4;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_KILOWATT:
		{
			BString line;
			ToValue = 5;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_CELSIUS:
		{
			BString line;
			ToValue = 6;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_FAHRENHEIT:
		{
			BString line;
			ToValue = 7;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_GALLONUS:
		{
			BString line;
			ToValue = 8;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_LITRE:
		{
			BString line;
			ToValue = 9;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_KILOGRAM:
		{
			BString line;
			ToValue = 10;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		case CONVERT_TO_POUND:
		{
			BString line;
			ToValue = 11;
			Result = VanConvert(InputValue, FromValue, ToValue);
			line << Result;
			vanresultcontrol->TextView()->SetText(line.String());
		}
		break;
		
		
		default:
			BWindow::MessageReceived(message);
		break;
	}
}

