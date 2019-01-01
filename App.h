#pragma once
#include <IMainGame.h>
#include "TetrisPlayScreen.h"


class App : public Rasengine::IMainGame
{
public:
	App();
	~App();


	virtual void OnInit() override;
	virtual void AddScreens() override;
	virtual void OnExit() override;

private:

	std::unique_ptr<TetrisPlayScreen> m_gamePlayScreen = nullptr;
};

