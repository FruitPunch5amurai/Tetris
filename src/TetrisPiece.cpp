#include "TetrisPiece.h"

const int TETRIS_WIDTH = 24;
const int ROWS = 24;
const int COLUMNS = 10;
const glm::vec4 piMatrix = glm::vec4(0, -1, 1, 0);
const Rasengine::ColorRGBA8 I_BLOCK_COLOR(0.0f, 255.0f, 255.0f, 255.0f);
const Rasengine::ColorRGBA8 J_BLOCK_COLOR(10.0f, 10.0f, 255.0f, 255.0f);
const Rasengine::ColorRGBA8 L_BLOCK_COLOR(255.0f, 165.0f, 0.0f, 255.0f);
const Rasengine::ColorRGBA8 O_BLOCK_COLOR(255.0f, 255.0f, 0.0f, 255.0f);
const Rasengine::ColorRGBA8 S_BLOCK_COLOR(0.0f, 128.0f, 0.0f, 255.0f);
const Rasengine::ColorRGBA8 T_BLOCK_COLOR(148.0f, 0.0f, 211.0f, 255.0f);
const Rasengine::ColorRGBA8 Z_BLOCK_COLOR(255.0f, 0.0f, 0.0f, 255.0f);
const Rasengine::ColorRGBA8 SINGLE_BLOCK_COLOR(255.0f, 255.0f, 255.0f, 255.0f);

TetrisPiece::TetrisPiece()
{
}

TetrisPiece::~TetrisPiece()
{
}

void TetrisPiece::CreateTetrisPiece(const glm::vec2 & position, TetrisCell* cells, TetrisType type, int idCounter)
{
	m_tetrisBlocks.clear();
	m_type = type;
	isFalling = true;
	m_frameCounter = 0;
	didCollide = false;

	switch (type)
	{
	case TetrisType::I_Block:

		for (int i = 0; i < 4; i++)
		{
			m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH*i), position.y),
				idCounter,
				I_BLOCK_COLOR));
		}
		m_pivot = m_tetrisBlocks[1];
		break;
	case TetrisType::J_Block:
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH * 2), position.y),
			idCounter,
			J_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH), position.y),
			idCounter,
			J_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x, position.y),
			idCounter,
			J_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x, position.y + TETRIS_WIDTH),
			idCounter,
			J_BLOCK_COLOR));
		m_pivot = m_tetrisBlocks[1];
		break;
	case TetrisType::L_Block:
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH * 2), position.y),
			idCounter,
			L_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH), position.y),
			idCounter,
			L_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x, position.y),
			idCounter,
			L_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH * 2), position.y + TETRIS_WIDTH),
			idCounter,
			L_BLOCK_COLOR));
		m_pivot = m_tetrisBlocks[1];
		break;
	case TetrisType::O_Block:
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x, position.y),
			idCounter,
			O_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH), position.y),
			idCounter,
			O_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH), position.y + (TETRIS_WIDTH)),
			idCounter,
			O_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x, position.y + (TETRIS_WIDTH)),
			idCounter,
			O_BLOCK_COLOR));
		m_pivot = nullptr;
		break;
	case TetrisType::S_Block:
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x, position.y),
			idCounter,
			S_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH), position.y),
			idCounter,
			S_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH), position.y + (TETRIS_WIDTH)),
			idCounter,
			S_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH * 2), position.y + (TETRIS_WIDTH)),
			idCounter,
			S_BLOCK_COLOR));
		m_pivot = m_tetrisBlocks[1];
		break;
	case TetrisType::T_Block:
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x, position.y),
			idCounter,
			T_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH), position.y),
			idCounter,
			T_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH), position.y + (TETRIS_WIDTH)),
			idCounter,
			T_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH * 2), position.y),
			idCounter,
			T_BLOCK_COLOR));
		m_pivot = m_tetrisBlocks[1];
		break;
	case TetrisType::Z_Block:
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x, position.y + (TETRIS_WIDTH)),
			idCounter,
			Z_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH), position.y + (TETRIS_WIDTH)),
			idCounter,
			Z_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH), position.y),
			idCounter,
			Z_BLOCK_COLOR));
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x + (TETRIS_WIDTH * 2), position.y),
			idCounter,
			Z_BLOCK_COLOR));
		m_pivot = m_tetrisBlocks[2];
		break;
	default:
		m_tetrisBlocks.push_back(new TetrisBlock(glm::vec2(position.x, position.y),
			idCounter,
			SINGLE_BLOCK_COLOR));
		m_pivot = nullptr;
		break;
	}
	idCounter++;
}

