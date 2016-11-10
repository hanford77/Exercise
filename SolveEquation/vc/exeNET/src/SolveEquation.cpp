//SolveEquation.cpp
#include "StdAfx.h"
#include "frmMain.h"

[System::STAThreadAttribute]
int WINAPI _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow) 
{
    // Enabling Windows XP visual effects before any controls are created
    System::Windows::Forms::Application::EnableVisualStyles();
    System::Windows::Forms::Application::SetCompatibleTextRenderingDefault(false); 
    // Create the main window and run it
    System::Windows::Forms::Application::Run(gcnew frmMain());
    return 0;
}
