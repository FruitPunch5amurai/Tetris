#pragma once

#include <GLM/glm.hpp>
#include <Vertex.h>
#include <SpriteBatch.h>
class TetrisBlock;

//Simple 
class TetrisCell
{
public:
	TetrisCell();
	~TetrisCell();

	void SetPosition(const glm::vec2& position) { m_position = position; }
	void SetBlock(TetrisBlock* block) { m_tetrisBlock = block; }
	void Draw(Rasengine::SpriteBatch & spriteBatch, int width, Rasengine::ColorRGBA8 color);
	glm::vec2 GetPosition() { return m_position; }
	TetrisBlock* GetBlock() { return m_tetrisBlock; }
private:
	GLuint m_textureId;
	glm::vec2 m_position;
	TetrisBlock* m_tetrisBlock = nullptr;
};

