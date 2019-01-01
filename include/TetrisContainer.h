#pragma once

#include <SDL/SDL.h>
#include <GLM/glm.hpp>
#include <GLSLProgram.h>
#include <Vertex.h>
#include <vector>
#include "TetrisPiece.h"
#include <SpriteBatch.h>

class TetrisBlock;
class TetrisCell;


class TetrisContainer
{
public:
	TetrisContainer(); 
	~TetrisContainer();

	void Init(const glm::vec2& position, const glm::vec2& dims, const Rasengine::ColorRGBA8& color);
	void Draw(Rasengine::SpriteBatch& spriteBatch);
	void DrawTetrisPieces(Rasengine::SpriteBatch& spriteBatch);
	bool Update(float deltaTime);
	void AddNextTetrisPiece(TetrisType type);
	void CheckClearRows();
	void CheckLoseCondition();


private:
	int m_width;
	int m_height;
	
	float m_fallSpeed = 20.0f;/*30.0f;*/
	float m_collisionSpeed = 100.0f;/* 240.0f;*/

	int m_points = 0;

	int m_idCounter = 0;

	bool isLose = false;

	glm::vec2 m_position;

	Rasengine::ColorRGBA8 m_color;

	GLuint m_textureId;

	TetrisPiece* m_lastTetrisPiece;

	TetrisType m_lastTetrisType;

	std::vector<TetrisPiece> m_tetrisPieces;
	
	TetrisCell* m_tetrisCells;

	friend class TetrisController;
};

