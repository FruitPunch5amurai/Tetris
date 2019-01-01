#include <ResourceManager.h>
#include <Errors.h>

#include "TetrisCell.h"
#include "TetrisContainer.h"


const int TETRIS_WIDTH = 24;
const int ROWS = 24;
const int COLUMNS = 10;
TetrisContainer::TetrisContainer()
{
	m_textureId = Rasengine::ResourceManager::GetTexture("Textures/TetrisContainer.png").id;
}


TetrisContainer::~TetrisContainer()
{
	delete[] m_tetrisCells;
}

void TetrisContainer::Init(const glm::vec2 & position,
	const glm::vec2 & dims, 
	const Rasengine::ColorRGBA8 & color)
{
	int counter = 0;
	
	m_width = dims.x;
	m_height = dims.y;
	m_color = color;
	m_position.x = position.x - (m_width / 2);
	m_position.y = position.y - (m_height / 2);

	m_tetrisCells = new TetrisCell[ROWS*COLUMNS];

	glm::vec2 cellPos(m_position.x, m_position.y);
	
	for (int i = 0; i < ROWS*COLUMNS ;i++)
	{
		m_tetrisCells[i].SetPosition(cellPos);
		if (counter !=  COLUMNS - 1)
		{
			cellPos.x += TETRIS_WIDTH;
			counter++;
		}
		else {
			cellPos.y += TETRIS_WIDTH;
			cellPos.x = m_position.x;
			counter = 0;
		}
	}

}

void TetrisContainer::Draw(Rasengine::SpriteBatch& spriteBatch)
{
	const glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	glm::vec4 destRect(m_position.x, 
		m_position.y,
		m_width, 
		m_height);
	spriteBatch.Draw(destRect, uvRect, m_textureId, 0.0f, m_color);
}

void TetrisContainer::DrawTetrisPieces(Rasengine::SpriteBatch & spriteBatch)
{	
	TetrisBlock* block;
	for (int i = 0; i < (ROWS * COLUMNS) - COLUMNS*4;i++)// Dont draw last 2 rows;
	{
		block = m_tetrisCells[i].GetBlock();
		if(block != nullptr)
			block->Draw(spriteBatch);
		m_tetrisCells[i].Draw(spriteBatch, TETRIS_WIDTH, Rasengine::ColorRGBA8(100.0f, 100.0f, 100.0f,255.0f));
	}
	for (int i = (ROWS * COLUMNS) - COLUMNS*4; i < (ROWS * COLUMNS); i++)// Draw last two rows in red
	{
		block = m_tetrisCells[i].GetBlock();
		if (block != nullptr)
			block->Draw(spriteBatch);
		m_tetrisCells[i].Draw(spriteBatch, TETRIS_WIDTH, Rasengine::ColorRGBA8(255.0f, 100.0f, 100.0f, 255.0f));
	}
}

bool TetrisContainer::Update(float deltaTime)
{
	if (isLose)
		return false;
	for (int i = 0; i < m_tetrisPieces.size(); i++)
	{
		if (!m_tetrisPieces[i].Update(deltaTime, m_fallSpeed, m_collisionSpeed, m_tetrisCells))
		{
			/*Remove the Tetris Piece*/			
			m_tetrisPieces.erase(m_tetrisPieces.begin() + sizeof(TetrisPiece) * i);
			m_lastTetrisPiece = nullptr;
			CheckClearRows();
			/*Check to see if it is on the last row*/
			CheckLoseCondition();
			if (isLose)
				return false;
			/*Spawn next Tetris Piece*/
			TetrisType t = static_cast<TetrisType>(rand() % 7);
			while(t == m_lastTetrisType)
				t = static_cast<TetrisType>(rand() % 7);
			AddNextTetrisPiece(t);
		}
	}
	return true;
}
void TetrisContainer::CheckClearRows()
{
	//Iterate through rows
	for (int i = ROWS * COLUMNS; i > 0; i -= COLUMNS)	// i = row
	{
		bool clearRow = true;
		//Check columns
		for (int j = i - 1; j >= i - COLUMNS; j--) //J = column
		{
			if (m_tetrisCells[j].GetBlock() == nullptr)
			{
				clearRow = false;
				break;
			}
		}
		if (clearRow)
		{
			m_points += 1000;
			Rasengine::Debug("Cleared Row #" + std::to_string(i - COLUMNS));
			for (int k = i-1; k >= i - COLUMNS; k--) // k = column
			{
				delete m_tetrisCells[k].GetBlock();
				m_tetrisCells[k].SetBlock(nullptr);
			}
			//Move All blocks above to the row down
			for (int cell = i; cell < ROWS * COLUMNS; cell++)
			{
				TetrisBlock* tetrisBlock = m_tetrisCells[cell].GetBlock();
				if (tetrisBlock == nullptr)
					continue;
				tetrisBlock->SetIndex(cell - COLUMNS);
				tetrisBlock->SetPosition(m_tetrisCells[cell - COLUMNS].GetPosition());
				tetrisBlock->SetCellPosition(glm::ivec2(tetrisBlock->GetCellPosition().x, tetrisBlock->GetCellPosition().y - 1));
				m_tetrisCells[cell].SetBlock(nullptr);
				m_tetrisCells[cell - COLUMNS].SetBlock(tetrisBlock);
			}
		}
	}
}

void TetrisContainer::CheckLoseCondition()
{
	int lastRow = (ROWS * COLUMNS) - COLUMNS*4;
	for (int i = 0; i < COLUMNS; i++)
	{
		if (m_tetrisCells[lastRow + i].GetBlock() != nullptr)
		{
			isLose = true;
			Rasengine::Debug("Player Lost!");
			break;
		}
	}
}


void TetrisContainer::AddNextTetrisPiece(TetrisType type)
{
	TetrisPiece piece;
	piece.CreateTetrisPiece(glm::vec2(m_position.x, m_position.y + m_height), m_tetrisCells, type, m_idCounter);
	//m_lastTetrisPiece.CreateTetrisPiece(glm::vec2(m_position.x + TETRIS_WIDTH *5, m_position.y + TETRIS_WIDTH * 6), type, m_idCounter);
	for (auto& b : piece.GetTetrisBlocks())
	{
		glm::vec2 pos = b->GetPosition();
		int index = (int)(((pos.y - m_position.y)/TETRIS_WIDTH) * COLUMNS + ((pos.x - m_position.x) / TETRIS_WIDTH));
		m_tetrisCells[index].SetBlock(b);
		b->SetIndex(index);
	}
	m_fallSpeed = 30.0f;
	m_tetrisPieces.push_back(piece);
	m_lastTetrisPiece = &m_tetrisPieces[m_tetrisPieces.size() - 1];
	m_idCounter++;
	m_lastTetrisType = type;
}