bool TetrisPiece::Update(float deltaTime, float fallSpeed, float collisionSpeed, TetrisCell* tetrisCells)
{
	m_frameCounter += 0.1f + deltaTime;
	bool collisionTimeDone = false;

	if (didCollide)
		m_collisionFrameCounter += deltaTime;
	else
		m_collisionFrameCounter = 0;

	if (m_frameCounter > fallSpeed)
	{
		m_frameCounter = 0;
		for (auto& p : m_tetrisBlocks)
		{
			didCollide = CheckCollision(p, tetrisCells);
			if (didCollide)
			{
				break;
			}
		}
		for (auto& p : m_tetrisBlocks)
		{
			if (didCollide) {
				/*Check to see if the time remaining to move is up*/
				if (m_collisionFrameCounter >= collisionSpeed)
				{
					collisionTimeDone = true;
					p->inPlay = false;
				}
			}
			else
			{
				/*Falling*/
				int oldIndex = p->m_cellIndex;
				int newIndex = p->m_cellIndex - COLUMNS;
				tetrisCells[newIndex].SetBlock(p);
				p->m_position = tetrisCells[newIndex].GetPosition();
				p->SetIndex(newIndex);
				if (tetrisCells[oldIndex].GetBlock() == p)
				{
					tetrisCells[oldIndex].SetBlock(nullptr);
				}
			}
		}
		if (collisionTimeDone && didCollide)
			return false;
	}
	return true;
}
void TetrisPiece::SpeedFall(TetrisCell* tetrisCells)
{
	bool done = false;
	while(!done)
	{
		for (int i = 0; i < 4; i++)
		{
			if (m_tetrisBlocks[i]->m_cellIndex - COLUMNS < 0)
			{
				done = true;
				break;
			}
			TetrisBlock* t = tetrisCells[m_tetrisBlocks[i]->m_cellIndex - COLUMNS].GetBlock();
			if (t != nullptr)
			{
				if (t->id == m_tetrisBlocks[i]->id)
				{
					continue;/*Keep going*/
				}
				else /*Hit a block*/
				{
					done = true;
					break;
				}
			}
			else
				continue;/*Keep going*/
		}
		if (!done)
		{
			for (auto& p : m_tetrisBlocks)
			{
				/*Falling*/
				int oldIndex = p->m_cellIndex;
				int newIndex = p->m_cellIndex - COLUMNS;
				tetrisCells[newIndex].SetBlock(p);
				p->m_position = tetrisCells[newIndex].GetPosition();
				p->SetIndex(newIndex);
				if (tetrisCells[oldIndex].GetBlock() == p)
				{
					tetrisCells[oldIndex].SetBlock(nullptr);
				}
			}
		}
	}
	didCollide = true;
	m_frameCounter = m_collisionFrameCounter = 1000.0f;
}
void TetrisPiece::MoveDown(TetrisCell * tetrisCells)
{
		bool done = false;
		for (int i = 0; i < 4; i++)
		{
			if (m_tetrisBlocks[i]->m_cellIndex - COLUMNS < 0)
			{
				done = true;
				break;
			}
			TetrisBlock* t = tetrisCells[m_tetrisBlocks[i]->m_cellIndex - COLUMNS].GetBlock();
			if (t != nullptr)
			{
				if (t->id == m_tetrisBlocks[i]->id)
				{
					continue;/*Keep going*/
				}
				else /*Hit a block*/
				{
					done = true;
					break;
				}
			}
			else
				continue;/*Keep going*/
		}
		if (!done)
		{
			for (auto& p : m_tetrisBlocks)
			{
				/*Falling*/
				int oldIndex = p->m_cellIndex;
				int newIndex = p->m_cellIndex - COLUMNS;
				tetrisCells[newIndex].SetBlock(p);
				p->m_position = tetrisCells[newIndex].GetPosition();
				p->SetIndex(newIndex);
				if (tetrisCells[oldIndex].GetBlock() == p)
				{
					tetrisCells[oldIndex].SetBlock(nullptr);
				}
			}
		}
	//didCollide = true;
	//m_frameCounter = m_collisionFrameCounter = 1000.0f;
}
/*Check if you will collide with any blocks beneath*/
bool TetrisPiece::CheckCollision(TetrisBlock* block, TetrisCell* tetrisCells)
{
	int index = block->m_cellIndex - COLUMNS;
	if (index < 0)
	{
		return true;
	}
	if (tetrisCells[index].GetBlock() == nullptr)
	{
		return false;
	}
	else {
		if (tetrisCells[index].GetBlock()->id == block->id)
			return false;
	}
	return true;
}

