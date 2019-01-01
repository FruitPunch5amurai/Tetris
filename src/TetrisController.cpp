#include "TetrisController.h"
#include "TetrisContainer.h"

TetrisController::TetrisController()
{
	
}

TetrisController::~TetrisController()
{
}



void TetrisController::Init(Rasengine::InputManager& inputManager)
{
	m_inputManager =&inputManager;
}

void TetrisController::CreateTetrisContainer(const glm::vec2 & position,
	const glm::vec2 & dims, 
	const Rasengine::ColorRGBA8 & color)
{
	if (m_tetrisContainer == nullptr)
	{
		m_tetrisContainer = new TetrisContainer();
		m_tetrisContainer->Init(position,
			dims,
			color);
	}
}

void TetrisController::Draw(Rasengine::SpriteBatch& spriteBatch)
{
	m_tetrisContainer->Draw(spriteBatch);
	m_tetrisContainer->DrawTetrisPieces(spriteBatch);
}
int TetrisController::GetPoints()
{
	return m_tetrisContainer->m_points; 
}
bool TetrisController::Update(float deltaTime)
{
	m_frameCounter += 1.0f + deltaTime;
	if (m_inputManager->isKeyPressed(SDLK_1))
	{
		if (m_frameCounter >= m_addRate)
		{
			printf("Added Tetris Piece I \n");
			m_tetrisContainer->AddNextTetrisPiece(TetrisType::I_Block);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_2))
	{
		if (m_frameCounter >= m_addRate)
		{
			printf("Added Tetris Piece J \n");
			m_tetrisContainer->AddNextTetrisPiece(TetrisType::J_Block);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_3))
	{
		if (m_frameCounter >= m_addRate)
		{
			printf("Added Tetris Piece L \n");
			m_tetrisContainer->AddNextTetrisPiece(TetrisType::L_Block);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_4))
	{
		if (m_frameCounter >= m_addRate)
		{
			printf("Added Tetris Piece O \n");
			m_tetrisContainer->AddNextTetrisPiece(TetrisType::O_Block);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_5))
	{
		if (m_frameCounter >= m_addRate)
		{
			printf("Added Tetris Piece S \n");
			m_tetrisContainer->AddNextTetrisPiece(TetrisType::S_Block);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_6))
	{
		if (m_frameCounter >= m_addRate)
		{
			printf("Added Tetris Piece T \n");
			m_tetrisContainer->AddNextTetrisPiece(TetrisType::T_Block);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_7))
	{
		if (m_frameCounter >= m_addRate)
		{
			printf("Added Tetris Piece Z \n");
			m_tetrisContainer->AddNextTetrisPiece(TetrisType::Z_Block);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_0))
	{
		if (m_frameCounter >= m_addRate)
		{
			printf("Added Tetris Piece Z \n");
			m_tetrisContainer->AddNextTetrisPiece(TetrisType::SINLGE);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_RIGHT))
	{
		if (m_frameCounter >= m_addRate && m_tetrisContainer->m_lastTetrisPiece != nullptr)
		{
			m_tetrisContainer->m_lastTetrisPiece->MoveTetrisPiece(m_tetrisContainer->m_tetrisCells, glm::vec2(1.0f, 0.0f));
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_LEFT))
	{
		if (m_frameCounter >= m_addRate && m_tetrisContainer->m_lastTetrisPiece != nullptr)
		{
			m_tetrisContainer->m_lastTetrisPiece->MoveTetrisPiece(m_tetrisContainer->m_tetrisCells, glm::vec2(-1.0f, 0.0f));
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_z))
	{
		if (m_frameCounter >= m_addRate && m_tetrisContainer->m_lastTetrisPiece != nullptr)
		{
			m_tetrisContainer->m_lastTetrisPiece->Rotate(m_tetrisContainer->m_tetrisCells, m_tetrisContainer->m_position, true);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_x))
	{
		if (m_frameCounter >= m_addRate && m_tetrisContainer->m_lastTetrisPiece != nullptr)
		{
			m_tetrisContainer->m_lastTetrisPiece->Rotate(m_tetrisContainer->m_tetrisCells, m_tetrisContainer->m_position, false);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_SPACE))
	{
		if (m_frameCounter >= m_addRate && m_tetrisContainer->m_lastTetrisPiece != nullptr)
		{
			m_tetrisContainer->m_lastTetrisPiece->SpeedFall(m_tetrisContainer->m_tetrisCells);
			m_frameCounter = 0;
		}
	}
	else if (m_inputManager->isKeyPressed(SDLK_DOWN))
	{
		if (m_frameCounter >= m_addRate && m_tetrisContainer->m_lastTetrisPiece != nullptr)
		{
			m_tetrisContainer->m_lastTetrisPiece->MoveDown(m_tetrisContainer->m_tetrisCells);
			m_frameCounter = 0;
		}
	}
	if (!m_tetrisContainer->Update(deltaTime))
		return false;
	return true;
		
}
