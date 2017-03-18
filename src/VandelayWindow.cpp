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
	filemenu->AddItem(new BMenuItem("Quit", new BMessage(MENU_APP_QUIT), 'Q', B_COMMAND_KEY));
	
	// Add BMenu to BMenuBar
	vanmenubar->AddItem(filemenu);
	
	
	// Create new BTextControl        
	vantextcontrol = new BTextControl("InputBox", NULL, "Enter the value to convert", NULL);
	
	
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
	vanmenufieldfrom->Menu()->SetLabelFromMarked(true);
	
	
	vanmenufieldto = new BMenuField("VanMenuFieldTo", NULL, vanmenuto);
	vanmenufieldto->SetAlignment(B_ALIGN_RIGHT);	
	vanmenufieldto->Menu()->SetLabelFromMarked(true);
	
	
	vanfromtext= new BStringView( "input_label", "Convert From");
	vantotext= new BStringView("output_label", "Convert To");
	
	/*------Create-a-result-view------------------------------*/
	vanresultcontrol = new BTextControl("VanResultControl", NULL, NULL, NULL);
	
	// Create a Button
	btnclear =
		new BButton("button_clear", "Clear", new BMessage(BTN_CLEAR_PRESSED));
		
	btncompute =
		new BButton("button_compute", "Compute", new BMessage(BTN_COMPUTE_PRESSED));
	
	/*------Set-views-background-colors-----------------------*/
	VanView->SetViewColor(bgcolor);
	
	
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
		.AddStrut(0)
		.AddGroup(B_HORIZONTAL)
			.AddGlue()
			.Add(btncompute)
			.Add(btnclear)
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

		case MENU_APP_QUIT:
			be_app->PostMessage(B_QUIT_REQUESTED);
		break;
		
		
		// Convert From
		case CONVERT_FROM_FOOT:
		{
			FromValue = 0;
			
		}
		break;
		case CONVERT_FROM_KILOMETER:
		{
			FromValue = 1;
			
		}
		break;
		case CONVERT_FROM_METER:
		{
			FromValue = 2;
		
		}
		break;
		case CONVERT_FROM_MILEUS:
		{
			FromValue = 3;
		
		}
		break;
		case CONVERT_FROM_HORSEPOWER:
		{
			FromValue = 4;
		
		}
		break;
		case CONVERT_FROM_KILOWATT:
		{
			FromValue = 5;
		}
		break;
		case CONVERT_FROM_CELSIUS:
		{
			FromValue = 6;

		}
		break;
		case CONVERT_FROM_FAHRENHEIT:
		{
			FromValue = 7;

		}
		break;
		case CONVERT_FROM_GALLONUS:
		{
			FromValue = 8;

		}
		break;
		case CONVERT_FROM_LITRE:
		{
			FromValue = 9;

		}
		break;
		case CONVERT_FROM_KILOGRAM:
		{
			FromValue = 10;
			
		}
		break;
		case CONVERT_FROM_POUND:
		{
			FromValue = 11;
		
		}
		break;
		
		// Convert To
		case CONVERT_TO_FOOT:
		{
			
			ToValue = 0;
			
		}
		break;
		case CONVERT_TO_KILOMETER:
		{

			ToValue = 1;

		}
		break;
		case CONVERT_TO_METER:
		{
			
			ToValue = 2;
			
		}
		break;
		case CONVERT_TO_MILEUS:
		{
			
			ToValue = 3;
			
		}
		break;
		case CONVERT_TO_HORSEPOWER:
		{
		
			ToValue = 4;
		
		}
		break;
		case CONVERT_TO_KILOWATT:
		{
		
			ToValue = 5;
		
		}
		break;
		case CONVERT_TO_CELSIUS:
		{
			
			ToValue = 6;
			
		}
		break;
		case CONVERT_TO_FAHRENHEIT:
		{
		
			ToValue = 7;
		
		}
		break;
		case CONVERT_TO_GALLONUS:
		{
			
			ToValue = 8;
		
		}
		break;
		case CONVERT_TO_LITRE:
		{
			
			ToValue = 9;
	
		}
		break;
		case CONVERT_TO_KILOGRAM:
		{
	
			ToValue = 10;
			
		}
		break;
		case CONVERT_TO_POUND:
		{
			
			ToValue = 11;
		
		}
		break;
		case BTN_COMPUTE_PRESSED:
		{
			
			ComputeResult();
			
		}
		break;
		case BTN_CLEAR_PRESSED:
		{
			
			ClearTextFields();
	
		}
		break;
		
		default:
			BWindow::MessageReceived(message);
		break;
	}
}

void VandelayWindow::ComputeResult(void)
{
	BString line;
	InputValue = atof(vantextcontrol->Text());
	Result = VanConvert(InputValue, FromValue, ToValue);
	line << Result;
	vanresultcontrol->SetText(line.String());

}

void VandelayWindow::ClearTextFields(void)
{
	
	vantextcontrol->SetText("");
	vanresultcontrol->SetText("");
	
}