void TetrisPiece::MoveTetrisPiece(TetrisCell* tetrisCells, const glm::vec2& dir)
{
	TetrisBlock* block;
	int newIndex;
	for (auto& b : m_tetrisBlocks)
	{
		if (!b->inPlay) {
			return;
		}
		newIndex = b->m_cellIndex + dir.x;
		if (floor(b->m_cellIndex / COLUMNS) != floor(newIndex / COLUMNS) || newIndex < 0)
			return;
		block = tetrisCells[newIndex].GetBlock();
		if (block != nullptr)
		{
			if (block->id != b->id) {
				return;
			}
		}
	}
	for (auto& p : m_tetrisBlocks)
	{
		int oldIndex = p->m_cellIndex;
		newIndex = p->m_cellIndex + dir.x;
		tetrisCells[newIndex].SetBlock(p);
		p->m_position = tetrisCells[newIndex].GetPosition();
		p->SetIndex(newIndex);
		if (tetrisCells[oldIndex].GetBlock() == p)
		{
			tetrisCells[oldIndex].SetBlock(nullptr);
		}
	}
}

void TetrisPiece::Rotate(TetrisCell* cells, const glm::vec2& containerPosition, bool isRight)
{
	int i = 0;
	TetrisBlock rotatedBlocks[4];
	bool blockCollisionOccured = false;
	bool borderCollisionOccured = false;
	bool canResolveCollision = true;

	if (m_pivot == nullptr) return;
	if (isRight)
	{
		for (auto &b : m_tetrisBlocks)
		{
			glm::vec2 pivotCoords = glm::vec2((m_pivot->m_position.x - containerPosition.x) / TETRIS_WIDTH,
				(m_pivot->m_position.y - containerPosition.y) / TETRIS_WIDTH);
			glm::vec2 blockCoords = glm::vec2((b->m_position.x - containerPosition.x) / TETRIS_WIDTH,
				(b->m_position.y - containerPosition.y) / TETRIS_WIDTH);

			glm::vec2 Vr = blockCoords - pivotCoords;

			//Transform by pi/2 matrix
			/*
			[0  1]
			[-1  0]
			*/
			glm::vec2 Vt = glm::vec2(
				(piMatrix.x * Vr.x) + (-piMatrix.y * Vr.y),
				(-piMatrix.z * Vr.x) + (piMatrix.w * Vr.y));
			glm::vec2 V = pivotCoords + Vt;

			if (b == m_pivot)
			{
				rotatedBlocks[i].m_cellPosition = glm::ivec2(V.x, V.y);
				rotatedBlocks[i].m_position = b->m_position;
				rotatedBlocks[i].m_cellIndex = b->m_cellIndex;
				rotatedBlocks[i].id = m_tetrisBlocks[i]->id;
				i++;
			}
			else
			{
				rotatedBlocks[i].m_position = glm::vec2(containerPosition.x + (V.x* TETRIS_WIDTH),
					containerPosition.y + (V.y * TETRIS_WIDTH));
				rotatedBlocks[i].m_cellIndex = V.y * COLUMNS + V.x;
				rotatedBlocks[i].m_cellPosition = glm::ivec2(V.x, V.y);

				//Check to see if there was a collision with borders of container
				if (V.x >= COLUMNS || V.x < 0 || V.y < 0 || V.y >= ROWS)
				{
					borderCollisionOccured = true;
				}
				rotatedBlocks[i].id = m_tetrisBlocks[i]->id;
				if (rotatedBlocks[i].m_cellIndex >= 0 && rotatedBlocks[i].m_cellIndex < ROWS * COLUMNS)
				{
					if (cells[rotatedBlocks[i].m_cellIndex].GetBlock() != nullptr)
					{
						if (cells[rotatedBlocks[i].m_cellIndex].GetBlock()->id != b->id)
							blockCollisionOccured = true;
					}
				}
				i++;
				//b->m_position = glm::vec2(containerPosition.x + (V.x* TETRIS_WIDTH), containerPosition.y + (V.y * TETRIS_WIDTH));
				//cells[b->m_cellIndex].SetBlock(nullptr);
				//b->m_cellIndex = V.y * COLUMNS + V.x;
				//cells[b->m_cellIndex].SetBlock(b);
			}

		}
	}
	else
	{
		for (auto &b : m_tetrisBlocks)
		{
			glm::vec2 pivotCoords = glm::vec2((m_pivot->m_position.x - containerPosition.x) / TETRIS_WIDTH, (m_pivot->m_position.y - containerPosition.y) / TETRIS_WIDTH);
			glm::vec2 blockCoords = glm::vec2((b->m_position.x - containerPosition.x) / TETRIS_WIDTH, (b->m_position.y - containerPosition.y) / TETRIS_WIDTH);

			glm::vec2 Vr = blockCoords - pivotCoords;

			//Transform by negative pi/2 matrix
			/*
			[0  -1]
			[1  0]
			*/
			glm::vec2 Vt = glm::vec2(
				(piMatrix.x * Vr.x) + (piMatrix.y * Vr.y),
				(piMatrix.z * Vr.x) + (piMatrix.w * Vr.y));
			glm::vec2 V = pivotCoords + Vt;
			if (b == m_pivot)
			{
				rotatedBlocks[i].m_cellPosition = glm::ivec2(V.x, V.y);
				rotatedBlocks[i].m_position = b->m_position;
				rotatedBlocks[i].m_cellIndex = b->m_cellIndex;
				rotatedBlocks[i].id = m_tetrisBlocks[i]->id;
				i++;
			}
			else
			{
				rotatedBlocks[i].m_position = glm::vec2(containerPosition.x + (V.x* TETRIS_WIDTH), containerPosition.y + (V.y * TETRIS_WIDTH));
				rotatedBlocks[i].m_cellIndex = V.y * COLUMNS + V.x;
				rotatedBlocks[i].m_cellPosition = glm::ivec2(V.x, V.y);
				if (V.x >= COLUMNS || V.x < 0 || V.y < ROWS || V.y >= COLUMNS * ROWS)
				{
					borderCollisionOccured = true;
				}
				rotatedBlocks[i].id = m_tetrisBlocks[i]->id;
				if (rotatedBlocks[i].m_cellIndex >= 0 && rotatedBlocks[i].m_cellIndex < ROWS * COLUMNS)
				{
					if (cells[rotatedBlocks[i].m_cellIndex].GetBlock() != nullptr )
					{
						if (cells[rotatedBlocks[i].m_cellIndex].GetBlock()->id != b->id)
							blockCollisionOccured = true;
					}
				}
				i++;
				//b->m_position = glm::vec2(containerPosition.x + (V.x* TETRIS_WIDTH), containerPosition.y + (V.y * TETRIS_WIDTH));
				//cells[b->m_cellIndex].SetBlock(nullptr);
				//b->m_cellIndex = V.y * COLUMNS + V.x;
				//cells[b->m_cellIndex].SetBlock(b);
			}
		}
	}
	/*If rotation collided with border, resolve it first*/
	if (borderCollisionOccured)
	{
		ResolveBorderCollision(rotatedBlocks, cells);
	}
	/*Check if a block collision ocurred while rotating*/
	if (blockCollisionOccured)
	{
		canResolveCollision = CheckRotationCollision(rotatedBlocks, cells);
	}
	/*If we cant resolve rotation collision, then dont rotate tetris piece*/
	if (canResolveCollision == false)
		return;
	/*First Clear cells*/
	for (int i = 0; i < 4; i++)
	{
		cells[m_tetrisBlocks[i]->m_cellIndex].SetBlock(nullptr);
	}
	/*Then set cells*/
	for (int i = 0; i < 4; i++)
	{
		m_tetrisBlocks[i]->m_position = rotatedBlocks[i].m_position;
		m_tetrisBlocks[i]->m_cellIndex = rotatedBlocks[i].m_cellIndex;
		m_tetrisBlocks[i]->m_cellPosition = rotatedBlocks[i].m_cellPosition;
		cells[rotatedBlocks[i].m_cellIndex].SetBlock(m_tetrisBlocks[i]);
	}
}

