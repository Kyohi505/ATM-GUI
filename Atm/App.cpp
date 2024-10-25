#include "App.h"
#include "MainFrame.h"


wxIMPLEMENT_APP(App);

bool App::OnInit() 
{
	wxInitAllImageHandlers();

	MainFrame* mainFrame = new MainFrame("ATM Simulator");
	mainFrame->SetClientSize(1024, 768);
	mainFrame->SetMaxSize(wxSize(1024, 768));
	mainFrame->CenterOnScreen();
	mainFrame->Show();
	return true;
}