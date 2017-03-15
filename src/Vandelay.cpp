
#include "Vandelay.h"

const char * kSignature = "application/x-vnd.Blum-Vandelay";


VandelayApp::VandelayApp() : BApplication(kSignature) {
	
	
	VanWindow = new VandelayWindow();
			
	// make window visible
	VanWindow->Show();
}

void
VandelayApp::AboutRequested()
{
	BAlert *alert = new BAlert("about",
		"VanDelay v1.0\n"
		"\tby David Blumberg,\n"
		"\tdavidblumberg@linux.se\n"
		"\tCopyright 200?\n\n"
		"Convert between units and all kinds of\n"
		"measurements with ease.",
		"Thank you"
		);

	BTextView *view = alert->TextView();
	BFont font;
	view->SetStylable(true);
	view->GetFont(&font);
	font.SetSize(font.Size() + 4);
	font.SetFace(B_BOLD_FACE);
	view->SetFontAndColor(0, 11, &font);
	alert->Go();
}


int main() {	

	VandelayApp VanApp;
	VanApp.Run();
	return 0;
}