bool TetrisPiece::CanSpawn(TetrisCell * cells, const glm::vec2 & pos)
{
	int x = 0;
	int y = pos.y / ROWS;
	if (cells[y*COLUMNS + x].GetBlock() != nullptr)
		return false;
	return true;
}
/*Resolve the border collision*/
void TetrisPiece::ResolveBorderCollision(TetrisBlock * rotatedBlocks, TetrisCell * tetrisCells)
{
	for (int i = 0; i < 4; i++)
	{
		//Move blocks right
		if (rotatedBlocks[i].m_cellPosition.x < 0)
		{
			for (int j = 0; j < 4; j++)
			{
				rotatedBlocks[j].m_cellIndex += 1;
				rotatedBlocks[j].m_position = tetrisCells[rotatedBlocks[j].m_cellIndex].GetPosition();
				rotatedBlocks[j].m_cellPosition.x += 1;
			}
			ResolveBorderCollision(rotatedBlocks, tetrisCells);
			break;
		}
		// Move blocks left
		else if (rotatedBlocks[i].m_cellPosition.x >= COLUMNS) {
			for (int j = 0; j < 4; j++)
			{
				rotatedBlocks[j].m_cellIndex -= 1;
				rotatedBlocks[j].m_position = tetrisCells[rotatedBlocks[j].m_cellIndex].GetPosition();
				rotatedBlocks[j].m_cellPosition.x -= 1;
			}
			ResolveBorderCollision(rotatedBlocks, tetrisCells);
			break;
		}
		//Move blocks up
		else if (rotatedBlocks[i].m_cellPosition.y < 0)
		{
			for (int j = 0; j < 4; j++)
			{
				rotatedBlocks[j].m_cellIndex += COLUMNS;
				rotatedBlocks[j].m_position = tetrisCells[rotatedBlocks[j].m_cellIndex].GetPosition();
				rotatedBlocks[j].m_cellPosition.y += 1;
			}
			ResolveBorderCollision(rotatedBlocks, tetrisCells);
			break;
		}
		//Move blocks down
		else if (rotatedBlocks[i].m_cellPosition.y >= ROWS) {
			for (int j = 0; j < 4; j++)
			{
				rotatedBlocks[j].m_cellIndex -= COLUMNS;
				rotatedBlocks[j].m_position = tetrisCells[rotatedBlocks[j].m_cellIndex].GetPosition();
				rotatedBlocks[j].m_cellPosition.y -= 1;
			}
			ResolveBorderCollision(rotatedBlocks, tetrisCells);
			break;
		}
	}
}
/*Resolve the rotation collision*/
bool TetrisPiece::CheckRotationCollision(TetrisBlock* rotatedBlocks, TetrisCell* tetrisCells)
{
	//Check if we can move up
	if (!CanMoveUp(rotatedBlocks, tetrisCells))
	{
		//Check if we can move right
		if (!CanMoveRight(rotatedBlocks, tetrisCells))
		{
			//Check if we can move left
			if (!CanMoveLeft(rotatedBlocks, tetrisCells))
			{
				//If we cannot move anywhere then return blocks
				return false;
			}
			else {
				for (int i = 0; i < 4; i++)
				{
					rotatedBlocks[i].m_cellIndex--;
					rotatedBlocks[i].m_position = glm::vec2(rotatedBlocks[i].m_position.x - TETRIS_WIDTH,
						rotatedBlocks[i].m_position.y);
				}
				return true;
			}
		}
		else {
			for (int i = 0; i < 4; i++)
			{
				rotatedBlocks[i].m_cellIndex++;
				rotatedBlocks[i].m_position = glm::vec2(rotatedBlocks[i].m_position.x + TETRIS_WIDTH,
					rotatedBlocks[i].m_position.y);
			}
			return true;
		}
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			rotatedBlocks[i].m_cellIndex += COLUMNS;
			rotatedBlocks[i].m_position = glm::vec2(rotatedBlocks[i].m_position.x,
				rotatedBlocks[i].m_position.y + TETRIS_WIDTH);
		}
		return true;
	}
}

