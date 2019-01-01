#pragma once
#include <IGameScreen.h>
#include <vector>
#include <SpriteBatch.h>
#include <GLSLProgram.h>
#include <Camera.h>
#include <GLTexture.h>
#include <Window.h>
#include <GUI.h>
#include <DebugRenderer.h>

#include "TetrisController.h"


class TetrisPlayScreen : public Rasengine::IGameScreen
{
public:
	TetrisPlayScreen(Rasengine::Window* window);
	~TetrisPlayScreen();
	//Return the index of the next or previous screen when changing
	virtual int GetNextScreenIndex() const override;
	virtual int GetPreviousScreenIndex() const override;


	//Called at beggining and end of application
	virtual void Build() override;
	virtual void Destroy() override;

	//Called when a screen enters and exits focus
	virtual void OnEntry() override;
	virtual void OnExit() override;

	//Called in main game loop
	virtual void Update() override;
	virtual void Draw() override;

private:
	void CheckInput();
	bool  m_renderDebug = true;

	//Tetris 
	TetrisController m_tetrisController;

	//Rasengine::DebugRenderer m_debugRenderer;
	Rasengine::GLSLProgram m_textureProgram;
	//Rasengine::GLSLProgram m_lightProgram;
	Rasengine::Camera2D m_camera;
	Rasengine::SpriteBatch m_spriteBatch;
	Rasengine::GLTexture m_texture;
	Rasengine::Window* m_window;
	
	//GUI STUFF
	Rasengine::GUI m_gui;
	CEGUI::MultiLineEditbox* m_score;
};

