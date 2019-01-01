#include "App.h"
#include <ScreenList.h>

App::App()
{
	//Set screen dims
	//m_screenWidth = 800;
	//m_screenHeight = 600;
}


App::~App()
{
}

void App::OnInit()
{

}

void App::AddScreens()
{
	m_gamePlayScreen = std::make_unique<TetrisPlayScreen>(&m_window);

	m_screenList->AddScreen(m_gamePlayScreen.get());
	m_screenList->SetScreen(m_gamePlayScreen->GetIndex());
}

void App::OnExit()
{
}
