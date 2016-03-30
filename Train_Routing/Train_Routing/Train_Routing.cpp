// Train_Routing.cpp : main project file.

#include "stdafx.h"
#include "Mainmenu.h"
using namespace Train_Routing;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew Mainmenu());//*** Mainmenu is the main window ***//
	return 0;
}