bool TetrisPiece::CanMoveLeft(TetrisBlock* rotatedBlocks, TetrisCell * tetrisCells)
{
	TetrisBlock* temp = nullptr;
	for (int i = 0; i < 4; i++)
	{
		temp = tetrisCells[rotatedBlocks[i].m_cellIndex - 1].GetBlock();
		if (temp != nullptr)
		{
			if (temp->id != rotatedBlocks[i].id)
			{
				return false;
			}
		}
	}
	return true;
}

bool TetrisPiece::CanMoveRight(TetrisBlock* rotatedBlocks, TetrisCell* tetrisCells)
{
	TetrisBlock* temp = nullptr;
	for (int i = 0; i < 4; i++)
	{
		temp = tetrisCells[rotatedBlocks[i].m_cellIndex + 1].GetBlock();
		if (temp != nullptr)
		{
			if (temp->id != rotatedBlocks[i].id)
			{
				return false;
			}
		}
	}
	return true;
}

bool TetrisPiece::CanMoveUp(TetrisBlock* rotatedBlocks, TetrisCell* tetrisCells)
{
	TetrisBlock* temp = nullptr;
	for (int i = 0; i < 4; i++)
	{
		temp = tetrisCells[rotatedBlocks[i].m_cellIndex + COLUMNS].GetBlock();
		if (temp != nullptr)
		{
			if (temp->id != rotatedBlocks[i].id)
			{
				return false;
			}
		}
	}
	return true;
}
